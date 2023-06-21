#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

enum flags
{
    NONE = 0,
    ALL = 1,
    LONG = 2,
    SIZE = 4,
    LIST = 8,
};

int list(const char* path, enum flags flag)
{
    DIR *dir = opendir(path);

    struct dirent *info = readdir(dir);
    while(info != NULL)
    {
        if(!flag&ALL) {
            if(info->d_name[0] == '.') {
                info = readdir(dir);
                continue;
            }
        }
        struct stat stat_buf;
        stat(info->d_name, &stat_buf);
        unsigned char *type;
        switch(stat_buf.st_mode & S_IFMT){
        case S_IFBLK:
            type = ANSI_COLOR_GREEN;
            break;
        case S_IFCHR:
            type = ANSI_COLOR_RED;
            break;
        case S_IFDIR:
            type = ANSI_COLOR_CYAN;
            break;
        case S_IFIFO:
            break;
        case S_IFLNK:
            type = ANSI_COLOR_YELLOW;
            break;
        case S_IFREG:
            type = ANSI_COLOR_BLUE;
            break;
        case S_IFSOCK:
            type = ANSI_COLOR_MAGENTA;
            break;
        default:
            type = ""; break;
        }
        printf("%s%s %d " ANSI_COLOR_RESET, type, info->d_name, stat_buf.st_size);
        info = readdir(dir);
    }
    printf("\n");
    
    closedir(dir);
}


int main(int argc, char **argv)
{
    enum flags flag = NONE;
    char *file = ".";
    for(int i = 1; i < argc; i++)
    {
        if(argv[i][0] == '-')
        {
            if(argv[i][1] == 'a') {
                flag += ALL;
            }
            continue;
        } else {
            strcpy(file, argv[i]);
        }
    }
    list(file, flag);

    return 0;
}
