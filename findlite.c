#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

// Recursive function to search through directories
void searchDirectory(char *basePath) {

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

        // Print the full path
        printf("%s\n", fullPath);

        // Use stat to check if this entry is a directory
        struct stat path_stat;
        stat(fullPath, &path_stat);

        // If it is a directory, recursively search inside it
        if (S_ISDIR(path_stat.st_mode)) {
            searchDirectory(fullPath);
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

    // Start recursive search
    searchDirectory(basePath);

    return 0;
}
