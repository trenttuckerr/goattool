# goattool

goattool is a command-line utility designed to assist users in exploring and understanding the file system of their Unix-like operating systems.

# author
Trent 

## how to compile

```bash
goattool user$ gcc file_operations.c text_operations.c main.c -o goattool
```

## how to run

```bash
Usage: ./goattool [switch] [arguments]
Switches:
-p, --print <file-path>                 Print the contents of one or more files.
-s, --search <file-path> <string>       Search a file for a particular string and print every line of the file that contains that string.
-z, --size <file-path>                  Print the size of one or more files.
-m, --merge <output-file-path> <files>  Merge multiple files into a single file with a specified name and path.
-c, --compress <file-path>              Compress a text file into the .goat format.
-d, --decompress <file-path>            Decompress a .goat file to retrieve the original text.
-rwx, --permissions <file-path>         Print the permissions of one or more files as an integer (000 to 777).
-mv, --move <source-path> <destination-path> Move a file from one place to another with a specified path and new name.
-h, --help                         Print a help page.

Examples:
> ./goattool -s file.txt password
> ./goattool -mv writing.txt ~/dev/new.txt
> ./goattool -m ~/projects/project.txt part1.txt part2.txt
...
```

## how to Test
```bash
goattool user$ ./runner.sh
```
After the run of this command, you will see a generated file called runner_output.txt. Here you can find the results of the tests.
```bash
goattool user$ cat runner_output.txt
```
