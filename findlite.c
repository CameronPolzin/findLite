/************************************************
* A simple implementation of a file search      *
* utility in C that mimics basic functionality  *
* of the Unix 'find' command.                   *
*                                               *
* Usage: ./findLite <directory> <pattern>       *
* Pattern can be of the form:                   *
*   - *.txt (matches files ending with .txt)    *
*   - test* (matches files starting with test)  *
*                                               *
* Author: Cameron Polzin                        *
*************************************************/

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <strings.h>

// Function to check if filename matches the given pattern
int matchesPattern(char *filename, char *pattern) {
    int lenPattern = strlen(pattern);

    // Case 1: pattern starts with '*' -> suffix match (e.g., *.txt)
    if (pattern[0] == '*') {
        char *suffix = pattern + 1;

        int lenName = strlen(filename);
        int lenSuffix = strlen(suffix);

        // Check if filename ends with the suffix
        if (lenName >= lenSuffix &&
            strcasecmp(filename + lenName - lenSuffix, suffix) == 0) {
            return 1;
        }
    }

    // Case 2: pattern ends with '*' -> prefix match (e.g., test*)
    else if (pattern[lenPattern - 1] == '*') {
        int lenPrefix = lenPattern - 1;

        // Check if filename starts with the prefix
        if (strncasecmp(filename, pattern, lenPrefix) == 0) {
            return 1;
        }
    }

    return 0;
}

// Recursive function to search through directories
void searchDirectory(char *basePath, char *pattern) {

    // Open the current directory
    DIR *dp = opendir(basePath); 
    if (dp == NULL) {
        fprintf(stderr, "Could not open directory: %s\n", basePath);
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(dp)) != NULL) {

        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        // Skip hidden files (those starting with '.')
        if (entry->d_name[0] == '.') {
            continue;
        }

        // Build full path: basePath + "/" + filename
        char fullPath[1024];
        if (basePath[strlen(basePath) - 1] == '/') {
            snprintf(fullPath, sizeof(fullPath), "%s%s", basePath, entry->d_name);
        } else {
            snprintf(fullPath, sizeof(fullPath), "%s/%s", basePath, entry->d_name);
        }

        // Check if the filename matches the pattern
        if (matchesPattern(entry->d_name, pattern)) {
            printf("%s\n", fullPath);
        }

        // Use stat to check if this entry is a directory
        struct stat path_stat;

        if (stat(fullPath, &path_stat) == -1) {
            fprintf(stderr, "stat failed on %s: ", fullPath);
            perror("");
            continue;
        }

        // If it is a directory, recursively search inside it
        if (S_ISDIR(path_stat.st_mode)) {
            searchDirectory(fullPath, pattern);
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[]) {

    // Validate arguments
    // Expected usage: ./findLite <directory> <pattern>
    if (argc != 3) {
        printf("Usage: ./findLite <directory> <pattern>\n");
        return 1;
    }

    //stores base directory path
    char *basePath = argv[1];
    char *pattern = argv[2];

    // Count the number of '*' in pattern
    int starCount = 0;
    for (int i = 0; pattern[i]; i++) {
       if (pattern[i] == '*') {
           starCount++;
       }
    }

    // Only allow one '*' at beginning or end of pattern
    if (starCount != 1 || (pattern[0] != '*' && pattern[strlen(pattern) - 1] != '*')) {
      printf("Pattern must contain exactly one '*' at the beginning or end\n");
        return 1;
    }

    // Check if the base directory can be opened
    DIR *dp = opendir(basePath);
    if (dp == NULL) {
        fprintf(stderr, "Could not open directory: %s\n", basePath);
        return 1;
    }
    closedir(dp);

    // Start recursive search
    searchDirectory(basePath, pattern);

    return 0;
}
