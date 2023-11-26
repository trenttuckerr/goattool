/*
 * File: main.c
 * Author: Trent Tucker
 * Description: driver file for goattool
 * Created on: November 19, 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"
#include "text_operations.h"


int main(int argc, char *argv[]){
    const int RUN_AND_SWITCH_ARGUMENT_COUNT = 2;

    if (argc == 1){
        print_help_page();
        return 0;
    }

    const char *COMMAND = argv[1];

    if (strcmp(COMMAND, "-p") == 0 || strcmp(COMMAND, "--print") == 0){
        const int MINIMUM_ARGS_FOR_PRINT_OPERATION = 3;
        if (argc < MINIMUM_ARGS_FOR_PRINT_OPERATION) {
            fprintf(stderr, "Usage: %s -p/--print <files>\n", argv[0]);
            return 1;
        }

        char **files_arg = malloc((argc - RUN_AND_SWITCH_ARGUMENT_COUNT)
                                  * sizeof(char *));
        for (int i = 0; i < argc - RUN_AND_SWITCH_ARGUMENT_COUNT; i++) {
            files_arg[i] = strdup(argv[i + RUN_AND_SWITCH_ARGUMENT_COUNT]);
            if (files_arg[i] == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                return 1;
            }
        }

        print_file_contents(files_arg, argc - RUN_AND_SWITCH_ARGUMENT_COUNT);

        for (int i = 0; i < argc - RUN_AND_SWITCH_ARGUMENT_COUNT; i++) {
            free(files_arg[i]);
        }
        free(files_arg);
    }

    else if (strcmp(COMMAND, "-s") == 0 || strcmp(COMMAND, "--search") == 0) {
        const int EXACT_NUMBER_OF_ARGS_NEEDED_FOR_SEARCH_OPERATION = 4;

        if (argc == EXACT_NUMBER_OF_ARGS_NEEDED_FOR_SEARCH_OPERATION){
            search_file_for_string(argv[2], argv[3]);
        } else{
            fprintf(stderr, "Usage: %s -s/--search <file> <string>\n",
                    argv[0]);
            return 1;
        }
    }

    else if (strcmp(COMMAND, "-z") == 0 || strcmp(COMMAND, "--size")  == 0){
        const int MINIMUM_ARGS_FOR_SIZE_OPERATION = 3;
        if (argc < MINIMUM_ARGS_FOR_SIZE_OPERATION){
            fprintf(stderr, "Usage: %s -z/--size <files>\n", argv[0]);
            return 1;
        }
        int num_files = argc - RUN_AND_SWITCH_ARGUMENT_COUNT;
        print_file_size(argv + RUN_AND_SWITCH_ARGUMENT_COUNT, num_files);
    }

    else if (strcmp(COMMAND, "-m") == 0 || strcmp(COMMAND, "--merge") == 0) {
        const int MINIMUM_ARGS_FOR_MERGE_OPERATION = 4;
        if (argc < MINIMUM_ARGS_FOR_MERGE_OPERATION) {
            fprintf(stderr, "Usage: %s -m/--merge <output-file> <files>\n",
                    argv[0]);
            return 1;
        }

        const char* output_file = argv[2];
        int num_source_files = argc - 3;
        const char** source_files = (const char**)&argv[3];

        merge_files(source_files, num_source_files, output_file);
    }

    else if (strcmp(COMMAND, "-c") == 0 || strcmp(COMMAND, "--compress") == 0){
        const int EXACT_NUMBER_OF_ARGS_NEEDED_FOR_COMPRESS_OPERATION = 3;
        if (argc == EXACT_NUMBER_OF_ARGS_NEEDED_FOR_COMPRESS_OPERATION){
            compress_to_goat(argv[2]);
        } else{
            fprintf(stderr, "Usage: %s -c/--compress <file>\n", argv[0]);
            return 1;
        }
    }

    else if (strcmp(COMMAND, "-d") == 0 ||
             strcmp(COMMAND, "--decompress") == 0){
        const int EXACT_NUMBER_OF_ARGS_NEEDED_FOR_DECOMPRESS_OPERATION = 3;
        if (argc == EXACT_NUMBER_OF_ARGS_NEEDED_FOR_DECOMPRESS_OPERATION) {
            decompress_from_goat(argv[2]);
        } else {
            fprintf(stderr, "Usage: %s -d/--decompress <file>\n", argv[0]);
            return 1;
        }
    }

    else if (strcmp(COMMAND, "-rwx") == 0 ||
             strcmp(COMMAND, "--permissions") == 0){
        const int MINIMUM_ARGS_FOR_PERMISSIONS_OPERATION = 3;
        if (argc < MINIMUM_ARGS_FOR_PERMISSIONS_OPERATION) {
            fprintf(stderr, "Usage: %s -rwx/--permissions <files>\n", argv[0]);
            return 1;
        }
        int num_files = argc - 2;
        print_file_permissions(argv + 2, num_files);
    }

    else if (strcmp(COMMAND, "-mv") == 0 || strcmp(COMMAND, "--move") == 0){
        const int EXACT_NUMBER_OF_ARGS_NEEDED_FOR_MOVE_OPERATION = 4;
        if (argc == EXACT_NUMBER_OF_ARGS_NEEDED_FOR_MOVE_OPERATION) {
            move_file(argv[2], argv[3]);
        } else {
            fprintf(stderr,
                    "Usage: %s -mv/--move <source> <destination>\n", argv[0]);
        }
    }

    else if (strcmp(COMMAND, "-h") == 0 || strcmp(COMMAND, "--help") == 0){
        print_help_page();
    }

    else {
        printf("Supplied switch not recognized: %s\nHere's the help page!\n\n",
               COMMAND);
        print_help_page();
        return 1;
    }

    return 0;
}
