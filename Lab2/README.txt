Launch.c correctly forks off a child and uses execve to execute command given in argv[1]

Tube.c correctly sets up a pipe, forks off 2 children, rewires stdin and stdout to the pipe using dup2,
has the first child execute the first command, pipes the output of the first child into the input of the 
second child, and the second child executes the second command using the output of the first child.

9/16 completed launch.c
9/18 changed format of print in launch.c, finished half of tube.c
9/21 completed tube.c and makefile