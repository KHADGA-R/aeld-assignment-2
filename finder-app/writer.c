
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char *argv[])
{
    /* Check that exactly two command-line arguments were provided.
     * argv[1] = file to write
     * argv[2] = string to write
     */
    if (argc != 3)
    {
        fprintf(stderr, "Error: two arguments are required\n");
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    /* Initialize syslog using the LOG_USER facility. */
    openlog("writer", LOG_PID, LOG_USER);

    /* Open the requested file for writing.
     * "w" creates the file if it does not exist and
     * overwrites the file if it already exists.
     */
    FILE *file = fopen(writefile, "w");

    if (file == NULL)
    {
        syslog(LOG_ERR, "Error: could not open file %s", writefile);
        fprintf(stderr, "Error: could not open file %s\n", writefile);
        closelog();
        return 1;
    }

    /* Write the supplied string to the file. */
    if (fprintf(file, "%s\n", writestr) < 0)
    {
        syslog(LOG_ERR, "Error: could not write to file %s", writefile);
        fprintf(stderr, "Error: could not write to file %s\n", writefile);

        fclose(file);
        closelog();
        return 1;
    }

    /* Close the file and check for errors. */
    if (fclose(file) != 0)
    {
        syslog(LOG_ERR, "Error: could not close file %s", writefile);
        fprintf(stderr, "Error: could not close file %s\n", writefile);

        closelog();
        return 1;
    }

    /* Log successful write using LOG_DEBUG as required. */
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    closelog();

    return 0;
}

