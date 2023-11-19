#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

/**
 * @file file_operations.h
 * @brief Declarations for file-related operations in GoatTool.
 */

/**
 * @brief Print the contents of one or more files to the console.
 *
 * This function takes an array of file paths and prints the contents of each
 * specified file to the console.
 *
 * @param files An array of file paths (strings).
 * @param num_files The number of files in the array.
 */
void print_file_contents(const char* files[], int num_files);

/**
 * @brief Search a file for a particular string and print lines containing that string.
 *
 * This function takes a file path and a search string. It searches the file for
 * occurrences of the search string and prints every line containing that string to the console.
 *
 * @param file_path The path of the file to be searched.
 * @param search_string The string to search for in the file.
 */
void search_file_for_string(const char* file_path, const char* search_string);

/**
 * @brief Print the size of one or more files to the console.
 *
 * This function takes an array of file paths and prints the size of each specified
 * file to the console.
 *
 * @param files An array of file paths (strings).
 * @param num_files The number of files in the array.
 */
void print_file_size(const char* files[], int num_files);

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
void merge_files(const char* source_files[], int num_source_files, const char* dest_file_path);

/**
 * @brief Print the permissions of one or more files as an integer (000 to 777).
 *
 * This function takes an array of file paths and prints the file permissions as integers
 * to the console.
 *
 * @param files An array of file paths (strings).
 * @param num_files The number of files in the array.
 */
void print_file_permissions(const char* files[], int num_files);

/**
 * @brief Move a file from one place to another with a specified path and new name.
 *
 * This function takes the source file path and the destination path. It moves the specified
 * file to the destination path with a potentially new name.
 *
 * @param source_path The path of the source file.
 * @param dest_path The path of the destination file.
 */
void move_file(const char* source_path, const char* dest_path);

#endif
