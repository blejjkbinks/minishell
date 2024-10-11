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

void	print_comms(t_m *m)
{
	char	**comm;

	for (int i = 0; m->pipe[i]; i++)
	{
		comm = ft_split(m->pipe[i], " ");
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

void	ex_pipe(t_m *m)
{
	int		i;
	int		pfd[2];
	int		fd_tmp;
	int		pid;
	char	**comm;

	fd_tmp = -1;
	i = 0;
	while (m->pipe[i])
	{
		comm = ft_split(m->pipe[i], " ");
		if (m->pipe[i + 1])
			pipe(pfd);
		pid = fork();
		if (pid == 0)
		{
			if (fd_tmp != -1)
			{
				dup2(fd_tmp, STDIN_FILENO);
				close(fd_tmp);
			}
			if (m->pipe[i + 1])
			{
				close(pfd[0]);
				dup2(pfd[1], STDOUT_FILENO);
				close(pfd[1]);
			}
			execve(comm[0], comm, NULL);
			exit (0 * printf("execve didnt work\n"));
		}
		else
		{
			if (fd_tmp != -1)
				close(fd_tmp);
			if (m->pipe[i + 1])
			{
				close(pfd[1]);
				fd_tmp = pfd[0];
			}
			wait(NULL);
		}
	i++;
	}
}

int main()
{
	char	*s;
	char	**pipe;
//	s = "/bin/ls | /usr/bin/grep i";
	s = "/bin/cat | /bin/cat | /bin/ls";
//	s = "/bin/cat file | /usr/bin/grep bla | /usr/bin/more";
//	s = "/bin/ls filethatdoesnotexist | /usr/bin/grep bla | /usr/bin/more";

	pipe = ft_split(s, "|");
	t_m	m;
	m.pipe = pipe;
	print_comms(&m);
	ex_pipe(&m);
	ft_split_free(pipe);
	return (0);
}
