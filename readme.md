```
blejj@blejjs-MacBook-Pro ~ % echo $SHLVL
1
blejj@blejjs-MacBook-Pro ~ % bash

The default interactive shell is now zsh.
To update your account to use zsh, please run `chsh -s /bin/zsh`.
For more details, please visit https://support.apple.com/kb/HT208050.
bash-3.2$ echo $SHLVL
2
bash-3.2$ bash

The default interactive shell is now zsh.
To update your account to use zsh, please run `chsh -s /bin/zsh`.
For more details, please visit https://support.apple.com/kb/HT208050.
bash-3.2$ echo $SHLVL
3
bash-3.2$ exit
exit
bash-3.2$ echo $SHLVL
2
bash-3.2$ cd minishell/
bash-3.2$ ls
Makefile	header		libft		minishellrc	src
bash-3.2$ mm=asd
bash-3.2$ echo $mm
asd
bash-3.2$ cat << $mm
> asd
> mm
> $mm
asd
mm
bash-3.2$ echo $?
0
bash-3.2$ haha=">file"
bash-3.2$ echo $haha
>file
bash-3.2$ echo "$haha"
>file
bash-3.2$ echo ""$haha""
>file
bash-3.2$ echo "">file""
bash-3.2$ ls | grep file
Makefile
file
bash-3.2$ rm file
bash-3.2$ echo $?
0
bash-3.2$ echo hello>file1>file2
bash-3.2$ cat file1
bash-3.2$ cat file2
hello
bash-3.2$ echo $?
0
bash-3.2$ cat << d << f > file1 | tr a b > file2
> asd
> asd
> d
> axc
> axc
> f
bash-3.2$ cat file1
qwe
qwe
bash-3.2$ cat file2
bash-3.2$ cat << d << f | tr a b > file2
> asd
> asd
> d
> afff
> asdf
> f
bash-3.2$ cat file2
bfff
bsdf
bash-3.2$ echo $?
0
bash-3.2$ echo asd > file
bash-3.2$ cat file
asd
bash-3.2$ cat file | tr a b > file
bash-3.2$ cat file
bash-3.2$ echo asd > file
bash-3.2$ cat file | tr a b >> file
bash-3.2$ cat file
asd
bsd
bash-3.2$ cat < file | tr a b >> file
bash-3.2$ cat file
asd
bsd
bsd
bsd
bash-3.2$ <file tr b x >> file
bash-3.2$ cat file
asd
bsd
bsd
bsd
asd
xsd
xsd
xsd
bash-3.2$ echo $?
0
bash-3.2$ qwe=123 asd=456
bash-3.2$ echo $qwe $asd
123 456
bash-3.2$ echo "cat lol.c | cat>lol.c"
cat lol.c | cat>lol.c
bash-3.2$ expr $? + $?
0
bash-3.2$ ls
Makefile	file1		header		minishellrc
file		file2		libft		src
bash-3.2$ /bin/ls
Makefile	file1		header		minishellrc
file		file2		libft		src
bash-3.2$ unset PATH; ls
bash: ls: No such file or directory
bash-3.2$ /bin/ls
Makefile	file1		header		minishellrc
file		file2		libft		src
bash-3.2$ exit
exit
blejj@blejjs-MacBook-Pro ~ % bash

The default interactive shell is now zsh.
To update your account to use zsh, please run `chsh -s /bin/zsh`.
For more details, please visit https://support.apple.com/kb/HT208050.
bash-3.2$ ls
Applications	Downloads	Music		Templates
Desktop		Library		Pictures	minishell
Documents	Movies		Public
bash-3.2$ cd minishell/
bash-3.2$ echo $USER
rdomange
bash-3.2$ echo "$USER"
rdomange
bash-3.2$ echo '$USER'
$USER
bash-3.2$ ./src
bash: ./src: is a directory
bash-3.2$ src
bash: src: command not found
bash-3.2$ /asd
bash: /asd: No such file or directory
bash-3.2$ cat | cat | ls
Makefile	file1		header		minishellrc
file		file2		libft		src


bash-3.2$ cat << asd
> a
> as
> asdf
> asd
a
as
asdf
bash-3.2$ echo $?
1
bash-3.2$ cat << asd
> ctrlc
> 
bash-3.2$ echo $?
1
bash-3.2$ cat << asd
> ctrld
> ctrld
bash-3.2$ echo $?
0
bash-3.2$ 
```

```
$minishell$ blejj@ ./minishell (main) :3 $ echo asd | | echo asd
minishell: invalid token '|'
$minishell$ blejj@ ./minishell (main) :( $ echo asd | 
minishell: invalid token '|'
$minishell$ blejj@ ./minishell (main) :( $  | echo asd
minishell: invalid token '|'
$minishell$ blejj@ ./minishell (main) :( $ | echo asd
minishell: invalid token '|'
$minishell$ blejj@ ./minishell (main) :( $ echo $?
1
$minishell$ blejj@ ./minishell (main) :3 $ echo <
minishell: invalid token >< >:(
```

heredoc testing

ctrl+c with buffer

ctrl+c at beginning of line

ctrl+d with buffer

ctrl+d at beginning of line