# minishell

Welcome to **minishell**, a project for 42 School that involves building a simple Unix shell. This shell aims to replicate basic shell functionalities while introducing custom features and behaviors.

## Table of Contents

1. [Introduction](#introduction)  
2. [Features](#features)  
3. [Installation](#installation)  
4. [Usage](#usage)  
5. [Supported Commands](#supported-commands)  
6. [Limitations](#limitations)  
7. [Future Improvements](#future-improvements)  
8. [Credits](#credits)

---

## Introduction

**minishell** is a small-scale shell program written in C. It provides a simplified version of a Unix shell, handling common commands, environment variables, and basic shell scripting features. This project is part of the 42 School curriculum and serves as an introduction to system programming, process management, and parsing in C.

---

## Features

- **Prompt Display**: Displays a customizable prompt based on environment variables.  
- **Command Execution**: Supports execution of binaries in `$PATH`.  
- **Built-in Commands**: Includes implementations of basic shell built-ins like:
  - `cd`
  - `echo`
  - `env`
  - `exit`
  - `export`
  - `unset`  
- **Environment Variables**: Handles environment variables dynamically.  
- **Pipes and Redirections**: Supports input/output redirection and piping between commands.  
- **Signal Handling**: Graceful handling of `CTRL+C`, `CTRL+D`, and `CTRL+Z` signals.  
- **Error Management**: Provides user-friendly error messages for unsupported commands or syntax errors.  

---

## Installation

1. Clone this repository to your local machine:
   ```bash
   git clone https://github.com/yourusername/minishell.git
   cd minishell
   ```
2. Build the project:
   ```bash
   make
   ```
3. Run the shell:
   ```bash
   ./minishell
   ```

---

## Usage

1. Launch the shell using the `./minishell` command.  
2. Enter commands just like you would in a standard Unix shell.  
3. To exit, type `exit` or press `CTRL+D`.  

### Example Session

```shell
minishell$ echo Hello, world!
Hello, world!
minishell$ cd /tmp
minishell$ pwd
/tmp
minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
42
minishell$ exit
```

---

## Supported Commands

### Built-ins

- `echo`: Print arguments to the standard output.
- `cd`: Change the current directory.
- `pwd`: Print the current directory.
- `export`: Set or export environment variables.
- `unset`: Remove environment variables.
- `env`: Display all environment variables.
- `exit`: Exit the shell.

### Other Commands

Any executable present in the `$PATH` can be executed by minishell. For example, `ls`, `cat`, or `grep`.

---

## Limitations

- **No Job Control**: Background jobs (`&`) and job control commands like `fg`/`bg` are not supported.  
- **Incomplete Syntax Support**: Some advanced shell syntax, like subshells (`()`), is not implemented.  
- **Limited Error Handling**: While basic errors are managed, edge cases might not be handled perfectly.  

---

## Future Improvements

- Add support for logical operators (`&&`, `||`).  
- Implement advanced redirection features (`<<` for heredocs).  
- Expand test coverage for edge cases and unusual inputs.  
- Introduce support for scripting and configuration files.  

This project was developed as part of the **42 School curriculum**. Special thanks to the 42 community for their invaluable support and resources.

---

Enjoy using **minishell**, and happy coding! 🐚
