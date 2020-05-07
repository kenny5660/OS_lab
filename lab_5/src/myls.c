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

int main(int argv,char ** argc){
    // struct stat st;
    // stat(argc[1],&st);
    int stat_mode = 0;
    char* dir_name = argc[argv-1];

    if (argv > 1 && argc[1][0] == '-' && argc[1][1] == 'l'){
        stat_mode = 1;
    }
    if(argv < 2 | (argv < 3 && stat_mode == 1)){
        dir_name = malloc(256);
        getcwd(dir_name,256);
    }
    DIR* dir = opendir(dir_name);
    struct dirent* obj;
    while((obj = readdir(dir)) != NULL){
        if (stat_mode == 0)
        {
            if(obj->d_name[0] != '.'){
            printf("%s ", obj->d_name);
            }
        }
        else{
            struct stat st;
            stat(obj->d_name,&st);
            char obj_type = st.st_mode & S_IFDIR ? 'd': '-';
            char obj_user_perm_r = st.st_mode & S_IRUSR ? 'r': '-';
            char obj_user_perm_w = st.st_mode & S_IWUSR ? 'w': '-';
            char obj_user_perm_x = st.st_mode & S_IXUSR ? 'x': '-';
            printf("%c%c%c%c %d %s %s %d %s\n",obj_type,obj_user_perm_r,obj_user_perm_w,obj_user_perm_x,st.st_nlink,
                                            getpwuid(st.st_uid)->pw_name,getgrgid(st.st_gid)->gr_name, st.st_size,obj->d_name);
        }
    }
printf("\n");
}