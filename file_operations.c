/*
 * File: file_operations.c
 * Author: Trent Tucker
 * Description: goattool's implementation for the file operations
 *              that the tool offers.
 *
 * GitHub Repository: https://github.com/trenttuckerr/goattool
 *
 * Created on: November 19, 2023
 */

#include "file_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


/**
 * @brief Print the contents of one or more files to the console.
 *
 * This function takes an array of file paths and prints the contents of each
 * specified file to the console.
 *
 * @param files An array of file paths (strings).
 * @param num_files The number of files in the array.
 */
void print_file_contents(const char *files[], int num_files) {
    for (int i = 0; i < num_files; ++i) {
        FILE *file = fopen(files[i], "r");
        if (file == NULL) {
            fprintf(stderr, "Error opening file: %s\n", files[i]);
            continue;
        }
        printf("Contents of file: %s\n", files[i]);

        // read file one character at a time, and output each character
        int character;
        while ((character = fgetc(file)) != EOF) {
            putchar(character);
        }

        fclose(file);
        printf("\n=====================\n");
    }
}


/**
 * @brief Search a file for a particular string and print lines containing that string.
 *
 * This function takes a file path and a search string. It searches the file for
 * occurrences of the search string and  prints everyline containing that string to the console.
 *
 * @param file_path The path of the file to be searched.
 * @param search_string The string to search for in the file.
 */
void search_file_for_string(const char* file_path, const char* search_string){
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", file_path);
        return;
    }

    // read and print lines containing the search string
    char line[256]; // adjust size upon need
    int found = 0;   // flag indication -> have we found the string?

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, search_string) != NULL) {
            printf("String found in file!\n");
            printf("Line containing text: %s\n", line);
            found = 1;
        }
    }
    fclose(file);
    if (!found) {
        printf("String '%s' not found in the file.\n", search_string);
    }
}


/**
 * @brief Print the size of one or more files to the console.
 *
 * This function takes an array of file paths and prints the size of each specified
 * file to the console.
 *
 * @param files An array of file paths (strings).
 * @param num_files The number of files in the array.
 */
void print_file_size(const char* files[], int num_files) {
    for (int i = 0; i < num_files; ++i) {
        const char* file_path = files[i];

        // utilize stat to get file information, includes size
        struct stat file_info;
        if (stat(file_path, &file_info) == 0) {
            printf("File: %s, Size: %lld bytes\n", file_path, (long long)file_info.st_size);
        } else {
            perror("Error getting file size.");
        }
    }
}


/**
 * @brief Merge multiple files into a single file with a specified name and path.
 *
 * This function takes an array of source file paths, the number of source files, and
 * a destination file path. It merges the contents of the source files into a single file
 * at the specified destination path.
 *
 * @param source_files An array of source file paths (strings).
 * @param num_source_files The number of source files in the array.
 * @param dest_file_path The path of the destination file.
 */
void merge_files(const char* source_files[], int num_source_files, const char* dest_file_path) {
    // open in write binary
    FILE* dest_file = fopen(dest_file_path, "wb");
    if (dest_file == NULL) {
        perror("Error opening destination file");
        return;
    }

    // iterate through source files and append their contents to the destination file
    for (int i = 0; i < num_source_files; ++i) {
        const char* source_file_path = source_files[i];
        FILE* source_file = fopen(source_file_path, "rb");

        if (source_file == NULL) {
            perror("Error opening source file");
            fclose(dest_file);
            return;
        }

        // copy contents from source to destination
        char buffer[1024];
        size_t bytes_read;

        while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
            fwrite(buffer, 1, bytes_read, dest_file);
        }
        fclose(source_file);
    }
    fclose(dest_file);
}


/**
 * @brief Print the permissions of one or more files as an integer (000 to 777).
 *
 * This function takes an array of file paths and prints the file permissions as integers
 * to the console.
 *
 * @param files An array of file paths (strings).
 * @param num_files The number of files in the array.
 */
void print_file_permissions(const char* files[], int num_files) {
    for (int i = 0; i < num_files; ++i) {
        const char* file_path = files[i];
        // use stat to get file information, includes permissions
        struct stat file_info;
        if (stat(file_path, &file_info) == 0) {
            // print permissions as an integer (000 to 777)
            printf("File: %s, Permissions: %o\n", file_path, file_info.st_mode & 0777);
        } else {
            perror("Error getting file permissions");
        }
    }
}


/**
 * @brief Move a file from one place to another with a specified path and new name.
 *
 * This function takes the source file path and the destination path. It moves the specified
 * file to the destination path with a potentially new name.
 *
 * @param source_path The path of the source file.
 * @param dest_path The path of the destination file.
 */
void move_file(const char* source_path, const char* dest_path) {
    if (rename(source_path, dest_path) == 0) {
        printf("File moved successfully from %s to %s\n", source_path, dest_path);
    } else {
        perror("Error moving file");
    }
}
