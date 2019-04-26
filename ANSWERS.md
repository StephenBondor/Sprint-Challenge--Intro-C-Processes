**1. List all of the main states a process may be in at any point in time on a
standard Unix system. Briefly explain what each of these states means.**

1. Running: The process is either in running or ready to run.
1. Waiting: The process is waiting for an event or for a resource.
1. Stopped: Halted from receiving a call or from reaching the end of its
   execution.
1. Zombie: The process is dead but the information is still available in the
   process table.

**2. What is a zombie process?**

-   Zombie: A dead process that has not yet been cleaned up.

**3. How does a zombie process get created? How does one get destroyed?**

-   By calling the creation of a process, then terminating it. It is a zombie
    before it is trashed.

**4. What are some of the benefits of working in a compiled language versus a
non-compiled language? More specifically, what benefits are there to be had from
taking the extra time to compile our code?**

-   It doesnt need anything to help it run, it can run on its' own. It usually
    runs faster as there is less obfuscation.
