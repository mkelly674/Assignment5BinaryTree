/*
            COP 3502C Assignment 3502C
    This program is written by: Michael Kelly
*/

#include <stdio.h>
#include <stdlib.h>

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
        createNode(fine, name);
        return;
    }
    
}
int main()
{
    printf("Hello World");

    return 0;
}
