#define _GNU_SOURCE

#include <dirent.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define WHITE "\x1b[37m"
#define RED "\x1b[31m"

int check_path(const char *path) {
    struct stat st;
    if (stat(path, &st) == -1)
        return 0;

    return 1;
}

void fill_cur_file_stat(const char *path, struct stat *st) {
    stat(path, st);
}

unsigned int get_file_mode(struct stat st) {
    return st.st_mode;
}

int is_dir(struct stat st) {
    return (get_file_mode(st) & S_IFMT) == S_IFDIR;
}

int is_dir_by_path(const char *path) {
    struct stat st;
    stat(path, &st);
    return (st.st_mode & S_IFMT) == S_IFDIR;
}

int is_fifo(struct stat st) {
    return (get_file_mode(st) & S_IFIFO) == S_IFIFO;
}

int is_exec(struct stat st) {
    return (get_file_mode(st) & S_IEXEC) == S_IEXEC;
}

unsigned long get_inode(struct stat st) {
    return st.st_ino;
}

void fill_rights(char rights_buffer[], struct stat st) {
    mode_t mode = st.st_mode;

    rights_buffer[0] = (mode & S_IFDIR) ? 'd' : '-';
    rights_buffer[1] = (mode & S_IRUSR) ? 'r' : '-';
    rights_buffer[2] = (mode & S_IWUSR) ? 'w' : '-';
    rights_buffer[3] = (mode & S_IXUSR) ? 'x' : '-';
    rights_buffer[4] = (mode & S_IRGRP) ? 'r' : '-';
    rights_buffer[5] = (mode & S_IWGRP) ? 'w' : '-';
    rights_buffer[6] = (mode & S_IXGRP) ? 'x' : '-';
    rights_buffer[7] = (mode & S_IROTH) ? 'r' : '-';
    rights_buffer[8] = (mode & S_IWOTH) ? 'w' : '-';
    rights_buffer[9] = (mode & S_IXOTH) ? 'x' : '-';
}

unsigned long get_links_count(struct stat st) {
    return st.st_nlink;
}

int fill_user_name(char **name, struct stat st) {
    struct passwd *pswd = getpwuid(st.st_uid);

    if (pswd == NULL)
        return 0;

    *name = (char *)calloc(strlen(pswd->pw_name) + 1, sizeof(char));
    strcpy(*name, pswd->pw_name);

    return 1;
}

char *get_modify_time(struct stat st) {
    struct timespec ts = st.st_mtim;
    char *mt = strdup(ctime(&ts.tv_sec));
    mt[strlen(mt) - 9] = 0;
    return mt;
}

void print_info(struct stat st) {
    char rights_buffer[10];
    char *name = NULL;
    char *t = get_modify_time(st);
    fill_rights(rights_buffer, st);
    fill_user_name(&name, st);
    printf(WHITE "%10s ", rights_buffer);
    printf("%2ld ", get_links_count(st));
    printf("%s ", name);
    printf("%ld ", st.st_size);
    printf("%s ", t + 4);
}

void ls(const char *path, int file_suffix, int hidden, int info) {
    if (!check_path(path)) {
        printf(RED "ls: cannot access '%s': No such file or directory\n" WHITE, path);
        return;
    }

    struct stat cur_file_stat;

    fill_cur_file_stat(path, &cur_file_stat);

    if (!is_dir(cur_file_stat)) {

        if (info) {
            print_info(cur_file_stat);
        }
        printf(GREEN "%s%s\n" WHITE, path, file_suffix ? is_exec(cur_file_stat) ? "*" : is_fifo(cur_file_stat) ? "|" : "" : "");
        return;
    }

    DIR *dir = opendir(path);

    struct dirent *entry;

    for (entry = readdir(dir); entry != NULL; entry = readdir(dir)) {
        fill_cur_file_stat(entry->d_name, &cur_file_stat);
        if (!hidden) {
            if (!strcmp(entry->d_name, "."))
                continue;
            else if (!strcmp(entry->d_name, ".."))
                continue;
        }

        if (is_dir_by_path(entry->d_name)) {
            if (info) {
                print_info(cur_file_stat);
                printf(GREEN "%s%s    " WHITE, entry->d_name, file_suffix ? "/" : "");
                printf("\n");
                continue;
            }
            printf(GREEN "%s%s    " WHITE, entry->d_name, file_suffix ? "/" : "");

        } else {
            if (info) {
                print_info(cur_file_stat);
                printf(BLUE "%s%s    " WHITE, entry->d_name, file_suffix ? is_exec(cur_file_stat) ? "*" : is_fifo(cur_file_stat) ? "|" : "" : "");
                printf("\n");
                continue;
            }
            printf(BLUE "%s%s    " WHITE, entry->d_name, file_suffix ? is_exec(cur_file_stat) ? "*" : is_fifo(cur_file_stat) ? "|" : "" : "");
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        char *cur_dir = get_current_dir_name();
        ls(cur_dir, 0, 0, 0);
        free(cur_dir);
        printf("\n");
        return 0;
    } else {
        int i;
        int file_suffix = 0;
        int hidden = 0;
        int show_info = 0;
        int has_files = 0;
        for (i = 1; i < argc; i++) {
            if (argv[i][0] == '-') {
                int j;
                for (j = 1; j < (int)strlen(argv[i]); j++) {
                    switch (argv[i][j]) {
                    case 'l':
                        show_info = 1;
                        break;
                    case 'a':
                        hidden = 1;
                        break;
                    case 'F':
                        file_suffix = 1;
                        break;
                    default:
                        break;
                    }
                }
            } else {
                has_files = 1;
            }
        }

        if (!has_files) {
            char *cur_dir = get_current_dir_name();
            ls(cur_dir, file_suffix, hidden, show_info);
            free(cur_dir);
            printf("\n");
            return 0;
        } else {
            for (i = 1; i < argc; i++) {
                if (argv[i][0] != '-')
                    ls(argv[i], file_suffix, hidden, show_info);
            }
        }
    }

    printf("\n");

    return 0;
}
