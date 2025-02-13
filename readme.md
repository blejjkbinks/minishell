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

- ~~2: split_quotes by ' '~~

- 3: redirection first

- 4: cash_money after

- 5: split ' '

- ~~5~~ 6: (last) trim quotes
```
bash-3.2$ mm=asd
bash-3.2$ cat << $mm
> asd
> $mm
asd
bash-3.2$ 
```

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

bash-3.2$ cat << d << f > file1 | tr a b > file2
> asd
> asd
> d
> axc
> axc
> f
bash-3.2$ cat file1
axc
axc
bash-3.2$ cat file2
bash-3.2$ cat << d << f | tr a b > file2
> asd
> d
> axc
> f
bash-3.2$ cat file2
bxc
bash-3.2$ 
```
redirection in the first pipe (to file1) snatches it from tr

```
bash-3.2$ echo asd > file
bash-3.2$ cat file
asd
bash-3.2$ cat file | tr a b > file
bash-3.2$ cat file
bash-3.2$ echo asd > file
bash-3.2$ cat file | tr a b
bsd
```
order for opening "file"??? 
```
bash-3.2$ echo asd > file
bash-3.2$ cat < file | tr a b >> file
bash-3.2$ cat file
asd
bsd
bash-3.2$ 
```

## other stuff


ctrl+d message in main

unclosed quote message

handle and show errors:( for too many arguments, like pwd and var=val and env

## taslkist

- ~~libft~~ ^^
- ~~rewrite minishell function without stupid norm variable~~ yuh
- ~~add user@ to prompt~~ done
- ~~review export (for "export var" with no val)~~ done
- ~~add `which builtin`~~ nvm ugly
- ~~add `alias` and `unalias`~~ done
- add support for `#comments`
- add `source`
- fix readline lib on laptop
- check git branch in parents
- "alias name" shows name=alias or name not found

### flow

> redir first apparently...... !?!?!?!
- find_redir
- open_redir
- cash_money (with alias and #)
- ready_pipe
- clean_pipe

### ugh

- FIX SPLIT_QUOTES
- backtrack input line with only whitespaces
- ALIAS MAGIC NEEDS WORK
- also add recursion
```
bash-3.2$ asd=qwe zxc=ggg
bash-3.2$ echo $asd $zxc
qwe ggg
```
- random position in export, with a hash?? (maybe combine env_name and env_namelen, need room for 1 function to do this)
  not as simple as swap(last, random), need to move+1 all starting from rand
- ~~HEAP CORRUPTION LMAO~~ godbless

# priority-> whitespace, split_quotes, alias_magic
## redir
go through

if not quoted and '>' or '<'

if next is '>' or '<' change mode, if next is opposite '<' '>' invalid

if next next is also "><" invalid

if valid find next word, ended by unquoted space or next "><"

strdup it, open with mode, memmove (strlen(arg) + skipped + 1(null terminator of string))

## cash_money
already done, just need to add alias

