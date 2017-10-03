ush
=====
Ulises's shell

Description
----------------
This program is a basic shell that propmpts the user and executes commands if it finds them. The following features have been implemented for this project:

- Commands with some or none parameters
- Commands with full or no pathname
- One or more pipes
- Background proceses
- Changing directory (cd)

All of these features have been tested in interactive mode. However, changing directory and background do not pass the test in [testShell.sh](testshell.sh).

This shell starts in the HOME directory, taken from the environment.

usage
----------------
In order to build the project, navigate to the shell directory and run

`$make`

To run simply enter `$./ush` 

Acknowledgments
---------------
I developed this shell on my own using the linux manual pages for system calls [pipe](http://man7.org/linux/man-pages/man2/pipe.2.html), [dup](http://man7.org/linux/man-pages/man2/dup.2.html), [dup2](http://man7.org/linux/man-pages/man2/dup2.2.html), [close](http://man7.org/linux/man-pages/man2/close.2.html), [execve](http://man7.org/linux/man-pages/man2/execve.2.html), [fork](http://man7.org/linux/man-pages/man2/fork.2.html), [getcwd](http://man7.org/linux/man-pages/man2/getcwd.2.html), [stat](http://man7.org/linux/man-pages/man2/stat.2.html), [waitpid](http://man7.org/linux/man-pages/man2/waitpid.2.html)

I also helped the following students with their labs:

- Ana Jaqueline
- Kimberly Kato
- Manuel Yanez
- Daner Pacheco