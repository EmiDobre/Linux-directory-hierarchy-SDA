//DOBRE EMILIA ILIANA 315CB

#include "arb.h"

void MKDIR (char* dir_name, TDirectory* root, TDirectory* cd_dir, TDirectory* all_dir);
void TOUCH (char* file_name, TDirectory* root, TDirectory* cd_dir, TArbFile* all_files);
void RM (char* file_name, TDirectory* root, TDirectory* cd_dir, TArbFile* all_files);
void RMDIR (char* dir_name, TDirectory* root, TDirectory* cd_dir, TDirectory* all_dir);
void CD (char* dir_name, TDirectory* root, TDirectory* cd_dir);
void PWD (TDirectory dir);
void FIND_F ( TArbFile all_files, char* name);
void FIND_D ( TDirectory all_dir, char* name);

int main() {

    char input[10000];
    TDirectory root = NULL;
    TDirectory cd_dir = NULL;
    root = LeafDir ("root", NULL);
    cd_dir = LeafDir("root", NULL);

    TArbFile all_files = NULL;
    TDirectory all_dir = NULL;

    while ( fgets(input, 10000, stdin) != NULL ) {
        if ( strncmp(input, "mkdir", 5) == 0 ) {
            char* dir_name = calloc(51, sizeof(char));
            memcpy(dir_name, input+6, strlen(input+6));
            dir_name[strlen(dir_name) - 1] = '\0';
            MKDIR(dir_name, &root, &cd_dir, &all_dir);
            free(dir_name);
        }

        if( strncmp(input, "touch", 5) == 0 ) {
            char* file_name = calloc(51, sizeof(char));
            memcpy(file_name, input+6, strlen(input+6));
            file_name[strlen(file_name) - 1] = '\0';
            TOUCH(file_name, &root, &cd_dir, &all_files);
            free(file_name);
        }

        if( strncmp(input, "ls", 2) == 0 ) {
            
            if ( strcmp(cd_dir->name,"root") == 0 ) {
                SRD(root->current_subdir, 'd');
                SRD(root->files, 'f');
                printf("\n");

            } else {
                SRD(cd_dir->current_subdir, 'd');
                SRD(cd_dir->files, 'f');
                printf("\n");
            }
        }

        if( strncmp(input, "rm", 2) == 0 && input[2] == ' ' ) {
            char* file_name = calloc(51, sizeof(char));
            memcpy(file_name, input+3, strlen(input+3));
            file_name[strlen(file_name) - 1] = '\0';
            RM(file_name, &root, &cd_dir, &all_files);
            free(file_name);
        }

        if( strncmp(input, "rmdir", 5) == 0 ) {
            char* dir_name = calloc(51, sizeof(char));
            memcpy(dir_name, input+6, strlen(input+6));
            dir_name[strlen(dir_name) - 1] = '\0';
            RMDIR(dir_name, &root, &cd_dir, &all_dir);
            free(dir_name);
        }
        
        if( strncmp(input, "cd", 2) == 0 ) {
            char* dir_name = calloc(51, sizeof(char));
            memcpy(dir_name, input+3, strlen(input+3));
            dir_name[strlen(dir_name) - 1] = '\0';
            CD(dir_name, &root, &cd_dir);
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
            FIND_F(all_files, file_name);
            free(file_name);
        }

        if ( strncmp(input, "find -d", 7) == 0 ) {
            char* dir_name = calloc(51, sizeof(char));
            memcpy(dir_name, input+8, strlen(input+8));
            dir_name[strlen(dir_name) - 1] = '\0';
            FIND_D(all_dir, dir_name);
            free(dir_name);
        }
    }
    return 0;
}

void MKDIR (char* dir_name, TDirectory* root, TDirectory* cd_dir, TDirectory* all_dir) {
    
    if ( strcmp((*cd_dir)->name,"root") == 0 ) {
        if ( SearchFile((*root)->files, dir_name ) != NULL )
            printf("File %s already exists!\n", dir_name);
        else {
            if ( SearchDir((*root)->current_subdir, dir_name) != NULL )
                printf("Directory %s already exists!\n", dir_name);
            else
                (*root)->current_subdir = InsertInSubdir((*root)->current_subdir, dir_name, (*root));
        }
            
    } else {
        if ( SearchFile((*cd_dir)->files, dir_name ) != NULL ){
            printf("File %s already exists!\n", dir_name);
        } else {
            if ( SearchDir((*cd_dir)->current_subdir, dir_name) != NULL )
                printf("Directory %s already exists!\n", dir_name);
            else
                (*cd_dir)->current_subdir = InsertInSubdir((*cd_dir)->current_subdir, dir_name, (*cd_dir));
        }
    }
    (*all_dir) = InsertInSubdir((*all_dir), dir_name, (*cd_dir));

}


void TOUCH (char* file_name, TDirectory* root, TDirectory* cd_dir, TArbFile* all_files) {

    if ( strcmp((*cd_dir)->name,"root") == 0 ) {
        if ( SearchDir((*root)->current_subdir, file_name) != NULL ){
            printf("Directory %s already exists!\n", file_name);
        } else {
            if ( SearchFile((*root)->files, file_name ) != NULL ) 
                printf("File %s already exists!\n", file_name);
            else 
                (*root)->files = InsertFile((*root)->files, file_name, (*root));
        }
        
    } else {
        if ( SearchDir((*cd_dir)->current_subdir, file_name) != NULL ){
            printf("Directory %s already exists!\n", file_name);
        } else {
            if ( SearchFile((*cd_dir)->files, file_name ) != NULL ) 
                printf("File %s already exists!\n", file_name);
            else 
                (*cd_dir)->files = InsertFile((*cd_dir)->files, file_name, (*cd_dir));
        }
    }
    (*all_files) = InsertFile((*all_files), file_name, (*cd_dir));

}


void RM(char* file_name, TDirectory* root, TDirectory* cd_dir, TArbFile* all_files) {

    if ( strcmp((*cd_dir)->name,"root") == 0 ) { 
        if (SearchFile((*root)->files, file_name) == NULL )
            printf("File %s doesn't exist!\n", file_name);
        else {
            (*root)->files = DeleteFile((*root)->files, file_name);
            (*all_files) = DeleteFile((*all_files), file_name);
        }

    } else {
        if (SearchFile((*cd_dir)->files, file_name) == NULL )
            printf("File %s doesn't exist!\n", file_name);
        else {
            (*cd_dir)->files = DeleteFile((*cd_dir)->files, file_name);
            (*all_files) = DeleteFile((*all_files), file_name);
        }
    }

}


void RMDIR (char* dir_name, TDirectory* root, TDirectory* cd_dir, TDirectory* all_dir) {

    if ( strcmp((*cd_dir)->name,"root") == 0 ) { 
        if (SearchDir((*root)->current_subdir, dir_name) == NULL )
            printf("Directory %s doesn't exist!\n", dir_name);
        else {
            (*root)->current_subdir = DeleteDir((*root)->current_subdir, dir_name, (*all_dir));
            (*all_dir) = DeleteDir((*all_dir), dir_name, (*all_dir));
        }

    } else {
        if (SearchDir((*cd_dir)->current_subdir, dir_name) == NULL )
            printf("Directory %s doesn't exist!\n", dir_name);
        else {
            (*cd_dir)->current_subdir = DeleteDir((*cd_dir)->current_subdir, dir_name, (*all_dir));
            (*all_dir) = DeleteDir((*all_dir), dir_name, (*all_dir));
        }
    }

}

void CD(char* dir_name, TDirectory* root, TDirectory* cd_dir) {
    if ( strcmp(dir_name, "..") == 0 ) {
        if ( (*cd_dir) != NULL && (*cd_dir)->parent != NULL )
            (*cd_dir) = (*cd_dir)->parent;
    } else {
                
        if ( strcmp((*cd_dir)->name,"root") == 0 ) {
            if ( SearchDir((*root)->current_subdir, dir_name) == NULL)
                printf("Directory not found!\n");
            else 
                (*cd_dir) = SearchDir((*root)->current_subdir, dir_name);
        } else {
            if ( SearchDir((*cd_dir)->current_subdir, dir_name) == NULL)
                printf("Directory not found!\n");
            else 
                (*cd_dir) = SearchDir((*cd_dir)->current_subdir, dir_name);
        }
    }
}

void PWD(TDirectory dir) {
    if ( dir->parent == NULL ) {
        printf("/%s", dir->name);
        return;
    } else {
        PWD(dir->parent);
        printf("/%s", dir->name);
    }
}

void FIND_F ( TArbFile all_files, char* name) {
    TArbFile file = NULL;
    file = SearchFile(all_files, name);
    if ( file == NULL ) 
        printf("File %s not found!\n", name);
    else {
        printf("File %s found!\n", name);
        PWD(file->parent_dir);
        printf("\n");
    }
}


void FIND_D ( TDirectory all_dir, char* name) {
    TDirectory dir = NULL;
    dir = SearchDir(all_dir, name);
    if ( dir == NULL ) {
        printf("Directory %s not found!\n", name);
    } else {
        printf("Directory %s found!\n", name);
        PWD(dir);
        printf("\n");
    }
}
