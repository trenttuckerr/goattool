/*
 * File: file_operations.c
 * Author: Trent Tucker
 * Description: goattool's implementation for the file operations
 *              that the tool offers
 * Created on: November 19, 2023
 */

#include "file_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
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
            printf("Error: The file '%s' does not exist.\n", files[i]);
            // fprintf(stderr, "Error opening file: %s\n", files[i]);
            continue;
        }
        printf("Contents of file: %s\n", files[i]);

        int character;
        while ((character = fgetc(file)) != EOF) {
            putchar(character);
        }

        fclose(file);
        printf("\n=====================\n");
    }
}


/**
 * @brief Search a file for a particular string and print lines containing
 * that string.
 *
 * This function takes a file path and a search string. It searches the
 * file for occurrences of the search string and  prints everyline
 * containing that string to the console.
 *
 * @param file_path The path of the file to be searched.
 * @param search_string The string to search for in the file.
 */
void search_file_for_string(const char* file_path,
                            const char* search_string){
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", file_path);
        return;
    }

    char line[256];
    int found = 0;

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
 * This function takes an array of file paths and prints the
 * size of each specified file to the console.
 *
 * @param files An array of file paths (strings).
 * @param num_files The number of files in the array.
 */
void print_file_size(const char* files[], int num_files) {
    for (int i = 0; i < num_files; ++i) {
        const char* FILE_PATH = files[i];

        struct stat file_info;
        if (stat(FILE_PATH, &file_info) == 0) {
            printf("File: %s, Size: %lld bytes\n", FILE_PATH,
                   (long long)file_info.st_size);
        } else {
            perror("Error getting file size.");
        }
    }
}


/**
 * @brief Copy the content of a source file to a destination
 * file in a separate thread.
 *
 * This function is designed to be used in a multithreaded
 * context, copying the contents of a specified source file
 * to a destination file. It locks and unlocks the destination
 * file to avoid data corruption during the copying process.
 *
 * @param arg A pointer to a ThreadArgs structure containing
 * the source and destination file paths.
 * @return NULL on success. Note: The function does not return
 * a value; the return type is required for compatibility with
 * pthread_create.
 */
void* pthread_copy_file_content(void* arg) {
    typedef struct {
        const char* SOURCE_FILE;
        const char* DEST_FILE_PATH;
    } ThreadArgs;

    ThreadArgs* args = (ThreadArgs*)arg;
    FILE* source = fopen(args->SOURCE_FILE, "rb");

    if (source) {
        int c;
        FILE* dest_file = fopen(args->DEST_FILE_PATH, "ab");

        if (!dest_file) {
            fprintf(stderr, "Error: Unable to open destination file\n");
            return NULL;
        }

        while ((c = fgetc(source)) != EOF) {
            flockfile(dest_file);
            fputc(c, dest_file);
            funlockfile(dest_file);
        }

        fclose(source);
        fclose(dest_file);
    } else {
        fprintf(stderr, "Error: Unable to open source file %s\n",
                args->SOURCE_FILE);
    }

    free(args);

    return NULL;
}



/**
 * @brief Merge multiple files into a single file with a specified
 * name and path.
 *
 * This function takes an array of source file paths, the number
 * of source files, and a destination file path. It merges the
 * contents of the source files into a single file at the specified
 * destination path.
 *
 * @param source_files An array of source file paths (strings).
 * @param num_source_files The number of source files in the array.
 * @param dest_file_path The path of the destination file.
 */
void merge_files(const char* source_files[], int num_source_files,
                 const char* dest_file_path) {
    pthread_t threads[num_source_files];

    for (int i = 0; i < num_source_files; ++i) {
        typedef struct {
            const char* SOURCE_FILE;
            const char* DEST_FILE_PATH;
        } ThreadArgs;

        ThreadArgs* thread_args = (ThreadArgs*)malloc(sizeof(ThreadArgs));
        thread_args->SOURCE_FILE = source_files[i];
        thread_args->DEST_FILE_PATH = dest_file_path;

        if (pthread_create(&threads[i], NULL, pthread_copy_file_content,
                           (void*)thread_args) != 0) {
            fprintf(stderr, "Error: Unable to create thread\n");
            break;
        }
    }

    for (int i = 0; i < num_source_files; ++i) {
        pthread_join(threads[i], NULL);
    }
}


/**
 * @brief Print the permissions of one or more files as
 * an integer (000 to 777).
 *
 * This function takes an array of file paths and prints
 * the file permissions as integers to the console.
 *
 * @param files An array of file paths (strings).
 * @param num_files The number of files in the array.
 */
void print_file_permissions(const char* files[], int num_files) {
    for (int i = 0; i < num_files; ++i) {
        const char* FILE_PATH = files[i];
        struct stat file_info;
        if (stat(FILE_PATH, &file_info) == 0) {
            printf("File: %s, Permissions: %o\n", FILE_PATH,
                   file_info.st_mode & 0777);
        } else {
            perror("Error getting file permissions");
        }
    }
}


/**
 * @brief Move a file from one place to another with a
 * specified path and new name.
 *
 * This function takes the source file path and the destination
 * path. It moves the specified file to the destination path
 * with a potentially new name.
 *
 * @param source_path The path of the source file.
 * @param dest_path The path of the destination file.
 */
void move_file(const char* source_path, const char* dest_path) {
    if (rename(source_path, dest_path) == 0) {
        printf("File moved successfully from %s to %s\n",
               source_path, dest_path);
    } else {
        perror("Error moving file");
    }
}
