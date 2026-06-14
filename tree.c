#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

static int is_hidden(const char *name)
{
    return name[0] == '.';
}

static void print_tree(const char *path, const char *prefix)
{
    DIR *dir;
    struct dirent *entry;
    char **names = NULL;
    int count = 0;
    int i;

    dir = opendir(path);
    if (!dir)
        return;

    while ((entry = readdir(dir)) != NULL)
    {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;
        if (is_hidden(entry->d_name))
            continue;

        names = realloc(names, sizeof(char *) * (count + 1));
        if (!names)
            exit(1);
        names[count] = strdup(entry->d_name);
        if (!names[count])
            exit(1);
        count++;
    }
    closedir(dir);

    for (i = 0; i < count; i++)
    {
        char fullpath[4096];
        struct stat st;
        int is_last = (i == count - 1);

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, names[i]);

        printf("%s%s%s\n", prefix, is_last ? "└── " : "├── ", names[i]);

        if (lstat(fullpath, &st) == 0 && S_ISDIR(st.st_mode))
        {
            char new_prefix[4096];

            snprintf(new_prefix, sizeof(new_prefix), "%s%s",
                     prefix, is_last ? "    " : "│   ");
            print_tree(fullpath, new_prefix);
        }

        free(names[i]);
    }

    free(names);
}

int main(int argc, char **argv)
{
    const char *path = ".";

    if (argc >= 2)
        path = argv[1];

    printf("%s\n", path);
    print_tree(path, "");

    return 0;
}
