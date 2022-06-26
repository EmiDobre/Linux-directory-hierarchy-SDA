//DOBRE EMILIA ILIANA 315CB

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

//arbore fis
typedef struct nodFile {
    char* name;
    struct nodFile * left;
    struct nodFile * right;
    struct directory* parent_dir;
} TOneFile, *TArbFile;

//director
typedef struct directory {
    char* name;
    struct directory* parent;
    struct directory* current_subdir;  
    TArbFile files;
    struct directory* right; 
    struct directory* left;

} TOneDir,*TDirectory;

//fct arb file:

TArbFile CreateLeafFile(char* name, TDirectory parent);
TArbFile InsertFile(TArbFile arb, char* name, TDirectory parent );

TDirectory LeafDir ( char* name, TDirectory parent);
TDirectory InsertInSubdir (TDirectory sub, char* name, TDirectory parent);

TDirectory SearchDir(TDirectory subdir, char* name);
TArbFile SearchFile(TArbFile files, char* name );

TArbFile DeleteFile(TArbFile files, char* name );
TArbFile ParentFile(TArbFile files, char* name);
TArbFile MinimFile(TArbFile subfiles);

TDirectory DeleteDir(TDirectory subdir, char* name, TDirectory all_dir);
TDirectory MinimDirectoy(TDirectory subdir);
TDirectory ParentDir(TDirectory subdir, char* name);

void SRD(void* a, char tip);
