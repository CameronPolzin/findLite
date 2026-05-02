#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

// Function to check if filename matches the given pattern
int matchesPattern(char *filename, char *pattern) {

    // Case 1: pattern starts with '*' -> suffix match (e.g., *.txt)
    if (pattern[0] == '*') {
        char *suffix = pattern + 1;

        int lenName = strlen(filename);
        int lenSuffix = strlen(suffix);

        // Check if filename ends with the suffix
        if (lenName >= lenSuffix &&
            strcmp(filename + lenName - lenSuffix, suffix) == 0) {
            return 1;
        }
    }

    // Case 2: pattern ends with '*' -> prefix match (e.g., test*)
    else if (pattern[strlen(pattern) - 1] == '*') {
        int lenPrefix = strlen(pattern) - 1;

        // Check if filename starts with the prefix
        if (strncmp(filename, pattern, lenPrefix) == 0) {
            return 1;
        }
    }

    return 0;
}

// Recursive function to search through directories
void searchDirectory(char *basePath, char *pattern) {

    // Open the current directory
    DIR *dp = opendir(basePath); 

    // Check if the directory was opened successfully
    if (dp == NULL) { 
        perror("opendir failed");
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(dp)) != NULL) {

        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Build full path: basePath + "/" + filename
        char fullPath[1024];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", basePath, entry->d_name);

        // Check if the filename matches the pattern
        if (matchesPattern(entry->d_name, pattern)) {
            printf("%s\n", fullPath);
        }

        // Use stat to check if this entry is a directory
        struct stat path_stat;
        stat(fullPath, &path_stat);

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

    // Start recursive search
    searchDirectory(basePath, pattern);

    return 0;
}
