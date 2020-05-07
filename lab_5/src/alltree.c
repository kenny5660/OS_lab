#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

int cur_deth = 0;
int max_deth = 2;
void print_tree(char* dir_name){
    DIR* dir = opendir(dir_name);

    struct dirent* obj;
    while((obj = readdir(dir)) != NULL){
        if(obj->d_type & DT_DIR){
            if(obj->d_name[0] != '.'){
                int path_length;
                char path[PATH_MAX];
 
                path_length = snprintf (path, PATH_MAX,
                                        "%s/%s", dir_name, obj->d_name);
                printf ("%s*\n", path);
                if (path_length >= PATH_MAX) {
                    fprintf (stderr, "Path length has got too long.\n");
                    exit (EXIT_FAILURE);
                }
                if(cur_deth != max_deth){
                    ++cur_deth;
                    print_tree (path);
                    --cur_deth;
                }
            }
        }
        else{
            if(obj->d_name[0] != '.'){
            printf("%s\n", obj->d_name);
            }
        }
    }
    closedir(dir);
}

int main(int argv,char ** argc){
    // struct stat st;
    // stat(argc[1],&st);
    int stat_mode = 0;
    char* dir_name;
    if (argc[1][0] == '-' && argc[1][1] == 'd'){
        if(argc[1][2] == '\0'){
            max_deth = atoi(argc[2]) -1;
        }
        else{
            max_deth = atoi((argc[1]+2)) -1;
        }
    }

    if(argv < 2){
        dir_name = malloc(256);
        getcwd(dir_name,256);
    }
    else{
        dir_name = argc[argv-1];
    }
    print_tree(dir_name);
}