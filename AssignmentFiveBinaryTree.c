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


//prototypes for nodes
Node * search(Node*root, char*name);
Node * createNode(int fine, char * name);
Node * parent(Node * root, Node * child);
Node * maxVal(Node * root);
Node * minVal(Node* root);

//prototypes for void functions
void insertion(Node * root, int fine, char * name);
void add(Node * root, int fine, char * name);
void deduct(Node * root, int deduct, char * name);
void delete(Node * root, Node * del);

//prototypes for return functions
int average(Node * root);
int height_balance(Node * root);
int calc_below(char * name);
int isLeaf(Node * root);
int rightChildOnly(Node * root);
int leftChildOnly(Node * root);

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

Node * createNode(int fine, char * name){
    Node * temp;
    temp->fine = fine;
    temp->name = name;
    temp->Left = NULL;
    temp->Right = NULL;
    return temp;
}

Node * parent(Node * root, Node * child){
    //base case
    if(root ==NULL)
        return root;

    //found the parent
    if(root->Left == child || root->Right == child)
        return root;
    
    //traverse Left
    if(strcmp(root->name, child->name) > 0)
        return parent(root->Left, child);

    //traverse Right
    if(strcmp(root->name, child->name) < 0)
        return parent(root->Right, child);

    return NULL;
}

Node * maxVal(Node * root){
    //finding the max value
    if(root->Right == NULL)
        return root;

    //traversing
    else
        return maxVal(root->Right);
}

Node * minVal(Node* root){
    //finding the min value
    if(root->Left == NULL)
        return root;

    //traversing
    else 
        return minVal(root->Left);
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
    
    //traverse the tree
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
    if(search(root, name) == NULL)
        return;

    Node * res = search(root, name);
    res->fine = res->fine - deduct;

    if(res->fine <= 0)
    delete(root, res);
}

void delete(Node * root, Node * del){
    if(root == NULL)
    return;

    Node * par = parent(root, del);

    //if root is leaf
    if(isLeaf(root) == 1){
        //simple free
        free(root);
        root = NULL;
    }

    //if root has only left child
    if(leftChildOnly(root) == 1){
        
    }

    //if root has only right child
    if(rightChildOnly(root) == 1){

    }
}


int average(Node * root){
    int res = 0;

    return res;
}

int height_balance(Node * root){

}

int calc_below(char * name){

}

int isLeaf(Node * root){
    // returns 1 if leaf node, 0 otherwise
    return(root->Left == NULL && root->Right == NULL);
}

int rightChildOnly(Node * root){
    // returns 1 iff node is right child, 0 otherwise
    return (root->Left == NULL && root->Right != NULL);
}

int leftChildOnly(Node * root){
    // returns 1 iff node is left child, 0 otherwise
    return (root->Left != NULL && root->Right == NULL);
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
    char name[24];

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
            //get the total before the specificed target
            int tot = 0;

            tot = calc_below(name);

            printf("%d \n", tot);
        }

    }

    return 0;
}
