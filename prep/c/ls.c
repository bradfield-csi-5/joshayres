#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(int argc, char **argv)
{
    char *buf = malloc(1024);
    size_t size = 1024;
    const char *cwd = getcwd(buf, size);

    char *path = malloc(1024);
    strcpy(path, cwd);
    // parse flags here
    if(argc > 1)
    {
        sprintf(path, "%s/%s", cwd, argv[argc-1]);
    }

    DIR *dir = opendir(path);

    struct dirent *info = readdir(dir);
    while(info != NULL)
    {
        unsigned char *type;
        switch(info->d_type){
        case DT_BLK:
            type = ANSI_COLOR_GREEN;
            break;
        case DT_CHR:
            type = ANSI_COLOR_RED;
            break;
        case DT_DIR:
            type = ANSI_COLOR_CYAN;
            break;
        case DT_FIFO:
            break;
        case DT_LNK:
            type = ANSI_COLOR_YELLOW;
            break;
        case DT_REG:
            type = ANSI_COLOR_BLUE;
            break;
        case DT_SOCK:
            type = ANSI_COLOR_MAGENTA;
            break;
        default:
            type = "";
            break;
        }
        printf("%s%s " ANSI_COLOR_RESET, type, info->d_name);
        info = readdir(dir);
    }
    printf("\n");
    
    return 0;
}
