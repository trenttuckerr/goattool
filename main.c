#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"
#include "text_operations.h"


int main(int argc, char *argv[]){
    // count of expected arguments - ./goattool and -[switch]
    const int RUN_AND_SWITCH_ARGUMENT_COUNT = 2;

    if (argc == 1){
        print_help_page();
        return 0;
    }

    const char *command = argv[1];

    if (strcmp(command, "-p") == 0 || strcmp(command, "--print") == 0){
        const int MINIMUM_ARGS_FOR_PRINT_OPERATION = 3;
        if (argc < MINIMUM_ARGS_FOR_PRINT_OPERATION) {
            fprintf(stderr, "Usage: %s -p/--print <file>\n", argv[0]);
            return 1;
        }

        // copy file names to files_arg
        char **files_arg = malloc((argc - RUN_AND_SWITCH_ARGUMENT_COUNT) * sizeof(char *));
        for (int i = 0; i < argc - RUN_AND_SWITCH_ARGUMENT_COUNT; i++) {
            files_arg[i] = strdup(argv[i + RUN_AND_SWITCH_ARGUMENT_COUNT]);
            if (files_arg[i] == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                return 1;
            }
        }

        // example: ./goattool -p, --print <file1> [file2] [file3] ...
        print_file_contents(files_arg, argc - RUN_AND_SWITCH_ARGUMENT_COUNT);

        for (int i = 0; i < argc - RUN_AND_SWITCH_ARGUMENT_COUNT; i++) {
            free(files_arg[i]);
        }
        free(files_arg);
    }

    else if (strcmp(command, "-s") == 0 || strcmp(command, "--search") == 0) {
        const int EXACT_NUMBER_OF_ARGS_NEEDED_FOR_SEARCH_OPERATION = 4;

        if (argc == EXACT_NUMBER_OF_ARGS_NEEDED_FOR_SEARCH_OPERATION){
            // example: ./goattool -s, --search <file> <string>
            search_file_for_string(argv[2], argv[3]);
        } else{
            fprintf(stderr, "Usage: %s -s/--search <file> <string>\n", argv[0]);
            return 1;
        }
    }

    else if (strcmp(command, "-z") == 0 || strcmp(command, "--size")  == 0){
        const int MINIMUM_ARGS_FOR_SIZE_OPERATION = 3;
        if (argc < MINIMUM_ARGS_FOR_SIZE_OPERATION){
            fprintf(stderr, "Usage: %s -z/--size <files>\n", argv[0]);
            return 1;
        }
        // example: ./goattool -z, --size <files>
        int num_files = argc - RUN_AND_SWITCH_ARGUMENT_COUNT;
        print_file_size(argv + RUN_AND_SWITCH_ARGUMENT_COUNT, num_files);
    }

    else if (strcmp(command, "-m") == 0 || strcmp(command, "--merge") == 0) {
        const int MINIMUM_ARGS_FOR_MERGE_OPERATION = 4;
        if (argc < MINIMUM_ARGS_FOR_MERGE_OPERATION) {
            fprintf(stderr, "Usage: %s -m/--merge <output-file> <files>\n", argv[0]);
            return 1;
        }

        const char* output_file = argv[2];
        int num_source_files = argc - 3;
        const char** source_files = (const char**)&argv[3]; // point to the source files in argv

        merge_files(source_files, num_source_files, output_file);
    }

    else if (strcmp(command, "-c") == 0 || strcmp(command, "--compress") == 0){
        const int EXACT_NUMBER_OF_ARGS_NEEDED_FOR_COMPRESS_OPERATION = 3;
        if (argc == EXACT_NUMBER_OF_ARGS_NEEDED_FOR_COMPRESS_OPERATION){
            // Example: ./goattool -c, --compress <file>
            compress_to_goat(argv[2]);
        } else{
            fprintf(stderr, "Usage: %s -c/--compress <file>\n", argv[0]);
            return 1;
        }
    }

    // DECOMPRESS
    else if (strcmp(command, "-d") == 0 || strcmp(command, "--decompress") == 0){
        const int EXACT_NUMBER_OF_ARGS_NEEDED_FOR_DECOMPRESS_OPERATION = 3;
        if (argc == EXACT_NUMBER_OF_ARGS_NEEDED_FOR_DECOMPRESS_OPERATION) {
            // Example: ./goattool -d, --decompress <file>
            print_file_size(argv[2], argv[3]);
        } else {
            fprintf(stderr, "Usage: %s -d/--decompress <file>\n", argv[0]);
            return 1;
        }
    }

    // PERMISSIONS
    else if (strcmp(command, "-rwx") == 0 || strcmp(command, "--permissions") == 0){
        const int MINIMUM_ARGS_FOR_PERMISSIONS_OPERATION = 3;
        if (argc < MINIMUM_ARGS_FOR_PERMISSIONS_OPERATION) {
            fprintf(stderr, "Usage: %s -rwx/--permissions <files>\n", argv[0]);
            return 1;
        }
        // Example: ./goattool -rwx, --permissions <files>
        int num_files = argc - 2; // Calculate the number of files passed
        print_file_permissions(argv + 2, num_files);
    }

    // MOVE
    else if (strcmp(command, "-mv") == 0 || strcmp(command, "--move") == 0){
        const int EXACT_NUMBER_OF_ARGS_NEEDED_FOR_MOVE_OPERATION = 4;
        // Example: ./goattool -mv, --move <source> <destination>
        if (argc == EXACT_NUMBER_OF_ARGS_NEEDED_FOR_MOVE_OPERATION) {
            move_file(argv[2], argv[3]);
        } else {
            fprintf(stderr, "Usage: %s -mv/--move <source> <destination>\n", argv[0]);
        }
    }

    // HELP
    else if (strcmp(command, "-h") == 0 || strcmp(command, "--help") == 0){
        // Example: ./goattool -h, --help
        print_help_page();
    }
    return 0;
}
