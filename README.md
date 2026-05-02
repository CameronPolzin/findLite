# findLite

A simplified version of the Unix `find` command implemented in C. 
Recursively searches directories and prints files that match a given pattern.

---

## Features

- Recursive directory traversal
- Wildcard pattern matching:
  - `*.txt` -> match files ending with `.txt`
  - `test*` -> match files starting with `test`
- Case-insensitive search
- Skips hidden files and system entries (`.` and `..`)
- Robust error handling for file system operations

---

## Technologies Used

- C
- POSIX system calls (`opendir`, `readdir`, `stat`)

---

## Installation
### Using GCC
`gcc findlite.c -o findLite`
### Using Makefile
`make`

---

## Usage
./findLite 'directory' 'pattern'
### Pattern Rules
- The pattern must contain exactly one `*`
- The `*` can only be used at the beginning or the end
#### Supported Formats
- `*.txt` -> matches all files that end with `.txt` 
- `test*` -> matches all files that start with `test`
- `*` -> matches all files in the directory 

---

## Example
```bash
# Search the current Directory for all '.txt' files 
./findLite ./ "*.txt"

# Search the current Directory for all '.c' files 
./findLite ./ "*.c"

# Search the current directory for all files that start with 'test'
./findLite ./ "test*"

# Search the directory 'src' for all files
./findLite ./src "*"
```

### Real Output Code using this repo
```bash
# Using make to compile the code
polzi@CamsDesktop:/mnt/c/Users/polzi/.vscode/GitHubRepos/findLite$ make
>gcc -Wall -Wextra -std=c99 findlite.c -o findLite
```
```bash
# Search the current directory for all files
polzi@CamsDesktop:/mnt/c/Users/polzi/.vscode/GitHubRepos/findLite$ ./findLite ./ "*"
>./Directory1
>./Directory1/dobby1.jpg
>./Directory1/dobby2.png
>./Directory1/test.txt
>./Directory2
>./Directory2/dobby1.jpg
>./Directory2/dobby2.png
>./Directory2/test.txt
>./findLite
>./findLite.c
>./Makefile
>./README.md
```
```bash
# Search the current Directory for all '.txt' files
polzi@CamsDesktop:/mnt/c/Users/polzi/.vscode/GitHubRepos/findLite$ ./findLite ./ "*.txt"
>./Directory1/test.txt
>./Directory2/test.txt
```
```bash
# Search Directory1 for all '.txt' files
polzi@CamsDesktop:/mnt/c/Users/polzi/.vscode/GitHubRepos/findLite$ ./findLite ./Directory1 "*.txt"
>./Directory1/test.txt
```
```bash
# Search Directory1 for all files 
polzi@CamsDesktop:/mnt/c/Users/polzi/.vscode/GitHubRepos/findLite$ ./findLite ./Directory1 "*"
>./Directory1/dobby1.jpg
>./Directory1/dobby2.png
>./Directory1/test.txt
``` 
