Program works as intended and laid out in the spec. Creates a daemon process that has a umask of 0,
creates a new session, closes and reroutes stdin, stdout, and stderr to /dev/null, handles the signals SIGTERM,
SIGUSR1, and SIGUSR2. The daemon uses forks and execv to spawn off mole processes (either 1 or 2 randomly) and 
uses send signals (SIGUSR1, SIGUSR2) to kill off moles. 

11/13 I began working on the project in the lab. Finished all but had errors with execv
11/14 figured out how to properly pass argv[0] to mole and stop the execv error