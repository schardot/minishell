# Minishell

## Overview
`minishell` is a simplified shell program implemented in C, designed to replicate core functionalities of the UNIX shell. This project is part of the 42 School curriculum and aims to provide a deeper understanding of system calls, process management, and shell behavior.

---

## Features
- **Execution of commands**: Supports both built-in commands and external binaries.
- **Environment variable management**: Export, unset, and modify environment variables.
- **Redirections**: Input (`<`), output (`>`), and append (`>>`) redirections.
- **Pipes (`|`)**: Create pipelines to connect commands.
- **Signal handling**: Handles `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` to mimic bash behavior.
- **Built-in commands**:
  - `cd`: Change directory.
  - `echo`: Print messages to standard output.
  - `pwd`: Print the current working directory.
  - `export`: Set environment variables.
  - `unset`: Remove environment variables.
  - `env`: Display environment variables.
  - `exit`: Exit the shell.

---

## Installation
### Prerequisites
- GCC or another C compiler
- `make`
- Linux operating system

### Build Instructions
1. Clone the repository:
   ```bash
   git clone https://github.com/schardot/minishell.git
   cd minishell
   ```
2. Build the executable:
   ```bash
   make
   ```
3. Run the shell:
   ```bash
   ./minishell
   ```

---

## Usage
Once the shell is running, you can type commands just as you would in a standard shell. Here are some examples:

```bash
# Running external binaries
ls -la

# Built-in commands
export MY_VAR=42
echo $MY_VAR
unset MY_VAR

# Using pipes and redirections
ls | grep minishell > output.txt
```

### Exiting the Shell
To exit `minishell`, type:
```bash
exit
```
Or use `Ctrl+D`.

---

## Error Handling
- Prints appropriate error messages for invalid commands or arguments.
- Handles edge cases like missing files, invalid syntax, and unsupported operations.

---

## Project Structure
```
minishell/
|-- src/              # Source code files
|-- include/          # Header files
|---- libft/          # Custom C library
|-- Makefile          # Build system
|-- README.md         # Project documentation
```

---

## Credits
Developed by [Elmira Kechedzhi](https://github.com/ekey13) and [Natália Schardosim](https://github.com/schardot) as part of the 42 School curriculum.

---

## License
This project is licensed under the [MIT License](LICENSE).
