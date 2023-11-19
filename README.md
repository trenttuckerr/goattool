# GoatTool

GoatTool is a command-line utility designed to assist users in exploring and understanding the file system of their Unix-like operating systems. It offers various operations, including printing file contents, searching for specific strings, printing file sizes, merging files, compressing and decompressing files in the .goat format, displaying file permissions, moving files, and providing a help page. With its straightforward interface and an array of essential operations, GoatTool simplifies the management of files and provides insights into your file system.

## How to Compile

```bash
gcc file_operations.c text_operations.c main.c -o goattool
```

## How to Run
Certainly! Here's the complete markdown text for GoatTool's README.md file:

markdown

# GoatTool

GoatTool is a command-line utility designed to assist users in exploring and understanding the file system of their Unix-like operating systems. It offers various operations, including printing file contents, searching for specific strings, printing file sizes, merging files, compressing and decompressing files in the .goat format, displaying file permissions, moving files, and providing a help page. With its straightforward interface and an array of essential operations, GoatTool simplifies the management of files and provides insights into your file system.

# Author
Trent Tucker

## How to Compile

```bash
gcc file_operations.c text_operations.c main.c -o goattool
```

## How to Run

```bash
Usage: ./goattool [switch] [arguments]
Switches:
-p, --print <file>                 Print the contents of one or more files.
-s, --search <file> <string>       Search a file for a particular string and print every line of the file that contains that string.
-z, --size <file>                  Print the size of one or more files.
-m, --merge <output-file> <files>  Merge multiple files into a single file with a specified name and path.
-c, --compress <file>              Compress a text file into the .goat format.
-d, --decompress <file>            Decompress a .goat file to retrieve the original text.
-rwx, --permissions <file>         Print the permissions of one or more files as an integer (000 to 777).
-mv, --move <source> <destination> Move a file from one place to another with a specified path and new name.
-h, --help                         Print a help page.

Examples:
> ./goattool -s file.txt password
> ./goattool -mv writing.txt ~/dev/new.txt
> ./goattool -m ~/projects/project.txt part1.txt part2.txt
...
```

