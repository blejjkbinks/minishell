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

# better structure for minishell

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
