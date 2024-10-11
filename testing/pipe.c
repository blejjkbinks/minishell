#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "../libft/header/libft.h"

void	ex_pipe(char **pipe)
{
	
}

int main()
{
	char	*s;
	char	**pipe, **comm;
//	s = "/bin/ls | /usr/bin/grep i";
	s = "/bin/cat | /bin/cat | /bin/ls";
//	s = "/bin/cat file | /usr/bin/grep bla | /usr/bin/more";
//	s = "/bin/ls filethatdoesnotexist | /usr/bin/grep bla | /usr/binmore"

	pipe = ft_split(s, "|");
	for (int i = 0; p[i]; i++)
	{
		comm = ft_split(p[i], " ");
		for (int j = 0; c[j]; j++)
		{
			printf("%s", c[j]);
			if (c[j + 1])
				printf(",");	
		}
		ft_split_free(comm);
		printf(";\n");
	}
	ex_pipe(pipe);
	ft_split_free(pipe);
	return (0);
}
