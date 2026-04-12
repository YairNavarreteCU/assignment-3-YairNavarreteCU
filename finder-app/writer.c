#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    int fileDescriptor;

    openlog("writer", LOG_PID, LOG_USER);

    if (argc < 3 || argv[1][0] == '\0' || argv[2][0] == '\0') {
        printf("Arguments not specified");
        syslog(LOG_ERR, "Invalid Arguments");
        closelog();
        return 1;
    }

    fileDescriptor = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fileDescriptor < 0) {
        printf("File could not be created");
        syslog(LOG_ERR, "File could not be created");
        closelog();
        return 1;
    }

    write(fileDescriptor, argv[2], strlen(argv[2]));
    syslog(LOG_DEBUG, "Writing %s to %s", argv[2], argv[1]);

    close(fileDescriptor);
    closelog();

    return 0;
}
