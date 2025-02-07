# cleanup libft

### split
`ft_split(char *str, char delim)`

`ft_split_set(char *str, char *delim)`

`ft_split_quotes(char *str, char delim, int keep)`

or forget keep and make
`ft_trim_quotes(char *str)`


`ft_isquoted` its own function in libft
also `ft_split_trim_quotes`

### join
`strjoin strjoin_free strnjoin`
make strnjoin_free? join n strings and specify whichs to free?

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

- add alias like env_extra, unalias

- ignore line starting with #, is a comment

- ~~var='$val' needs to be expanded and trimmed of quotes~~ already did that?
- "export var" with no value does not add "var=" to env

- "which builtin" to show a list of builtins

- minishellrc, source


# parsing input

> The shell then parses these tokens into commands and other constructs, removes the special meaning of certain words or characters, expands others, redirects input and output as needed, executes the specified command, waits for the command’s exit status, and makes that exit status available for further inspection or processing.


- 1: split_quotes by '|'

- 2: split_quotes by ' '

- 3: cash_money

- 4: redirection

- 5: (last) trim quotes

```
bash-3.2$ haha=">file1"
bash-3.2$ echo $haha
>file1
bash-3.2$ echo "$haha"
>file1
bash-3.2$ echo "">file1""
bash-3.2$ echo ""$haha""
>file1
bash-3.2$ 
```
~~trim quotes twice??? before and after cashmoney?~~

nvm looks straightforward

## parsing redirection

```
bash-3.2$ echo hello>file1>file2
bash-3.2$ cat file1
bash-3.2$ cat file2
hello
```
this is super annoying, im gonna take the easy way out and say it only works when ">>" is in its own string
```
bash-3.2$ echo bye >> file1
bash-3.2$ echo < file1

bash-3.2$ cat << d << f
> qwe
> qwe
> d
> asd
> asd
> f
asd
asd
bash-3.2$ 
```

## other stuff

?

## taslkist

- libft
- rewrite minishell function without stupid norm variable
- add user@ to prompt
- review export (for "export var" with no val)
- add `which builtin`
- add `alias` and `unalias`
- add support for `#comments`
- add `source`