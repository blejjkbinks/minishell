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
	int		prev_fd;
	int		*pid;
	int		status;
	char	**comm;

	pid = (int *)malloc(ft_split_len(line) * sizeof(int));
	prev_fd = -1;
	i = 0;
	while (line[i])
	{
		comm = ft_split(line[i], " ");
		if (line[i + 1])
			pipe(pipe_fd);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (line[i + 1])
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			execve(comm[0], comm, NULL);
			exit (0 * printf("execve didnt work\n"));
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (line[i + 1])
			{
				close(pipe_fd[1]);
				prev_fd = pipe_fd[0];
			}
			waitpid(pid[i], &status, 0);
		}
	i++;
	}
	free(pid);
}

int main()
{
	char	*s;
	char	**line;
//	s = "/bin/ls | /usr/bin/grep i";
//	s = "/bin/cat | /bin/cat | /bin/ls";
	s = "/bin/cat file | /usr/bin/grep bla | /usr/bin/more";
//	s = "/bin/ls filethatdoesnotexist | /usr/bin/grep bla | /usr/bin/more";

	line = ft_split(s, "|");
	print_comms(line);
	exec_pipe(line);
	ft_split_free(line);
	return (0);
}
