#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {

    // Check for correct number of arguments
    // Expected usage: ./findLite <directory> <pattern>
    if (argc != 3) {
        printf("Usage: ./findLite <directory> <pattern>\n");
        return 1;
    }

    // Store the directory path provided by the user
    char *basePath = argv[1];

    DIR *dp = opendir(basePath);

    // If directory cannot be opened, print error and exit
    if (dp == NULL) {
        perror("opendir failed");
        return 1;
    }

    // Pointer to hold each directory entry
    struct dirent *entry;

    // Loop through all entries in the directory
    while ((entry = readdir(dp)) != NULL) {
        // Skip the current directory "." and parent directory ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        printf("%s\n", entry->d_name);
    }

    closedir(dp);

    return 0;
}