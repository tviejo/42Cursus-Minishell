
# Minishell

![Minishell Banner](screenshots/begin.png)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
  - [Basic Functions](#basic-functions)
  - [Builtins](#builtins)
  - [Bonus Features](#bonus-features)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
  - [Executing a Simple Command](#executing-a-simple-command)
  - [Using Builtins](#using-builtins)
  - [Changing Directory](#changing-directory)
  - [Redirections and Pipes](#redirections-and-pipes)
  - [Handling Signals](#handling-signals)
  - [Bonus Features Examples](#bonus-features-examples)
- [Authors](#authors)

## Introduction

**Minishell** is a project developed by [tviejo](https://github.com/tviejo) and [ade-sarr](https://github.com/ade-sarr) as part of the curriculum at School 42. The goal of this project is to create a miniature version of the Unix shell, replicating essential functionalities of **bash** with a focus on POSIX compliance. Minishell allows users to execute commands, handle input/output redirections, manage environment variables, and more, providing a foundational understanding of shell operations.

## Features

### Basic Functions

- **Redirections**
  - Output Redirection: `>`
  - Append Redirection: `>>`
  - Heredoc: `<<`
- **Pipes**
  - Chain commands using `|`
- **Quotes Handling**
  - Double Quotes: `" "`
  - Single Quotes: `' '`
- **Error Handling**
  - Return values using `$?`
- **Environment Variables**
  - Access and modify environment variables
- **Signal Handling**
  - `Ctrl+D` to exit
  - `Ctrl+C` to interrupt
  - `Ctrl+\` to quit

### Builtins

- **echo**
  - Usage: `echo [-n] [string ...]`
  - Supports the `-n` option to omit the trailing newline
- **cd**
  - Usage: `cd [directory]`
  - Supports only relative or absolute paths
- **pwd**
  - Usage: `pwd`
  - Prints the current working directory
- **export**
  - Usage: `export [variable]`
  - Adds or modifies environment variables
- **unset**
  - Usage: `unset [variable]`
  - Removes environment variables
- **env**
  - Usage: `env`
  - Displays all environment variables
- **exit**
  - Usage: `exit`
  - Exits the shell

### Bonus Features

- **Logical Operators**
  - AND: `&&`
  - OR: `||`
- **Subshells**
  - Usage: `()`
  - Execute commands in a subshell
- **Wildcards**
  - Support for wildcard characters like `*` and `?`

## Installation

To install and set up Minishell on your local machine, follow these steps:

1. **Clone the Repository**

   ```bash
   git clone https://github.com/tviejo/42Cursus-Minishell.git
   ```

2. **Navigate to the Project Directory**

   ```bash
   cd minishell
   ```

3. **Compile the Project**

   Ensure you have `make` and a compatible C compiler installed.

   ```bash
   make
   ```

   This will generate the `minishell` executable.

## Usage

Run Minishell by executing the compiled binary:

```bash
./minishell
```

Once inside the shell, you can start typing commands as you would in a standard bash shell.

### Exiting Minishell

- Press `Ctrl+D` or type `exit` to exit the shell.

## Features

### Basic Functions

- **Redirections**
  - Output Redirection: `>`
  - Append Redirection: `>>`
  - Heredoc: `<<`
- **Pipes**
  - Chain commands using `|`
- **Quotes Handling**
  - Double Quotes: `" "`
  - Single Quotes: `' '`
- **Error Handling**
  - Return values using `$?`
- **Environment Variables**
  - Access and modify environment variables
- **Signal Handling**
  - `Ctrl+D` to exit
  - `Ctrl+C` to interrupt
  - `Ctrl+\` to quit

### Builtins

- **echo**
  - Usage: `echo [-n] [string ...]`
  - Supports the `-n` option to omit the trailing newline
- **cd**
  - Usage: `cd [directory]`
  - Supports only relative or absolute paths
- **pwd**
  - Usage: `pwd`
  - Prints the current working directory
- **export**
  - Usage: `export [variable]`
  - Adds or modifies environment variables
- **unset**
  - Usage: `unset [variable]`
  - Removes environment variables
- **env**
  - Usage: `env`
  - Displays all environment variables
- **exit**
  - Usage: `exit`
  - Exits the shell

### Bonus Features

- **Logical Operators**
  - **AND (`&&`)**
    - Executes the next command only if the previous command succeeds.
    - **Example:** `mkdir new_folder && cd new_folder`
  - **OR (`||`)**
    - Executes the next command only if the previous command fails.
    - **Example:** `cd nonexistent_folder || echo "Failed to change directory"`
- **Subshells (`()`)**
  - Groups commands to control execution flow and manage scope.
  - Executes commands within a subshell, isolating their environment.
  - **Example:** `(cd /tmp && ls)`: Changes to `/tmp` and lists its contents without affecting the current shell's directory.
- **Wildcards**
  - Supports wildcard characters like `*` and `?` for pattern matching.
  - **`*`**: Matches any number of characters.
    - **Example:** `ls *.txt` lists all `.txt` files in the current directory.
  - **`?`**: Matches exactly one character.
    - **Example:** `ls file?.c` matches `file1.c`, `file2.c`, etc., but not `file10.c`.

## Authors

- **tviejo** - [tviejo](https://github.com/tviejo)
- **ade-sarr** - [ade-sarr](https://github.com/ade-sarr)


```

---