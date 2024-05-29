# Custom Shell in C

## Overview
This project involves creating a custom shell in C that supports various functionalities like system calls, directory navigation, process management, I/O redirection, piping, and more. The shell is modular and well-structured to avoid monolithic code.

## Features

### Part A: Basic System Calls

1. ### **Shell Prompt:**

   - Displays in the format `[username@systemname:current_directory]$`.
   - Dynamically retrieves the username and system name.
   - Reflects the current directory in the prompt.

2. ### **Input Parsing:**

   - Supports multiple commands separated by `;` or `&`.
   - Uses `strtok` to tokenize input.
   - Manages background processes using `fork` and `&`.

3. ### **warp Command:**

    usage: `warp [DIR_PATH]`

   - [DIR_PATH] can take the following values:
     - `~` - Home directory
     - `.` - Current directory
     - `..` - Parent directory
     - `-` - Previous directory
     - `<path>` - Absolute or relative path 

   - Changes directories with support for `~`, `.`, `..`, and `-`.
   - Prints the full path after changing directories.

4. ### **peek Command:**

    usage: `peek [OPTIONS]... [FILE_OR_DIR_PATH]`

    - [OPTIONS] can be:
      - `-a` - Show hidden files
      - `-l` - Detailed information
      - `-la` or `-al` - Detailed information with hidden files

    - [FILE_OR_DIR_PATH] can be:
      - `<path>` - Absolute or relative path

    - Lists files and directories.
    - Color codes files, directories, and executables.
    - green for executables, white for files and blue for directories

5. ### **pastevents Command:**

    usage: `pastevents` | `pastevents purge` | `pastevents execute <index>`

   - Maintains a history of the last 15 commands.
   - Stores history in a file for persistence.
   - Supports `pastevents purge` to clear history.
   - Supports `pastevents execute <index>` will Execute the command at that index position in pastevents.

6. ### **System Commands:**

    usage: `<command> [args]`

   - Uses `fork` and `execvp` to run system commands.
   - Handles foreground and background processes.
   - It is able to run multiple background processes.
   - Prints the time taken by long-running foreground processes.

7. ### **proclore Command:**
    
    usage: `proclore` | `proclore <PID>`

    ```
        Process Status:

            R/R+ : Running
            S/S+ : Sleeping in an interruptible wait
            Z : Zombie
    ```

   - The “+” signifies whether it is a foreground or background process, i.e., add “+” only if it is a foreground process.
   - where `<PID>` is the process ID of the process to be explored.
   - Displays process information.
   - Uses `/proc` filesystem to retrieve process details.

8. ### **seek Command:**

    usage: `seek [OPTIONS]... [FILE_OR_DIR_NAME] [DIR_PATH]`

    - [OPTIONS] can be:
      - `-d` - Search for directories
      - `-f` - Search for files
      - `-e` - This flag is effective only when a single file or a single directory with the name is found. 

    - [FILE_OR_DIR_NAME] can be:
      - `<name>` - Name of the file or directory to search

    - [DIR_PATH] can be:
        - `<path>` - Absolute or relative path

   - Searches for files and directories.
   - Traverses the directory tree to find matches.
   - Display files in green and directories in blue.

### Part B: Processes, Files, and Miscellaneous

1. ### **I/O Redirection:**
   - Implements input (`<`) and output (`>`, `>>`) redirection.
   - `>` : Outputs to the filename following “>”.
   - `>>` : Similar to “>” but appends instead of overwriting if the file already exists.
   - `<` : Reads input from the filename following “<”.
   - Both input and output redirections can be used on a single command
        - Example: `cat < input.txt > output.txt`
   - Uses `open`, `dup2`, and `close` system calls to manage file descriptors.

2. ### **Piping:**
    - <command> | <command> can be used to pipe the output of the command on the left side of the pipe to the command on the right side of the pipe.
    - Two or more commands can be chained together by piping
    - Piping can be used alongside input and output redirections
        - Example: `cat < input.txt | wc -l > lines.txt`
    - Note that in case of a conflict between taking input/output from the pipe or through a redirection, the redirection is given higher preference
        - Example: `cat in.txt | sort > out.txt | wc -l`
    - This shall output 0 since the sort command redirects the output to out.txt and not the pipe

3. **activities Command:**

    usage: `activities`

   - Displays the processes spawned by the shell which are either running or suspended.
   - This list will contain the following information about all processes :
        - Command Name
        - pid
        - state : running, stopped and finished
   - Tracks and displays all processes spawned by the shell.
   - Maintains process state (running or stopped).

4. **Signals:**

    usage: `ping <PID> <signal_number>` | `fg <PID>` | `bg <PID>`
   - Implements `ping` command to send signals to processes.
   - Handles `SIGINT`, `SIGQUIT`, and `SIGTSTP` for interrupting, quitting, and stopping processes.
   - `Ctrl - C`
        - Interrupt any currently running foreground process by sending it the SIGINT signal. It has no effect if no foreground process is currently running.
   - `Ctrl - D`
        - Log out of your shell (after killing all processes) while having no effect on the actual terminal.
   - `Ctrl - Z`
        - Push the (if any) running foreground process to the background and change it’s state from “Running” to “Stopped”. It has no effect on the shell if no foreground process is running.
   - Implements `fg` and `bg` to bring processes to foreground and background.

5. **neonate Command:**

    usage : `neonate -n [time_arg]`

    - [time_arg] can be:
        - `<time>` - Time in seconds for which the neonate process should sleep
    
    - The command prints the Process-ID of the most recently created process on the system   and this pid will be printed every [time_arg] seconds until the key `x` is pressed.



### Part C: Networking

1. **iMan Command:**

    usage: `iMan <command>`

   - Fetches and displays man pages from the internet.
   - Uses socket programming to connect to man.he.net.
   - Parses and displays the fetched man page content.

## Installation
To build and run the custom shell, follow these steps:

1. Clone the repository:
   ```sh
    git clone <repository_url>
    cd <repository_name>
    ```
2. Compile the source code:
    ```sh
    make
    ```
3. Run the custom shell:
    ```sh
    ./a.out
    ```

