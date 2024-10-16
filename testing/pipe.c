#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "../libft/header/libft.h"

typedef struct s_m
{
	char **pipe;
}	t_m;

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

void	exec_pipe(char **line)
{
	int		i;
	int		pipe_fd[2];
	int		save_fd[2];
	int		pid;
	int		status;
	char	**comm;

	save_fd[0] = -1;
	i = 0;
	while (line[i])
	{
		printf("---i:%d\n", i);
		comm = ft_split(line[i], " ");
		if (line[i + 1])
		{
			pipe(pipe_fd);
			printf("---pipe(pipe_fd): [0]:%d, [1]:%d\n", pipe_fd[0], pipe_fd[1]);
		}
		pid = fork();
		if (pid == 0)
		{
			printf("---in child: pid=%d\n", pid);
			if (save_fd[0] != -1)
			{
				dup2(save_fd[0], STDIN_FILENO);
				close(save_fd[0]);
			}
			if (line[i + 1])
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			execve(comm[0], comm, NULL);
			exit (0 * printf("---execve didnt work\n"));
		}
		else
		{
			printf("---in parent: pid=%d\n", pid);
			if (save_fd[0] != -1)
				close(save_fd[0]);
			if (line[i + 1])
			{
				close(pipe_fd[1]);
				save_fd[0] = pipe_fd[0];
			}
			waitpid(pid, &status, 0);
		}
	i++;
	}
}

int main()
{
	char	*s;
	char	**line;
	s = "/bin/ls | /usr/bin/grep i";
//	s = "/bin/cat | /bin/cat | /bin/ls";
//	s = "/bin/cat file | /usr/bin/grep bla | /usr/bin/more";
//	s = "/bin/ls filethatdoesnotexist | /usr/bin/grep bla | /usr/bin/more";

	line = ft_split(s, "|");
	print_comms(line);
	exec_pipe(line);
	ft_split_free(line);
	return (0);
}
