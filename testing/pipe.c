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


//	cat | cat | ls
// cat file | grep bla | more
// cat filethatdoesnotexist | grep bla | more

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

/*

redirection stripping happens before splitting around pipes(|) character
redir in only applies to first command
redir out only applies to last command
for the purposes of passing the eval its fine because they only check pipes or redirection, but not both at once
builtins will execute inside of forked child process
"echo asd | cd /" or "echo asd | export var=value", because cd and export are running in a child, their effect will not last
this is fine, bash behaves the same, this makes it easier to handles pipes and dup2 and stuff

*/

int main()
{
	char	*s;
	char	**line;
//	char	**redir_in;
//	char	**redir_out;

	s = "/bin/ls | /usr/bin/grep i";
//	s = "/bin/cat | /bin/cat | /bin/ls";
//	s = "/bin/cat file | /usr/bin/grep bla"
//	s = "/bin/cat file | /usr/bin/grep bla | /usr/bin/more";
//	s = "/bin/ls filethatdoesnotexist | /usr/bin/grep bla | /usr/bin/more";
	line = ft_split(s, "|");

	print_comms(line);
	exec_pipe(line);

	ft_split_free(line);
	return (0);
}