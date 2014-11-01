Project currently functions as expected and described by the lab requirements.
The process accepts one integer from the command line, n, and forks off n processes as philosophers; all of 
which are set up under the same process group.
N unnamed semaphores are created for the chopsticks between philosophers and one chopstick gate semaphore is 
created to safeguard the critical section where deadlock may occur between processes.
A signal handler is set up for the launch-philosophers process and separate signal handlers are set up for 
each philosopher to handle when SIGTERM is sent to the process group.

10/28 wrote launch-philosophers script and began debugging
10/31 finished debugging