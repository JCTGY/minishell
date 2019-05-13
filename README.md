

Minishell
===
![](minishell.gif)
[bonus](#bonus)
## Objective
Minishell is the very first buble of the shell branch. We will recreate a simple shell. Later on at 21sh and 42sh, we will add more function to it.

## How to use

```
cd ~
git clone https://github.com/JCTGY/minishell.git minishell
cd minishell
make
./minishell
```

Allow Funtion
---
* malloc, free
* access
* open, close, read, write
* opendir, readdir, closedir
* getcwd, chdir
* stat, lstat, fstat
* fork, execve
* wait, waitpid, wait3, wait4
* signal, kill
* exit

Mandatory
---
* Can only use C
* No memory leaks
* Mini UNIX command interpreter.
* Manage the errors without using `errno`, by displaying a message adapted to the error output.
* You must deal correctly with the PATH and the environment (copy of system char **environ).
* Implement a series of builtins: 
  * `echo`
  * `cd`
  * `setenv`
  * `unsetenv`
  * `env`
  * `exit`

Bonus
---
* Signal management
* PATH's right management
* Multiple commands

