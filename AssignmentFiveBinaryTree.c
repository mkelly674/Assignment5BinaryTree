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


//prototypes
Node * search(Node*root, char*name);
Node * createNode(int fine, char * name);
void insertion(Node * root, int fine, char * name);
void add(Node * root, int fine, char * name);
void deduct(Node * root, int deduct, char * name);
int average(Node * root);
int height_balance(Node * root);

Node * createNode(int fine, char * name){
    Node * temp;
    temp->fine = fine;
    temp->name = name;
    temp->Left = NULL;
    temp->Right = NULL;
    return temp;
}

void insertion(Node * root, int fine, char * name){
    //create the node
    if(root == NULL){
        root = createNode(fine, name);
        return;
    }

    //see if the name is in the tree
    Node * temp = search(root, name);

    if(temp != NULL)
        return;
    

    if(strcmp(root->name, name)> 0)
        insertion(root->Left, fine, name);
    
    if(strcmp(root->name, name)< 0)
        insertion(root->Right, fine, name);
    
}

void add(Node * root, int fine, char * name){
    if(search(root, name) == NULL){
        insertion(root, fine, name);
    }
    else{
        Node * res = search(root, name);
        res->fine = res->fine + fine;
    }

}

void deduct(Node * root, int deduct, char * name){

}

Node *search(Node * root, char * name){
    if(root == NULL){
        return root;
    }
    Node * res = root;

    if(strcmp(res->name, name) > 0)
        res = search(res->Left, name);
    
    if(strcmp(res->name, name) < 0)
        res = search(res->Right, name);
        
    
    return res;
}

int average(Node * root){
    int res = 0;

    return res;
}

int height_balance(Node * root){

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

            add(root, fin, name);
        }

        if(strcmp(command, "deduct") == 0){
            //get the amount deducted
            scanf("%d", &deduc);

            //get the name
            scanf("%s", &name);

            deduct(root, deduc, name);
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
