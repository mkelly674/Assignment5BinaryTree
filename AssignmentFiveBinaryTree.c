/*
            COP 3502C Assignment 3502C
    This program is written by: Michael Kelly
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

struct Node{
    int fine;
    char * name;
    Node * Left;
    Node * Right;
};

Node * createNode(int fine, char * name){
    Node * temp;
    temp->fine = fine;
    temp->name = name;
    temp->Left = NULL;
    temp->Right = NULL;
    return temp;
}

void insertion(Node * root, int fine, char * name){
    if(root == NULL){
        root = createNode(fine, name);
        return;
    }
    
}

int add(Node * root, int fine, char * name){

}

int deduc(Node * root, int deduct, char * name){

}

Node * root(Node * root, char * name){

}

int average(Node * root){

}

int main(){
    //get the number of commands
    int numcom = 0;
    scanf("%d", &numcom);

    //get the command
    char command[15];

    //get the Node
    Node * root;

    //get the fine
    int fin = 0;

    //get the deduction
    int deduc = 0;

    //get the name
    char * name;

    for(int i = 0; i < numcom; i++){

        scanf("%s", &command);

        if(strcmp(command, "add") == 0){
            //get the fine to be added
            scanf("%d", &fin);

            //get the name to be added
            scanf("%s", &name);

            root->fine = add(root, fin, name);
        }

        if(strcmp(command, "deduct") == 0){
            //get the amount deducted
            scanf("%d", &deduc);

            //get the name
            scanf("%s", &name);


        }

        if(strcmp(command, "search") == 0){
            //get the name
            scanf("%s", &name);

            Node * temp = search(root, name);
        }

        if(strcmp(command, "average") == 0){
            //get the average
            int ave = 0;

            ave = average(root);

            printf("%d \n", ave);
        }

        if(strcmp(command, "height_balance") == 0){
            //get the height
            int hei = 0;

            hei = height_balance(root);

            printf("%d \n", hei);
        }

        if(strcmp(command, "calc_below") == 0){
            
        }

    }

    return 0;
}
