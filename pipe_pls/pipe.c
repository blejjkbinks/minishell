#include "../libft/header/libft.h"
#include <stdio.h>

void	print_comms(char **line)
{
	char	**comm;

	for (int i = 0; line[i]; i++)
	{
		comm = ft_split(line[i], " ");
		for (int j = 0; comm[j]; j++)
		{
			if (ft_strchr(comm[j], '/'))
				printf("%s", ft_strrchr(comm[j], '/') + 1);
			else
				printf("%s", comm[j]);
			if (comm[j + 1])
				printf(",");	
		}
		ft_split_free(comm);
		printf(";\n");
	}
	printf("_________\n");
}


/*

void	ft_close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void	ft_exec(char **arg, int first, int last, int pipefd[2], int *prevfd)
{
	int pid = fork();
	if (pid == 0)
	{
		printf("in child, comm:%s, f:%d, l:%d\n", arg[0], first, last);
		if (!last)
			dup2(pipefd[1], STDOUT_FILENO);
		if (!first)
			dup2(pipefd[0], STDIN_FILENO);
		ft_close_pipe(pipefd);
		execve(arg[0], arg, NULL);
	}
	waitpid(pid, NULL, 0);
	// if (!first)
	// 	close(*prevfd);
	// if (!last)
	// 	close(pipefd[1]);
	// *prevfd = pipefd[0];
}

void	exec_pipe(char **comm)
{
	int	i = 0;
	int	pipefd[2];
	int	prevfd;

	prevfd = dup(STDIN_FILENO);
	while (comm[i])
	{
		char **arg = ft_split(comm[i], " ");
		if (comm[i + 1] != NULL)
			pipe(pipefd);
		ft_exec(arg, i == 0, comm[i + 1] == NULL, pipefd, &prevfd);
		ft_split_free(arg);
		i++;
	}
}
*/

/*

redirection stripping happens before splitting around pipes(|) character
redir in only applies to first command
redir out only applies to last command
for the purposes of passing the eval its fine because they only check pipes or redirection, but not both at once
builtins will execute inside of forked child process
"echo asd | cd /" or "echo asd | export var=value", because cd and export are running in a child, their effect will not last
this is fine, bash behaves the same, this makes it easier to handles pipes and dup2 and stuff

*/

/*
NEW GPT
*/

void exec_pipe(char **comm)
{
	int i = 0;
	int pipefd[2];
	int prevfd = STDIN_FILENO;

	while (comm[i])
	{
		char **arg = ft_split(comm[i], " ");
		int is_last = (comm[i + 1] == NULL);

		if (!is_last && pipe(pipefd) < 0)
			exit(1);

		int pid = fork();
		if (pid < 0)
			exit(2);

		if (pid == 0) // Child process
		{
			if (prevfd != STDIN_FILENO)
			{
				dup2(prevfd, STDIN_FILENO);
				close(prevfd);
			}
			if (!is_last)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			if (!is_last)
				close(pipefd[0]);

			execve(arg[0], arg, NULL);
			perror("execve"); // If execve fails
			exit(4);
		}

		// Parent process
		if (prevfd != STDIN_FILENO)
			close(prevfd);
		if (!is_last)
			close(pipefd[1]);

		prevfd = is_last ? STDIN_FILENO : pipefd[0];

		ft_split_free(arg);
		i++;
	}

	// Wait for all children
	while (wait(NULL) > 0)
		;
}


int ft_exec(char **arg, int first, int last, int pipefd[2], int *prevfd, int fd_in, int fd_out)
{
	int pid = fork();
	if (pid == 0)
	{
		if (first && fd_in >= 0)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		else if (!first)
			dup2(*prevfd, STDIN_FILENO);
		if (last && fd_out >= 0)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		else if (!last)
			dup2(pipefd[1], STDOUT_FILENO);

		close(pipefd[0]);
		close(pipefd[1]);
		execve(arg[0], arg, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int exec_pipe_full(char **comm, char *redir_in, char *redir_out, int out_mode, char *heredoc_delim)
{
	int i = 0;
	int pipefd[2];
	int prevfd = STDIN_FILENO;
	int flags;
	int pid;
	int status;

	int fd_in = -1, fd_out = -1;

	// Handle heredoc (`<<`)
	if (heredoc_delim)
	{
		char *tmpfile = "/tmp/heredoc_tmp.txt";
		fd_in = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0600);
		if (fd_in < 0)
		{
			perror(tmpfile);
			exit(EXIT_FAILURE);
		}

		char *line;
		while (1)
		{
			write(1, "heredoc> ", 9);
			//printf("heredoc> ");
			line = get_next_line(STDIN_FILENO); // Implement or replace with your version
			if (!line || ft_strncmp(line, heredoc_delim, ft_strlen(line)) == 0)
				break;
			write(fd_in, line, ft_strlen(line));
			write(fd_in, "\n", 1);
			free(line);
		}
		free(line);
		close(fd_in);

		fd_in = open(tmpfile, O_RDONLY);
		if (fd_in < 0)
		{
			perror(tmpfile);
			exit(EXIT_FAILURE);
		}
	}
	// Handle input redirection (`<`)
	else if (redir_in)
	{
		fd_in = open(redir_in, O_RDONLY);
		if (fd_in < 0)
			exit(8);
	}

	// Handle output redirection (`>` or `>>`)
	if (redir_out)
	{
		if (out_mode == 0)
			flags = O_CREAT | O_WRONLY | O_TRUNC;
		else
			flags = O_CREAT | O_WRONLY | O_APPEND;
		fd_out = open(redir_out, flags, 0644);
		if (fd_out < 0)
			exit(9);
	}

	while (comm[i])
	{
		char **arg = ft_split(comm[i], " ");
		int is_first = (i == 0);
		int is_last = (comm[i + 1] == NULL);

		// Create a pipe if this is not the last command
		if (!is_last && pipe(pipefd) < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		// Execute the command
		pid = ft_exec(arg, is_first, is_last, pipefd, &prevfd, fd_in, fd_out);

		// Close unnecessary file descriptors in the parent
		if (prevfd != STDIN_FILENO)
			close(prevfd);
		if (!is_last)
			close(pipefd[1]);

		prevfd = is_last ? STDIN_FILENO : pipefd[0];

		ft_split_free(arg);
		i++;
	}

	// Close the redirection file descriptors in the parent
	if (fd_in >= 0)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);

	// Wait for all child processes
	while (wait(NULL) > 0) ;
	return (0);
	//waitpid(pid, &status, 0);
	//return ((status & 0xff00) >> 8);

}

int main()
{
	char	*s;
	char	**line;
	char	*redir_in = NULL;
	char	*redir_out = "file_out";
	int		out_mode = 0;
	char	*heredoc_delim = NULL;
	int		ret;

//	s = "/bin/ls | /usr/bin/grep i";
	s = "/bin/cat | /bin/cat | /bin/ls";
//	s = "/bin/cat file_in | /usr/bin/grep bla";
//	s = "/bin/cat file_in | /usr/bin/grep bla | /usr/bin/more";
//	s = "/bin/ls filethatdoesnotexist | /usr/bin/grep bla | /usr/bin/more";
//	s = "/bin/cat";

	line = ft_split(s, "|");

/*
	print_comms(line);
	exec_pipe(line);
	printf("^^^^^^\n");
*/
	print_comms(line);
	ret = exec_pipe_full(line, redir_in, redir_out, out_mode, heredoc_delim);
	printf("^^^^^^\n");
	printf("%d\n", ret);

	ft_split_free(line);
	return (0);
}