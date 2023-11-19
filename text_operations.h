#ifndef TEXT_OPERATIONS_H
#define TEXT_OPERATIONS_H

/**
 * @file text_operations.h
 * @brief Declarations for text-related operations in GoatTool.
 */

/**
 * @brief Compress a text file into the .goat format.
 *
 * This function takes the path of a source text file and compresses its contents
 * into the .goat format. The compressed file is created in the same directory
 * with the same name and the ".goat" extension.
 *
 * @param source_file_path The path of the source text file.
 */
void compress_to_goat(const char* source_file_path);

/**
 * @brief Decompress a .goat file to retrieve the original text.
 *
 * This function takes the path of a source .goat file and decompresses its contents,
 * creating a text file in the same directory with the same name (without the ".goat"
 * extension) containing the decompressed content.
 *
 * @param source_goat_file_path The path of the source .goat file.
 */
void decompress_from_goat(const char* source_goat_file_path);

/**
 * @brief Print a help page for the GoatTool program.
 *
 * This function prints a help page to the console, providing information on how
 * to use the GoatTool program, its commands, and their respective functionalities.
 */
void print_help_page(void);

#endif
