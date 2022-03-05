#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE_SIZE 300

struct Dir;
struct File;
typedef struct Stack{
    struct node *top;
    int len;
} Stack;
typedef struct node{
    struct node *next;
    char *data;
} node;
typedef struct Dir{
	char *name;
	struct Dir* parent;
	struct File* head_children_files;
	struct Dir* head_children_dirs;
	struct Dir* next;
} Dir;

typedef struct File {
	char *name;
	struct Dir* parent;
	struct File* next;
} File;
void initStack(Stack **stack){
    (*stack) = malloc(sizeof(Stack));
    (*stack)->top=NULL;
    (*stack)->len=0;
}
int is_empty(Stack *stack){
    if(stack->len<=0)
        return 1;
    return 0;
}
void add_stack(Stack *stack, char *data){
    node *nodStack;
    nodStack=(node*)malloc(sizeof(node));
    //nodStack->data=(char*)malloc((strlen(data)+2)*sizeof(char));
    nodStack->data=data;
    nodStack->next=stack->top;
    stack->top=nodStack;
    stack->len++;
}
void pop_stack(Stack *stack){
    //char *sir;
    if(stack->len<=0)
        {
            printf("nu!");
            return;
        }
    node *nodStack;
    nodStack=stack->top;
    stack->top=stack->top->next;
    free(nodStack);
    stack->len--;
}
void freeStack(Stack **stack){
    node *nodstack=(*stack)->top;
    while(nodstack->next!=NULL){
        nodstack=(*stack)->top;
        (*stack)->top=(*stack)->top->next;
        free(nodstack->data);
        free(nodstack);
    }
    nodstack=(*stack)->top;
    free(nodstack->data);
    free(nodstack);
    free(*stack);
}
Dir * initDir(char *nume){
    Dir * radacina;
    radacina = (Dir*)malloc(sizeof(Dir));
    int lenDir=strlen(nume);
    radacina->name=(char*)malloc((lenDir+1)*sizeof(char));
    strcpy(radacina->name,nume);
    radacina->next=NULL;
    radacina->head_children_dirs=NULL;
    radacina->head_children_files=NULL;
    radacina->parent=NULL;
    return radacina;
}
File * initFile(char * nume){
    File * fisier;
    fisier = (File*) malloc(sizeof(File));
    int lenFile = strlen(nume);
    fisier->name=(char*)malloc((lenFile+1)*sizeof(char));
    strcpy(fisier->name,nume);
    fisier->next=NULL;
    fisier->parent=NULL;
}
void freeDir(Dir ** radacina){

    
        File *fisierSters=(*radacina)->head_children_files;
        Dir *directorSters=(*radacina)->head_children_dirs;
        while((*radacina)->head_children_files!=NULL){
            fisierSters=(*radacina)->head_children_files;
            (*radacina)->head_children_files=(*radacina)->head_children_files->next;
            free(fisierSters->name);
            free(fisierSters);
        }
        while((*radacina)->head_children_dirs!=NULL){
            directorSters=(*radacina)->head_children_dirs;
            (*radacina)->head_children_dirs=(*radacina)->head_children_dirs->next;
            freeDir(&directorSters);
        }
        free((*radacina)->name);
        free((*radacina));
        
    
}
void touch (Dir* parent, char* name) {
     File *fisier;//=initFile(name);
     if(parent->head_children_files==NULL)
        {
        fisier=initFile(name);
        parent->head_children_files=fisier;
        fisier->parent=parent;
        }
    else
    {
        File *fisAux=parent->head_children_files;
        while(fisAux->next!=NULL){
            if(strcmp(fisAux->name,name)==0)
               {
                   printf("File already exists\n");
                   return;
               }
               fisAux=fisAux->next;
        }
        if(strcmp(fisAux->name,name)==0)
            {
                printf("File already exists\n");
                return;
            }
        fisier=initFile(name);
        fisAux->next=fisier; 
        fisier->parent=parent;
    }

}
void mkdir (Dir* parent, char* name) {
     Dir * directorNou;
     if(parent->head_children_dirs==NULL)
     {
         directorNou=initDir(name);
         parent->head_children_dirs=directorNou;
         directorNou->parent=parent;
     }
     else
    {
        Dir *dirAux=parent->head_children_dirs;
        while(dirAux->next!=NULL){
            if(strcmp(dirAux->name,name)==0)
               {
                   printf("Directory already exists\n");
                   return;
               }
               dirAux=dirAux->next;
        }
        if(strcmp(dirAux->name,name)==0)
            {
                 printf("Directory already exists\n");
                 return;
            }
        directorNou=initDir(name);
        dirAux->next=directorNou; 
        directorNou->parent=parent;
    }

}
void ls (Dir* parent) {
    Dir * auxDir=parent->head_children_dirs;
    File * auxFile=parent->head_children_files;
    while(auxDir!=NULL)
          {
              printf("%s",auxDir->name);
              auxDir=auxDir->next;
          }  
     while(auxFile!=NULL)
          {
              printf("%s",auxFile->name);
              auxFile=auxFile->next;        
          } 
}

void rm (Dir* parent, char* name) {
    File *fisier,*fisierAux;
    if(parent->head_children_files==NULL)
        {
        printf("Could not find the file\n");
        return;
        }
    if(!strcmp(parent->head_children_files->name,name))
        {
        fisierAux=parent->head_children_files;
        parent->head_children_files=parent->head_children_files->next;
         free(fisierAux->name);
                free(fisierAux);
        return;
        }
    fisier=parent->head_children_files;
    while(fisier->next!=NULL){
        if(!strcmp(fisier->next->name,name))
            {
                fisierAux=fisier->next;
               fisier->next=fisier->next->next;
                free(fisierAux->name);
                free(fisierAux);
                return;
            }
        fisier=fisier->next;
    }
    printf("Could not find the file\n");
}

void rmdir (Dir* parent, char* name) {
    Dir *directorSters,*directorAux;
    if(parent->head_children_dirs==NULL)
        {
        printf("Could not find the dir\n");
        return;
        }
    if(strcmp(parent->head_children_dirs->name,name)==0)
        {
           directorSters=parent->head_children_dirs;
           parent->head_children_dirs=parent->head_children_dirs->next; 
           freeDir(&directorSters);
           return;
        }
    directorSters=parent->head_children_dirs;
    while(directorSters->next!=NULL){
        if(!strcmp(directorSters->next->name,name))
            {
                directorAux=directorSters->next;
                directorSters->next=directorSters->next->next;
                freeDir(&directorAux);
                return;
            }     
        directorSters=directorSters->next;    
    }
    printf("Could not find the dir\n");
}

void cd(Dir** target, char *name) {
    if(strcmp(name,"..\n")==0)
        {
            if((*target)->parent!=NULL)
                (*target)=(*target)->parent;
            return;
        }
    Dir *cautaDir=(*target)->head_children_dirs;
    while(cautaDir!=NULL){
        if(strcmp(cautaDir->name,name)==0)
        {
             (*target)=cautaDir;
            return;
        }
        cautaDir=cautaDir->next;
    }
    printf("No directories found!\n");
}

char *pwd (Dir* target) {
    char *cale;
    int lungimeTotala=0,sizeDir;
    Stack *stack;
    initStack(&stack);
    while(target!=NULL){
        sizeDir=strlen(target->name);
        lungimeTotala+=sizeDir;
        if(target->name[sizeDir-1]=='\n')
            target->name[sizeDir-1]='\0';
        add_stack(stack,target->name);
        target=target->parent;
    }
    cale=malloc((lungimeTotala+2)*sizeof(char));
    strcpy(cale,"");
    while(stack->len>0)
    {       
        strcat(cale,"/");

        strcat(cale,stack->top->data);
        pop_stack(stack);
    }
    free(stack);
    //freeStack(&stack);
    return cale;
}

void stop (Dir* target) {}
void afisareSpatii(int level){
    int i;
    for(i=1;i<=level;i++)
        fputs("    ",stdout);
}
void tree (Dir* target, int level) {
    
    Dir *dirAux;
    File *fileAux;
    dirAux=target->head_children_dirs;
    while(dirAux!=NULL){
        afisareSpatii(level);
        fputs(dirAux->name,stdout);
        tree(dirAux,level+1);
        dirAux=dirAux->next;
    }
    fileAux=target->head_children_files;
    while(fileAux!=NULL){
        afisareSpatii(level);
        fputs(fileAux->name,stdout);
        fileAux=fileAux->next;
    }
}

void mv(Dir* parent, char *oldname, char *newname) {
    Dir * dirAux=parent->head_children_dirs,*dirAux2;
    File * filAux=parent->head_children_files, *filAux2=filAux;
    int lenNewname;
    if(dirAux==NULL)
        goto file;
    while(dirAux!=NULL){
        if(strcmp(dirAux->name,newname)==0){
            printf("File/Director already exists\n");
            return;
         }
        if(strcmp(dirAux->name,oldname)==0){
            dirAux2=dirAux->next;
            while(dirAux2!=NULL){
                if(strcmp(dirAux2->name,newname)==0){
                    printf("File/Director already exists\n");
                    return;
                }
                dirAux2=dirAux2->next;
            }
            while(filAux!=NULL){
                    if(strcmp(filAux->name,newname)==0){
                      printf("File/Director already exists\n");
                      return;
                    }
                    filAux=filAux->next;
                 }
            mkdir(parent,newname);
            rmdir(parent,oldname);
            return;
            }
            dirAux=dirAux->next;
         } 
file:
    if(filAux==NULL)
        goto end_mv;
    while(filAux!=NULL){
        if(strcmp(filAux->name,newname)==0){
            printf("File/Director already exists\n");
            return;
        }
        if(strcmp(filAux->name,oldname)==0){
            filAux2=filAux->next;
            while(filAux2!=NULL){
                if(strcmp(filAux2->name,newname)==0){
                    printf("File/Director already exists\n");
                    return;
                }
                filAux2=filAux2->next;
            }
             while(dirAux!=NULL){
               if(strcmp(dirAux->name,newname)==0){
                  printf("File/Director already exists\n");
                  return;
                }
                dirAux=dirAux->next;
            }
            touch(parent,newname);
            rm(parent,oldname);
            return;
        }
        filAux=filAux->next;
    }
end_mv:
    printf("File/Director not found\n");
}
int main () {
	char *stringReader,*cale,*oldname,*newname,*token;
    Dir *radacina,*dirCurent;
    radacina=initDir("home");
    dirCurent=radacina;
	stringReader = (char*) malloc((MAX_INPUT_LINE_SIZE+1)*sizeof(char));
	do
	{
		fgets(stringReader,MAX_INPUT_LINE_SIZE,stdin);
		if(strstr(stringReader,"touch ")!=NULL)
           {
               touch(dirCurent,stringReader+6);
           }
        if(strstr(stringReader,"ls\n")!=NULL)
           {
               ls(dirCurent);
           }
        if(strstr(stringReader,"mkdir ")!=NULL)
           {
               mkdir(dirCurent,stringReader+6);
           }
        if(strstr(stringReader,"rm ")!=NULL)
        {
            rm(dirCurent,stringReader+3);
        }
          if(strstr(stringReader,"rmdir ")!=NULL)
        {
            rmdir(dirCurent,stringReader+6);
        }
        if(strstr(stringReader,"cd ")!=NULL)
        {
            cd(&dirCurent,stringReader+3);
        }
        if(strcmp(stringReader,"tree\n")==0)
        {
            tree(dirCurent,0);
        }
        if(strcmp(stringReader,"pwd\n")==0)
        {
            cale=pwd(dirCurent);
            printf("%s\n",cale);
            free(cale); 
        }
        if(strstr(stringReader,"mv ")!=NULL)
        {
            int i,lung;
            token=stringReader+3;
            for(i=0;token[i]!=' ';i++){

            }
            lung=strlen(token);
            oldname=(char*)malloc((i+3)*sizeof(char));
            newname=(char*)malloc((lung-i)*sizeof(char));
            strncpy(oldname,token,i);
            oldname[i]='\n';
            oldname[i+1]='\0';
            strcpy(newname,token+i+1);
            //newname=stringReader+i+1;
            mv(dirCurent,oldname,newname);
            free(newname);
            free(oldname);
        }
    } while (strcmp(stringReader,"stop\n"));
    freeDir(&radacina);
    free(stringReader);
    return 0;
}
