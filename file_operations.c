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

void move_file(const char* source_path, const char* dest_path) {
    if (rename(source_path, dest_path) == 0) {
        printf("File moved successfully from %s to %s\n",
               source_path, dest_path);
    } else {
        perror("Error moving file");
    }
}

