#include "text_operations.h"

#include <stdio.h>

void compress_to_goat(const char* source_file_path) {
    printf("reached compression algorithm");
    FILE* source_file = fopen(source_file_path, "r");
    if (source_file == NULL) {
        perror("Error opening source file");
        return;
    }

    // Create the compressed file with ".goat" extension
    char goat_file_path[256]; // change as needed, assuming path will be < 256 chars
    snprintf(goat_file_path, sizeof(goat_file_path), "%s.goat", source_file_path);
    FILE* goat_file = fopen(goat_file_path, "w");
    if (goat_file == NULL) {
        perror("Error creating compressed file");
        fclose(source_file);
        return;
    }

    int current_char = fgetc(source_file);
    int count = 1;

    // compression algorithm
    while (current_char != EOF) {
        if(current_char == ' ') {
            printf("we have hit this top declaration for %c\n", current_char);
            fprintf(goat_file, "%c", current_char);
            current_char = fgetc(source_file);
            continue;
        }

        int next_char = fgetc(source_file);

        // check if the next character is the same as the current one and not a space
        if (next_char == current_char) {
            count++;
        } else {
            printf("we have hit this bot declaration for %c\n", current_char);
            // write compressed data to .goat file
            fprintf(goat_file, "%c%d", current_char, count);

            current_char = next_char;
            count = 1;
        }
    }

    fclose(source_file);
    fclose(goat_file);

    printf(".goat compression completed.\n .goat file: file: %s\n", goat_file_path);
}

void decompress_from_goat(const char* source_goat_file_path) {
    // Implementation
}


/**
 * @brief Print a help page for the GoatTool program.
 *
 * This function prints a help page to the console, providing information on how
 * to use the GoatTool program, its commands, and their respective functionalities.
 */
void print_help_page(void) {
    printf("\t\t\t\t\tHelp Page\n\n");
    printf("Overview: GoatTool is a command-line utility designed to assist\n");
    printf("users in exploring and understanding the file system of their\n");
    printf("Unix-like operating systems. It offers various operations, including\n");
    printf("printing file contents, searching for specific strings, printing file\n");
    printf("sizes, merging files, compressing and decompressing files in the .goat\n");
    printf("format, displaying file permissions, moving files, and providing a\n");
    printf("help page. With its straightforward interface and an array of\n");
    printf("essential operations, GoatTool simplifies the management of files and\n");
    printf("provides insights into your file system.\n\n");
    printf("Usage: ./goattool [switch] [arguments]\n\n");
    printf("Switches:\n");
    printf("  -p, --print <file>                 Print the contents of one or more files.\n");
    printf("  -s, --search <file> <string>       Search a file for a particular string and print every line of\n");
    printf("                                     the file that contains that string.\n");
    printf("  -z, --size <file>                  Print the size of one or more files.\n");
    printf("  -m, --merge <output-file> <files>  Merge multiple files into a single file with a specified\n");
    printf("                                     name and path.\n");
    printf("  -c, --compress <file>              Compress a text file into the .goat format.\n");
    printf("  -d, --decompress <file>            Decompress a .goat file to retrieve the original text.\n");
    printf("  -rwx, --permissions <file>         Print the permissions of one or more files as an integer (000 to\n");
    printf("                                     777).\n");
    printf("  -mv, --move <source> <destination> Move a file from one place to another with a specified path\n");
    printf("                                     and new name.\n");
    printf("  -h, --help                         Print a help page.\n\n");
    printf("Examples:\n");
    printf("> ./goattool -s file.txt password\n");
    printf("> ./goattool -mv writing.txt ~/dev/new.txt\n");
    printf("> ./goattool -m ~/projects/project.txt part1.txt part2.txt\n");
}
