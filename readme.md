# cleanup libft

```c
ft_split(char *str, char delim)
```

```c
ft_split_set(char *str, char *delim)
```

```c
ft_split_quotes(char *str, char delim, int keep)
```
or forget keep and make
```c
ft_trim_quotes(char *str)
```

`strjoin strjoin_free strnjoin`
make strnjoin_free? join n strings and specify whichs to free?

# better structure for minishell

> The shell then parses these tokens into commands and other constructs, removes the special meaning of certain words or characters, expands others, redirects input and output as needed, executes the specified command, waits for the command’s exit status, and makes that exit status available for further inspection or processing.

- think smarter about funny norm names

- rethink file structure, make it easy to follow down function calls

- look into bash redirection

    maybe i was wrong with my assumption that it applies to the pipeline as a whole

    maybe each command has its own redirection info

    then i need a better way to split

    maybe a different structure, maybe a list

- think about how piping works

    is it easy to modify? debug? visualize?

- with that done maybe i can do !! properly

- add debug and cute options

- add alias like env_extra, unalias

- ignore line starting with #, is a comment

- var='$val' needs to be expanded and trimmed of quotes

- "which builtin" to show a list of builtins

- minishellrc, source
