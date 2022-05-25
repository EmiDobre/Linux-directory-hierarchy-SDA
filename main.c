//DOBRE EMILIA ILIANA 315CB

#include "terminal.h"
//#define DEBUG_MODE 1
//#ifndef DEBUG_MODE
//de pus mereu printf 
//#endif

int main() {

    char input[10000];
   
    TDirectory root = NULL;
    TDirectory cd_dir = NULL;
    root = LeafDir ("root", NULL);
    cd_dir = LeafDir("root", NULL);


    while ( fgets(input, 10000, stdin) != NULL ) {
        if ( strncmp(input, "mkdir", 5) == 0 ) {
            char* dir_name = calloc(51, sizeof(char));
        
            memcpy(dir_name, input+6, strlen(input+6));
            dir_name[strlen(dir_name) - 1] = '\0';
            //printf("->ADDAmkdir in %s: .%s.\n", cd_dir->name,dir_name);

            if ( strcmp(cd_dir->name,"root") == 0 ) {
                if ( SearchFile(root->files, dir_name ) != NULL ){
                    printf("File %s already exists!\n", dir_name);
                } else {
                    if ( SearchDir(root->current_subdir, dir_name) != NULL )
                        printf("Directory %s already exists!\n", dir_name);
                    else
                        root->current_subdir = InsertInSubdir(root->current_subdir, dir_name, root);
                }
            } else {
                if ( SearchFile(cd_dir->files, dir_name ) != NULL ){
                    printf("File %s already exists!\n", dir_name);
                } else {
                    if ( SearchDir(cd_dir->current_subdir, dir_name) != NULL )
                        printf("Directory %s already exists!\n", dir_name);
                    else
                        cd_dir->current_subdir = InsertInSubdir(cd_dir->current_subdir, dir_name, cd_dir);
                }
            }

            free(dir_name);
        }

        if( strncmp(input, "touch", 5) == 0 ) {
            char* file_name = calloc(51, sizeof(char));

            memcpy(file_name, input+6, strlen(input+6));
            file_name[strlen(file_name) - 1] = '\0';
            //printf("->touch in %s: .%s.\n\n", cd_dir->name,file_name);

            if ( strcmp(cd_dir->name,"root") == 0 ) {
                if ( SearchDir(root->current_subdir, file_name) != NULL ){
                    printf("Directory %s already exists!\n", file_name);
                } else {
                    if ( SearchFile(root->files, file_name ) != NULL ) 
                        printf("File %s already exists!\n", file_name);
                    else 
                        root->files = InsertFile(root->files, file_name, root);
                }
            } else {
                if ( SearchDir(cd_dir->current_subdir, file_name) != NULL ){
                    printf("Directory %s already exists!\n", file_name);
                } else {
                    if ( SearchFile(cd_dir->files, file_name ) != NULL ) 
                        printf("File %s already exists!\n", file_name);
                    else 
                        cd_dir->files = InsertFile(cd_dir->files, file_name, cd_dir);
                }
            }

            free(file_name);
        }

        if( strncmp(input, "ls", 2) == 0 ) {
            
            if ( strcmp(cd_dir->name,"root") == 0 ) {
                //printf("->ls in rooot: ");
                SRD(root->current_subdir, 'd');
                SRD(root->files, 'f');
                printf("\n");
            } else {
                //printf("in dir curent %s:\n", cd_dir->name);
                //printf("->ls: ");
                SRD(cd_dir->current_subdir, 'd');
                SRD(cd_dir->files, 'f');
                printf("\n");
            }
        }

        if( strncmp(input, "rm", 2) == 0 && input[2] == ' ' ) {
            char* file_name = calloc(51, sizeof(char));

            memcpy(file_name, input+3, strlen(input+3));
            file_name[strlen(file_name) - 1] = '\0';
            //printf("->rm: .%s.\n", file_name);


            if ( strcmp(cd_dir->name,"root") == 0 ) { 
                if (SearchFile(root->files, file_name) == NULL )
                    printf("File %s doesn't exist!\n", file_name);
                else 
                    {root->files = DeleteFile(root->files, file_name);
                    //printf("    dupa rm: ");
                    //RSD(root->files);
                    }
                //printf("\n\n");
            } else {
                if (SearchFile(cd_dir->files, file_name) == NULL )
                    printf("File %s doesn't exist!\n", file_name);
                else 
                    {cd_dir->files = DeleteFile(cd_dir->files, file_name);
                    //printf("    dupa rm: ");
                    //RSD(cd_dir->files);
                    }
                //printf("\n\n");
            }



            free(file_name);
        }

        if( strncmp(input, "rmdir", 5) == 0 ) {
            char* dir_name = calloc(51, sizeof(char));

            memcpy(dir_name, input+6, strlen(input+6));
            dir_name[strlen(dir_name) - 1] = '\0';
            //printf("->rmdir: .%s.\n\n", dir_name);

            if ( strcmp(cd_dir->name,"root") == 0 ) { 
                if (SearchDir(root->current_subdir, dir_name) == NULL )
                    printf("Directory %s doesn't exist!\n", dir_name);
                else 
                    {root->current_subdir = DeleteDir(root->current_subdir, dir_name);
                    //printf("    dupa rmdir: ");
                    //RSD_dir(root->current_subdir);
                }
                //printf("\n\n");
            } else {
                if (SearchDir(cd_dir->current_subdir, dir_name) == NULL )
                    printf("Directory %s doesn't exist!\n", dir_name);
                else 
                    {cd_dir->current_subdir = DeleteDir(cd_dir->current_subdir, dir_name);
                    //printf("    dupa rmdir: ");
                    //RSD_dir(cd_dir->current_subdir);
                }
                //printf("\n\n");
            }

            free(dir_name);
        }
        
        if( strncmp(input, "cd", 2) == 0 ) {
            char* dir_name = calloc(51, sizeof(char));

            memcpy(dir_name, input+3, strlen(input+3));
            dir_name[strlen(dir_name) - 1] = '\0';
            //printf("->cd: %s\n\n", dir_name);

            if ( strcmp(dir_name, "..") == 0 ) {
                //printf("    SCHIMB LA PARINTE\n");
                if ( cd_dir != NULL && cd_dir->parent != NULL )
                    cd_dir = cd_dir->parent;
            } else {
                
                if ( strcmp(cd_dir->name,"root") == 0 ) {
                    if ( SearchDir(root->current_subdir, dir_name) == NULL)
                        printf("Directory not found!\n");
                    else {
                        cd_dir = SearchDir(root->current_subdir, dir_name);
                        //printf("    Am schimbat directorul la: %s\n", cd_dir->name);
                        //printf("    Parintele este: %s\n", cd_dir->parent->name);
                    }
                } else {
                    if ( SearchDir(cd_dir->current_subdir, dir_name) == NULL)
                        printf("Directory not found!\n");
                    else {
                        cd_dir = SearchDir(cd_dir->current_subdir, dir_name);
                        //printf("    Am schimbat directorul la: %s\n", cd_dir->name);
                        //printf("    Parintele este: %s\n", cd_dir->parent->name);
                    }
                }
            }

            free(dir_name);
        }

        if( strncmp(input, "pwd", 3) == 0 ) {
            PWD(cd_dir);
            printf("\n");
        }

        if ( strncmp(input, "find -f", 7) == 0 ) {
            char* file_name = calloc(51, sizeof(char));
            memcpy(file_name, input+8, strlen(input+8));
            file_name[strlen(file_name) - 1] = '\0';

            printf("Find in %s\n", file_name);

            TDirectory location = NULL;
            //location = FindFileSub(root, file_name);
            location = FindFile(root, file_name);
            if ( location == NULL ) 
                printf("File %s not found!\n", file_name);
            else 
                printf("File found in dir %s\n", location->name);

            free(file_name);
        }

        if ( strncmp(input, "find -d", 7) == 0 ) {
            char* dir_name = calloc(51, sizeof(char));
            memcpy(dir_name, input+8, strlen(input+8));
            dir_name[strlen(dir_name) - 1] = '\0';

            printf("Find in %s\n", dir_name);

            free(dir_name);
        }

    }
    return 0;
}
