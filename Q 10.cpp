#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

// Producer Process
int main() {
    int fd;
    char buffer[BUFFER_SIZE] = "Hello, World!";
    
    // Create or open a file for writing
    fd = open("message.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    
    // Write data to the file
    if (write(fd, buffer, sizeof(buffer)) < 0) {
        perror("write");
        close(fd);
        exit(1);
    }
    
    // Close the file
    close(fd);
    
    return 0;
}

// Consumer Process
int main() {
    int fd;
    char buffer[BUFFER_SIZE];
    
    // Open the file for reading
    fd = open("message.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    
    // Read data from the file
    if (read(fd, buffer, sizeof(buffer)) < 0) {
        perror("read");
        close(fd);
        exit(1);
    }
    
    // Close the file
    close(fd);
    
    // Print the received message
    printf("Received message: %s\n", buffer);
    
    return 0;
}

