/*
 * File: text_operations.c
 * Author: Trent Tucker
 * Description: goattool's implementation for the text operations
 *              that the tool offers
 * Created on: November 19, 2023
 */

#include "text_operations.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void compress_to_goat(const char* source_file_path) {
    FILE* source_file = fopen(source_file_path, "r");
    if (source_file == NULL) {
        perror("Error opening source file");
        return;
    }

    char goat_file_path[256];
    strcpy(goat_file_path, source_file_path);

    char * last_dot = strchr(goat_file_path, '.');
    if(last_dot != NULL) {
        strcpy(last_dot, ".goat");
    }

    FILE* goat_file = fopen(goat_file_path, "w");
    if (goat_file == NULL) {
        perror("Error creating compressed file");
        fclose(source_file);
        return;
    }

    int current_char = fgetc(source_file);
    int count = 1;

    while (current_char != EOF) {
        if (current_char == ' ') {
            fprintf(goat_file, "%c", current_char);
            current_char = fgetc(source_file);
            continue;
        } else if (current_char == '\n') {
            fprintf(goat_file, "\\n%d", count);
            current_char = fgetc(source_file);
            count = 1;
            continue;
        }

        int next_char = fgetc(source_file);

        if (next_char == current_char) {
            count++;
        } else {
            fprintf(goat_file, "%c%d", current_char, count);
            current_char = next_char;
            count = 1;
        }
    }

    fclose(source_file);
    fclose(goat_file);

    printf(".goat compression completed\n.goat file: %s\n",
           goat_file_path);
}

void decompress_from_goat(const char* source_goat_file_path) {
    FILE* source_file = fopen(source_goat_file_path, "r");
    if (source_file == NULL) {
        perror("Error opening source .goat file");
        return;
    }

    char decompressed_file_path[100];
    snprintf(decompressed_file_path, sizeof(decompressed_file_path),
             "%s.decompressed.txt", source_goat_file_path);

    FILE* decompressed_file = fopen(decompressed_file_path, "w");
    if (decompressed_file == NULL) {
        perror("Error creating decompressed file");
        fclose(source_file);
        return;
    }

    char current_char;
    int count = 1;

    while (fscanf(source_file, "%c", &current_char) == 1) {
        if (fscanf(source_file, "%d", &count) != 1) {
            count = 1;
        }

        if (current_char == ' ') {
            fprintf(decompressed_file, " ");
        } else if (current_char == '\n') {
            for (int i = 0; i < count; i++) {
                fprintf(decompressed_file, "\n");
            }
        } else {
            for (int i = 0; i < count; i++) {
                fprintf(decompressed_file, "%c", current_char);
            }
        }
    }

    fclose(source_file);
    fclose(decompressed_file);

    printf("decompression saved into %s\n",
           decompressed_file_path);
}

void print_help_page(void) {
    printf("\t\t\t\t\tHelp Page\n\n");
    printf("Overview: GoatTool is a CLI utility for exploring and\n");
    printf("understanding Unix file systems. It includes operations\n");
    printf("like printing file contents, searching for strings, file\n");
    printf("sizes, merging files, compressing/decompressing in .goat\n");
    printf("format, displaying file permissions, moving files, and\n");
    printf("providing a help page. Simplifies file management and\n");
    printf("offers insights into your file system.\n\n");
    printf("Usage: ./goattool [switch] [arguments]\n\n");
    printf("Switches:\n");
    printf("  -p, --print <files>\t\t\tPrint contents of 1+ files.\n");
    printf("  -s, --search <file> <str>\t\t\tSearch file for a string and\n");
    printf("                           \t\t\tprint every line with string.\n");
    printf("  -z, --size <files>\t\t\tPrint size of one or more files.\n");
    printf("  -m, --merge <output> <files>\t\t\tMerge files into a file\n");
    printf("                              \t\t\twith a name and path.\n");
    printf("  -c, --compress <file>\t\t\tCompress a text file to .goat.\n");
    printf("                       \t\t\twith a specified name and path.\n");
    printf("  -d, --decompress <file>\t\t\tDecompress a .goat file to get\n");
    printf("                         \t\t\tthe original text.\n");
    printf("  -rwx, --permissions <files>\t\t\tPrint permissions of\n");
    printf("                            \t\t\tfiles (000 to 777).\n");
    printf("  -mv, --move <source> <dest>\t\t\tMove a file from source\n");
    printf("                             \t\t\tpath to destination path.\n");
    printf("  -h, --help                 \t\t\tPrint a help page.\n\n");
    printf("Examples:\n");
    printf("> ./goattool -s file.txt password\n");
    printf("> ./goattool -mv writing.txt ~/dev/new.txt\n");
    printf("> ./goattool -m ~/projects/project.txt part1.txt part2.txt\n");
}

