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



int main()
{
	char	*s;
	char	**line;
	char	**redir_in;
	char	**redir_out;

//	s = "/bin/ls | /usr/bin/grep i";
	s = "/bin/cat | /bin/cat | /bin/ls";
//	s = "/bin/cat file | /usr/bin/grep bla | /usr/bin/more";
//	s = "/bin/ls filethatdoesnotexist | /usr/bin/grep bla | /usr/bin/more";
	line = ft_split(s, "|");

	redir_in = 

	print_comms(line);
	exec_pipe(line);

	ft_split_free(line);
	return (0);
}