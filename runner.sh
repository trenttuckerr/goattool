#!/bin/bash

# Redirect all output to a file
exec > runner_output.txt
exec 2>&1

# Compile project
# make -f Makefile

echo -e "Welcome to the testing Bash script for goattool\n"

echo -e "Tests for Operation 1: Print the contents of one or more files\n"

echo -e "Test 1 -"
echo -e "\texample.txt:\nThis is an example file."
echo -e "\tInput:\n./goattool -p example_file.txt"
echo -e "\tExpected Output:\n"Contents of file: example_file.txt""
echo -e "This is an example file."
echo -e "\tReceived Output: \n$(./goattool -p example_file.txt)\n"

echo -e "Test 2 - \n"
echo -e "Input:\n./goattool -p non_existent_file.txt"
echo -e "Error: The file 'non_existent_file.txt' does not exist."
echo -e "Received Output:"
echo -e "$(./goattool -p non_existent_file.txt)"
echo -e "=====================\n"

echo -e "Test 3 - \n"
echo -e "file1.txt: Hello"
echo -e "file2.txt: World"
echo -e "Input:\n./goattool -p file1.txt file2.txt"
echo -e "Expected Output:"
echo -e "Contents of file: file1.txt"
echo -e "Hello"
echo -e "====================="
echo -e "Contents of file: file2.txt"
echo -e "World"
echo -e "Received Output:"
echo -e "$(./goattool -p file1.txt file2.txt)\n"

echo -e "Test 4 - \n"
echo -e "Input: ./goattool -p"
echo -e "Expected Output:"
echo -e "Usage: ./goattool -p/--print <files>"
echo -e "Received Output:"
echo -e "$(./goattool -p)"
echo -e "=====================\n"

echo -e "Test 5 -  "
echo -e "example_file.txt: This is an example file."
echo -e "Input: ./goattool -p example_file.txt non_existent_file.txt"
echo -e "Expected Output:"
echo -e "Contents of file: example_file.txt"
echo -e "This is an example file."
echo -e "====================="
echo -e "Error: The file 'non_existent_file.txt' does not exist."
echo -e "Received Output:"
echo -e "$(./goattool -p example_file.txt non_existent_file.txt)\n"

echo -e "Tests for Operation 2: Search a file for a particular string\n"

echo -e "Test 6 - \n"
echo -e "example_file.txt: This is an example file."
echo -e "Input: ./goattool -s example_file.txt example"
echo -e "Expected Output:"
echo -e "String found in file!"
echo -e "Line containing text: This is an example file."
echo -e "Received Output:"
echo -e "$(./goattool -s example_file.txt example)\n"
echo -e "=====================\n"

echo -e "Test 7 - \n"
echo -e "example_file.txt: This is an example file."
echo -e "Input: ./goattool -s example_file.txt string_not_in_file"
echo -e "Expected Output:"
echo -e "String 'string_not_in_file' not found in the file."
echo -e "Received Output:"
echo -e "$(./goattool -s example_file.txt string_not_in_file)\n"
echo -e "=====================\n"

echo -e "Test 8 - \n"
echo -e "Input: ./goattool -s non_existent_file.txt search_string"
echo -e "Expected Output:"
echo -e "Error opening file: non_existent_file.txt"
echo -e "Received Output:"
echo -e "$(./goattool -s non_existent_file.txt search_string)"
echo -e "=====================\n"

echo -e "Test 9 - \n"
echo -e "Input: ./goattool -s example_file.txt"
echo -e "Expected Output:"
echo -e "Usage: ./goattool -s/--search <file> <string>"
echo -e "Received Output:"
echo -e "$(./goattool -s example_file.txt)"
echo -e "=====================\n"

echo -e "Test 10 - \n"
echo -e "Input: ./goattool -s"
echo -e "Expected Output:"
echo -e "Usage: ./goattool -s/--search <file> <string>"
echo -e "Received Output:"
echo -e "$(./goattool -s)"
echo -e "=====================\n"

echo -e "Tests for Operation 3: Print the size of one or more files\n"

echo -e "Test 11 - \n"
echo -e "example_file.txt: This is an example file. (24 bytes in size)"
echo -e "Input: ./goattool -z example_file.txt"
echo -e "Expected Output:"
echo -e "File: example_file.txt, Size: 24 bytes"
echo -e "Received Output:"
echo -e "$(./goattool -z example_file.txt)"
echo -e "=====================\n"

echo -e "Test 12 - \n"
echo -e "Input: ./goattool -z non_existent_file.txt"
echo -e "Expected Output:"
echo -e "Error getting file size.: No such file or directory"
echo -e "Received Output:"
echo -e "$(./goattool -z non_existent_file.txt)"
echo -e "=====================\n"

echo -e "Test 13 - \n"
echo -e "example_file.txt: This is an example file. (24 bytes in size)"
echo -e "Input: ./goattool -z example_file.txt non_existent_file.txt"
echo -e "Expected Output:"
echo -e "Error getting file size.: No such file or directory"
echo -e "File: example_file.txt, Size: 24 bytes"
echo -e "Received Output:"
echo -e "$(./goattool -z example_file.txt non_existent_file.txt)"
echo -e "=====================\n"

echo -e "Test 14 - \n"
echo -e "Input: ./goattool -z"
echo -e "Expected Output:"
echo -e "Usage: ./goattool -z/--size <files>"
echo -e "Received Output:"
echo -e "$(./goattool -z)"
echo -e "=====================\n"

echo -e "Test 15 - \n"
echo -e "file1.txt: Hello (5 bytes in size)"
echo -e "file2.txt: World (5 bytes in size)"
echo -e "Input: ./goattool -z file1.txt file2.txt"
echo -e "Expected Output:"
echo -e "File: file1.txt, Size: 5 bytes"
echo -e "File: file2.txt, Size: 5 bytes"
echo -e "Received Output:"
echo -e "$(./goattool -z file1.txt file2.txt)"
echo -e "=====================\n"

echo -e "Operation 4: Merge multiple files into a single file\n"

touch "merged_file.txt"

echo -e "Test 16 - \n"
echo -e "file1.txt: Hello"
echo -e "file2.txt: World"
echo -e "Input: ./goattool -m merged_file.txt file1.txt file2.txt"
echo -e "Expected Output:"
echo -e "merged_file.txt contents to be: \nHelloWorld || WorldHello (depending on thread chosen)"
echo -e "Received Output:"
echo -e "$(./goattool -m merged_file.txt file1.txt file2.txt)cat merged_file.txt"
echo -e "$(cat merged_file.txt)"
echo -e "=====================\n"

rm "merged_file.txt"

echo -e "Test 17 - \n"
echo -e "Input: ./goattool -m new_merge_file.txt non_existent_file.txt"
echo -e "Expected Output:"
echo -e "Error: Unable to open source file non_existent_file.txt"
echo -e "Received Output:"
echo -e "$(./goattool -m new_merge_file.txt non_existent_file.txt)"
echo -e "=====================\n"

echo -e "Test 18 - \n"
echo -e "Input: ./goattool -m new_merge_file.txt"
echo -e "Expected Output:"
echo -e "Usage: ./goattool -m/--merge <output-file> <files>"
echo -e "Received Output:"
echo -e "$(./goattool -m new_merge_file.txt)"
echo -e "=====================\n"

echo -e "Test 19 - \n"
echo -e "Input: ./goattool -m"
echo -e "Expected Output:"
echo -e "Usage: ./goattool -m/--merge <output-file> <files>"
echo -e "Received Output:"
echo -e "$(./goattool -m)"
echo -e "=====================\n"

echo -e "Test 20 - \n"
echo -e "empty.txt:"
echo -e "Input: ./goattool -m empty_merge.txt empty.txt"
echo -e "Expected Output:"
echo -e "empty_merge.txt contents to be: (nothing at all)"
echo -e "Received Output: $(./goattool -m empty_merge.txt empty.txt)"
echo -e "cat empty_merge.txt (nothing is found in empty_merge.txt)"
echo -e "$(cat empty_merge.txt)"
echo -e "=====================\n"

echo -e "Operation 5: Compress a file into the .goat format\n"

echo -e "Test 21 - \n"
echo -e "example_file.txt: This is an example file."
echo -e "Input: ./goattool -c example_file.txt"
echo -e "Expected Output:"
echo -e ".goat compression completed"
echo -e ".goat file: example_file.goat"
echo -e "example.goat contents to be:"
echo -e "T1h1i1s1 i1s1 a1n1 e1x1a1m1p1l1e1 f1i1l1e1.1"
echo -e "Received Output:"
echo -e "$(./goattool -c example_file.txt)"
echo -e "Contents of example_file.goat:"
echo -e "$(cat example_file.goat)"
echo -e "=====================\n"

echo -e "Test 22 - \n"
echo -e "Input: ./goattool -c non_existent_file.txt"
echo -e "Expected Output:"
echo -e "Error opening source file: No such file or directory"
echo -e "Received Output:"
echo -e "$(./goattool -c non_existent_file.txt)"
echo -e "=====================\n"

echo -e "Test 23 - \n"
echo -e "a_letters.txt: aaaaaaaaaaaa"
echo -e "Input: ./goattool -c a_letters.txt"
echo -e "Expected Output:"
echo -e ".goat compression completed"
echo -e ".goat file: a_letters.goat"
echo -e "example.goat contents to be:"
echo -e "a12"
echo -e "Received Output:"
echo -e "$(./goattool -c a_letters.txt)"
echo -e "Contents of a_letters.goat:"
echo -e "$(cat a_letters.goat)"
echo -e "=====================\n"



echo -e "Test 24 - \n"
echo -e "lots_of_ab.txt: aaaaaaaabbbaaaaabbbbbbbbbabaaaaaaaaaaa"
echo -e "Input: ./goattool -c lots_of_ab.txt"
echo -e "Expected Output:"
echo -e ".goat compression completed"
echo -e ".goat file: lots_of_ab.goat"
echo -e "example.goat contents to be:"
echo -e "a8b3a5b9a1b1a11"
echo -e "Received Output:"
echo -e "$(./goattool -c lots_of_ab.txt)"
echo -e "Contents of lots_of_ab.goat:"
echo -e "$(cat lots_of_ab.goat)"
echo -e "=====================\n"



echo -e "Test 25 - \n"
echo -e "Input: ./goattool -c"
echo -e "Expected Output:"
echo -e "Usage: ./goattool -c/--compress <file>"
echo -e "Received Output:"
echo -e "$(./goattool -c)"
echo -e "=====================\n"


echo -e "Operation 6: Decompress a .goat file\n"

echo -e "Test 26 - \n"
echo -e "example_file.goat: T1h1i1s1 i1s1 a1n1 e1x1a1m1p1l1e1.1"
echo -e "Input: ./goattool -d example_file.goat"
echo -e "Expected Output:"
echo -e "decompression saved into example_file.goat.decompressed.txt"
echo -e "example_file.goat.decompressed.txt contents to be:"
echo -e "This is an example file."
echo -e "Received Output:"
echo -e "$(./goattool -d example_file.goat)"
echo -e "cat example_file.goat.decompressed.txt"
echo -e "$(cat example_file.goat.decompressed.txt)"
echo -e "=====================\n"

echo -e "Test 27 - \n"
echo -e "Input: ./goattool -d non_existent_file.goat"
echo -e "Expected Output:"
echo -e "Error opening source .goat file: No such file or directory"
echo -e "Received Output:"
echo -e "$(./goattool -d non_existent_file.goat)"
echo -e "=====================\n"

echo -e "Test 28 - \n"
echo -e "Input: ./goattool -d"
echo -e "Expected Output:"
echo -e "Usage: ./goattool -d/--decompress <file>"
echo -e "Received Output:"
echo -e "$(./goattool -d)"
echo -e "=====================\n"

echo -e "Test 29 - \n"
echo -e "lots_of_ab.goat: a8b3a5b9a1b1a11"
echo -e "Input: ./goattool -d lots_of_ab.goat"
echo -e "Expected Output:"
echo -e "decompression saved into lots_of_ab.goat.decompressed.txt"
echo -e "lots_of_ab.goat.decompressed.txt contents to be:"
echo -e "aaaaaaaabbbaaaaabbbbbbbbbabaaaaaaaaaaa"
echo -e "Received Output:"
echo -e "$(./goattool -d lots_of_ab.goat)"
echo -e "cat lots_of_ab.goat.decompressed.txt"
echo -e "$(cat lots_of_ab.goat.decompressed.txt)"
echo -e "=====================\n"

echo -e "Test 30 - \n"
echo -e "Input: ./goattool -d sample.goat sample2.goat sample3.goat"
echo -e "Expected Output:"
echo -e "Usage: ./goattool -d/--decompress <file>"
echo -e "Received Output:"
echo -e "$(./goattool -d sample.goat sample2.goat sample3.goat)"
echo -e "=====================\n"

echo -e "Operation 7: Print the permissions of one or more files\n"

echo -e "Test 31 - \n"
echo -e "example_file.txt (Permissions 644): This is an example file."
echo -e "Input: ./goattool -rwx example_file.txt"
echo -e "Expected Output:"
echo -e "File: example_file.txt, Permissions: 644"
echo -e "Received Output:"
echo -e "$(./goattool -rwx example_file.txt)"
echo -e "=====================\n"

echo -e "Test 32 - \n"
echo -e "Input: ./goattool -rwx non_existent_file.txt"
echo -e "Expected Output:"
echo -e "Error getting file permissions: No such file or directory"
echo -e "Received Output:"
echo -e "$(./goattool -rwx non_existent_file.txt)"
echo -e "=====================\n"

echo -e "Test 33 - \n"
echo -e "Input: ./goattool -rwx"
echo -e "Expected Output:"
echo -e "Usage: ./goattool -rwx/--permissions <files>"
echo -e "Received Output:"
echo -e "$(./goattool -rwx)"
echo -e "=====================\n"

echo -e "Test 34 - \n"
echo -e "file1.txt (Permissions 644): Hello"
echo -e "file2.txt (Permissions 644): World"
echo -e "Input: ./goattool -rwx file1.txt file2.txt"
echo -e "Expected Output:"
echo -e "File: file1.txt, Permissions: 644"
echo -e "File: file2.txt, Permissions: 644"
echo -e "Received Output:"
echo -e "$(./goattool -rwx file1.txt file2.txt)"
echo -e "=====================\n"

echo -e "Test 35 - \n"
echo -e "file1.txt (Permissions 644): Hello"
echo -e "file2.txt (Permissions 644): World"
echo -e "Input: ./goattool -rwx file1.txt file2.txt non_existent_file.txt"
echo -e "Expected Output:"
echo -e "Error getting file permissions: No such file or directory"
echo -e "File: file1.txt, Permissions: 644"
echo -e "File: file2.txt, Permissions: 644"
echo -e "Received Output:"
echo -e "$(./goattool -rwx file1.txt file2.txt non_existent_file.txt)"
echo -e "=====================\n"

echo -e "Operation 8: Move a file from one place to another\n"

touch source_file.txt

echo -e "Test 36 - \n"
echo -e "source_file.txt is located on . directory"
echo -e "Input: ./goattool -mv source_file.txt destination_folder/renamed_file.txt"
echo -e "Expected Output:"
echo -e "File moved successfully from source_file.txt to destination_folder/renamed_file.txt"
echo -e "Received Output:"
echo -e "$(./goattool -mv source_file.txt destination_folder/renamed_file.txt)"
echo -e "=====================\n"

echo -e "Test 37 - \n"
echo -e "Input: ./goattool -mv non_existent_file.txt destination_folder/renamed_file.txt"
echo -e "Expected Output:"
echo -e "Error moving file: No such file or directory"
echo -e "Received Output:"
echo -e "$(./goattool -mv non_existent_file.txt destination_folder/renamed_file.txt)"
echo -e "=====================\n"

echo -e "Test 38 - \n"
echo -e "Input: ./goattool -mv example.txt non_existent_folder/renamed.txt"
echo -e "Expected Output:"
echo -e "Error moving file: No such file or directory"
echo -e "Received Output:"
echo -e "$(./goattool -mv example.txt non_existent_folder/renamed.txt)"
echo -e "=====================\n"

echo -e "Test 39 - \n"
echo -e "Input: ./goattool -mv"
echo -e "Expected Output:"
echo -e "Usage: ./goattool -mv/--move <source> <destination>"
echo -e "Received Output:"
echo -e "$(./goattool -mv)"
echo -e "=====================\n"

touch source_file.txt

echo -e "Test 40 - \n"
echo -e "Input: ./goattool -mv source_file.txt"
echo -e "Expected Output:"
echo -e "Usage: ./goattool -mv/--move <source> <destination>"
echo -e "Received Output:"
echo -e "$(./goattool -mv source_file.txt)"
echo -e "=====================\n"

echo -e "Operation 9: Printing the help page\n"

echo -e "Test 41 - \n"
echo -e "Input: ./goattool -h"
echo -e "Expected Output:"
echo "					Help Page

Overview: GoatTool is a CLI utility for exploring and
understanding Unix file systems. It includes operations
like printing file contents, searching for strings, file
sizes, merging files, compressing/decompressing in .goat
format, displaying file permissions, moving files, and
providing a help page. Simplifies file management and
offers insights into your file system.

Usage: ./goattool [switch] [arguments]

Switches:
  -p, --print <files>			Print contents of 1+ files.
  -s, --search <file> <str>			Search file for a string and
                                       print every line with string.
  -z, --size <files>			Print size of one or more files.
  -m, --merge <output> <files>			Merge files into a file
                                          with a name and path.
  -c, --compress <file>			Compress a text file to .goat.
                                   with a specified name and path.
  -d, --decompress <file>			Decompress a .goat file to get
                                     the original text.
  -rwx, --permissions <files>			Print permissions of
                                        files (000 to 777).
  -mv, --move <source> <dest>			Move a file from source
                                         path to destination path.
  -h, --help                 			Print a help page.

Examples:
> ./goattool -s file.txt password
> ./goattool -mv writing.txt ~/dev/new.txt
> ./goattool -m ~/projects/project.txt part1.txt part2.txt"
echo -e "Received Output:"
echo -e "$(./goattool -h)"
echo -e "=====================\n"

echo -e "Test 42 - \n"
echo -e "Input: ./goattool"
echo -e "Expected Output:"
echo "					Help Page

Overview: GoatTool is a CLI utility for exploring and
understanding Unix file systems. It includes operations
like printing file contents, searching for strings, file
sizes, merging files, compressing/decompressing in .goat
format, displaying file permissions, moving files, and
providing a help page. Simplifies file management and
offers insights into your file system.

Usage: ./goattool [switch] [arguments]

Switches:
  -p, --print <files>			Print contents of 1+ files.
  -s, --search <file> <str>			Search file for a string and
                                       print every line with string.
  -z, --size <files>			Print size of one or more files.
  -m, --merge <output> <files>			Merge files into a file
                                          with a name and path.
  -c, --compress <file>			Compress a text file to .goat.
                                   with a specified name and path.
  -d, --decompress <file>			Decompress a .goat file to get
                                     the original text.
  -rwx, --permissions <files>			Print permissions of
                                        files (000 to 777).
  -mv, --move <source> <dest>			Move a file from source
                                         path to destination path.
  -h, --help                 			Print a help page.

Examples:
> ./goattool -s file.txt password
> ./goattool -mv writing.txt ~/dev/new.txt
> ./goattool -m ~/projects/project.txt part1.txt part2.txt"
echo -e "Received Output:"
echo -e "$(./goattool)"
echo -e "=====================\n"
