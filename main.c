#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"
#include "text_operations.h"

int main(int argc, char *argv[]){
    // May need to alter, a blank ./goattool should at least print the homepage...
    if (argc < 2){
        fprintf(stderr, "Usage: %s <command> [arguments]\n", argv[0]);
        return 0;
    }
    const char *command = argv[1];

    // ============================================================
    // PRINT
    if (strcmp(command, "-p") == 0 || strcmp(command, "--print") == 0){
        if (argc < 3) {
            fprintf(stderr, "Usage: %s -p/--print <file>...\n", argv[0]);
            return 1;
        }

        // Copy file names to filesArg
        char **filesArg = malloc((argc - 2) * sizeof(char *));
        for (int i = 0; i < argc - 2; i++) {
            filesArg[i] = strdup(argv[i + 2]);
            if (filesArg[i] == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                return 1;
            }
        }

        // Example: ./goattool -p, --print <file1> [file2] [file3] ...
        print_file_contents(filesArg, argc - 2);

        // Free dynamically allocated memory
        for (int i = 0; i < argc - 2; i++) {
            free(filesArg[i]);
        }
        free(filesArg);
    }
    // ============================================================




    // ============================================================
    // SEARCH
    else if (strcmp(command, "-s") == 0 || strcmp(command, "--search") == 0) {
        if (argc < 4){
            fprintf(stderr, "Usage: %s -s/--search <file> <string>\n", argv[0]);
            return 1;
        }


        // Example: ./goattool -s, --search <file> <string>
        search_file_for_string(argv[2], argv[3]);
    }
    // ============================================================


    // SIZE
    else if (strcmp(command, "-z") == 0 || strcmp(command, "--size")  == 0){
        // Example: ./goattool -z, --size <file> !COULD BE MULTIPLE FILES
        int num_files = argc - 2; // Calculate the number of files passed
        print_file_size(argv + 2, num_files);
    }

    // MERGE
    else if (strcmp(command, "-m") == 0 || strcmp(command, "--merge") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Usage: %s -m/--merge <output-file> <files>...\n", argv[0]);
            return 1;
        }

        const char* output_file = argv[2];
        int num_source_files = argc - 3; // Calculate the number of source files passed
        const char** source_files = (const char**)&argv[3]; // Point to the source files in argv

        merge_files(source_files, num_source_files, output_file);
    }

    // COMPRESS
    else if (strcmp(command, "-c") == 0 || strcmp(command, "--compress") == 0){
        // Example: ./goattool -c, --compress <file>
        print_file_size(argv[2], argv[3]);
    }

    // DECOMPRESS
    else if (strcmp(command, "-d") == 0 || strcmp(command, "--decompress") == 0){
        // Example: ./goattool -d, --decompress <file>
        print_file_size(argv[2], argv[3]);
    }

    // PERMISSIONS
    else if (strcmp(command, "-rwx") == 0 || strcmp(command, "--permissions") == 0){
        // Example: ./goattool -rwx, --permissions <file> !! Can be multiple
        int num_files = argc - 2; // Calculate the number of files passed
        print_file_permissions(argv + 2, num_files);
    }

    // MOVE
    else if (strcmp(command, "-mv") == 0 || strcmp(command, "--move") == 0){
        // Example: ./goattool -mv, --move <source> <destination>
        if (argc == 4) {
            move_file(argv[2], argv[3]);
        } else {
            fprintf(stderr, "Usage: %s -mv, --move <source> <destination>\n", argv[0]);
        }
    }

    // HELP
    else if (strcmp(command, "-h") == 0 || strcmp(command, "--help") == 0){
        // Example: ./goattool -h, --help
        printf("help page contents.");
    }
    return 0;
}
