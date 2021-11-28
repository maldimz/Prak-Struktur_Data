#include <iostream>
#include <malloc.h>

using namespace std;

typedef struct node *typenode;
typedef int typeinfo;

bool check = false;

struct node
{
    typeinfo info;
    char name[30];
    typenode up, down;
};

typenode top, bottom;

bool isEmpty(){
    if(top == NULL){
        return true;
    }else{
        return false;
    }
}


void createlist()
{
    typenode first;

    first = (node*)malloc(sizeof(node));
    first = NULL;
    top = first;
    bottom = first;
}

void addStack(node input){
    typenode NI;
    

    NI = (node*)malloc(sizeof(node));
    NI->info = input.info;

    for(int i=0; i<=30;i++){
        NI->name[i] = input.name[i];
    }
    
    if(isEmpty()){
        NI->up=NULL;
        NI->down=NULL;
        top = NI;
        bottom = NI;
    }else{
        NI->up=NULL;
        top->up=NI;
        NI->down=top;
        top=NI;
    }

    if(check){
        FILE *fp;
        fp = fopen ("stack_file.dat" , "a");
        fwrite(&input, sizeof(node), 1, fp);
        fclose(fp);
    }
}

void takeStack(){
    typenode helper;
    node input;

    helper = top;

    if(isEmpty()){
        puts("Is empty");
    }else{
        top=helper->down;
        if(top!=NULL){
            free(helper);
            top->up=NULL;
        }else{
            free(top);
            free(bottom);
            createlist();
        }
    }

    if(check){
        helper = bottom;
        FILE *fp;
        fp = fopen ("stack_file.dat" , "w");
        while(helper!=NULL){
            input.info = helper->info;
            for(int i=0; i<=30;i++){
                input.name[i] = helper->name[i];
            }
            helper=helper->up;
            fwrite(&input, sizeof(node), 1, fp);
            
        }
        fclose(fp);
    }
}

void printStack(){
    if(!isEmpty()){
        typenode helper;

        helper=top;

        puts("\nPrint Stack");
        while(helper!=NULL){
            printf("%d   %s \n", helper->info, helper->name);
            helper=helper->down;
        }
    }else{
        puts("Is Empty!");
    }
};

void getData(){
    node ID;

    FILE *fp;
    fp = fopen ("stack_file.dat" , "r");
    if(fp != NULL){
        while(fread(&ID, sizeof(node), 1, fp)){
            addStack(ID);
        }
    }
    fclose(fp);
    check = true;
}

int main()
{
    createlist();
    getData();
    char loop='y';
    int pil;
    node data;

    while(loop=='Y' || loop =='y')
    {
        system("cls");

        puts("Menu");
        puts("1. Add Stack");
        puts("2. Take Stack");
        puts("3. Print Stack");
        printf("Choice : "); cin >> pil;   

        switch (pil)
        {
        case 1:
            printf("\nAdd number : "); cin >> data.info;
            printf("Name : "); cin.ignore(); cin.getline(data.name, 30);
            addStack(data);
            break;

        case 2:
            takeStack();
            break;

        case 3:
            printStack();
            break;
        
            default:
            break;
        } 

        printf("Back To Home? (y/n)"); cin >> loop;
    }



    return 0;
}