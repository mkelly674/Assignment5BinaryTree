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
void delete(Node * root, Node * del, char * name);
void height_balance(Node * root);

//prototypes for return functions
int average(Node * root);
int calc_below(Node * root,char * name);
int isLeaf(Node * root);
int rightChildOnly(Node * root);
int leftChildOnly(Node * root);
int getHeight(Node * root);
int sum(Node * root);
int count(Node * root, int count);

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
    if(root == NULL){
        insertion(root, fine, name);
    }

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
    delete(root, res, name);
}

void delete(Node * root, Node * del, char * name){
    if(root == NULL)
    return;
    Node * saveNode;
    Node * par = parent(root, del);

    //if root is leaf
    if(isLeaf(del) == 1){
        //simple free
        free(del);
        del = NULL;  
    }

    //if root has only left child
    if(leftChildOnly(del) == 1){
        //this is when deleting root with one child
        if(par  == NULL){
          root = del->Left;
          free(del);  
        }

        //if the deletion is to the Right of the parent Node
        if(strcmp(par->name, del->name) < 0){
            saveNode = del->Left;
            free(del);
            del = NULL;
            par->Right = saveNode;
        }

        //if the deletion is to the Left of the parent Node
        if(strcmp(par->name, del->name) > 0){
            saveNode = del->Left;
            free(del);
            del = NULL;
            par->Left = saveNode;
        }
    }

    //if root has only right child
    if(rightChildOnly(root) == 1){
        //this is when deleting root with one child
        if(par  == NULL){
          root = del->Right;
          free(del);  
        }

        //if the deletion is to the Right of the parent Node
        if(strcmp(par->name, del->name) < 0){
            saveNode = del->Right;
            free(del);
            del = NULL;
            par->Right = saveNode;
        }

        //if the deletion is to the Left of the parent Node
        if(strcmp(par->name, del->name) > 0){
            saveNode = del->Right;
            free(del);
            del = NULL;
            par->Left = saveNode;
        }
    }
    
}

void height_balance(Node * root){
    //get the left and right heights of subtree
    int rHei = 0;
    int lHei = 0;

    //get the balance
    int balance = 0;

    //get the heights
    rHei = rHei + getHeight(root->Right);
    lHei = lHei + getHeight(root->Left);

    printf("left height = %d right height = %d", lHei, rHei);

    balance = rHei - lHei;

    if(balance <= 1 && balance >=-1)
        printf("balanced \n");
    

    else
        printf("not balanced \n");
}
int average(Node * root){
    //get the sum and number of nodes in tree
    int summed= 0;
    int counted = 0;
    double res = 0;

    summed = summed + sum(root);

    counted = count(root, counted);

    res = summed/counted;
    return res;
}
int sum(Node * root){
    if(root == NULL){
        return 0;
    }
    int res = root->fine;
    

    //traverse to the right
    while (root != NULL){
        return res + sum(root->Right);
    }
    
    //traverse to the left
    while(root != NULL)
        return res + sum(root->Left);

    return res;
}

int count(Node * root, int counted){
    if(root == NULL)
        return 0;

    if(root->Left != NULL)
        return count(root->Left, counted + 1);

    if(root->Right != NULL)
        return count(root->Right, counted + 1);

    if(root->Left == NULL && root->Right == NULL)
        return 1;
}

int getHeight(Node * root){
    int hei = 0;

    // empty list
    if(root == NULL)
        return hei - 1;

    //get the leaf node
    if(root->Right == NULL && root->Left == NULL)
        return hei;
    
    //right child only
    if(root->Right != NULL && root->Left == NULL){
        hei++;
        return hei + getHeight(root->Right);
    }

    //left child only
    if(root->Left != NULL && root->Right == NULL){
        hei++;
        return hei + getHeight(root->Left);
    }
    
    //when there are two children, get the height on both subtrees
    int rHei = getHeight(root->Right);
    int lHei = getHeight(root->Left);

    //if left subtree is bigger
    if(rHei < lHei)
        return lHei;
    
    //if right subtree is bigger
    if(rHei > lHei)
        return rHei;
    
    return hei;
}

int calc_below(Node  * root, char * name){
    if(root == NULL)
        return 0;
    //get the Node to stop at
    Node * countNode = search(root, name);
    
    int res = root->fine;

    if(countNode == NULL)
        return 0;

    if(strcmp(root->name, countNode->name) < 0)
       return res + calc_below(root->Left, name);

    return res;
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
    char * name = (char *) malloc(sizeof(char)*24);

    for(int i = 0; i < numcom; i++){

        scanf("%s", &command);

        if(strcmp(command, "add") == 0){
            //get the fine to be added
            scanf("%d", &fin);

            //get the name to be added
            scanf("%s", name);

            add(root, fin, name);
        }

        if(strcmp(command, "deduct") == 0){
            //get the amount deducted
            scanf("%d", &deduc);

            //get the name
            scanf("%s", name);

            deduct(root, deduc, name);
        }

        if(strcmp(command, "search") == 0){
            //get the name
            scanf("%s", name);

            Node * temp = search(root, name);
        }

        if(strcmp(command, "average") == 0){
            //get the average
            int ave = 0;

            ave = average(root);

            printf("%d \n", ave);
        }

        if(strcmp(command, "height_balance") == 0){

            height_balance(root);
        }

        if(strcmp(command, "calc_below") == 0){
            //get the total before the specificed target
            int tot = 0;

            scanf("%s", name);

            tot = calc_below(root, name);

            printf("%d \n", tot);
        }

    }

    return 0;
}
