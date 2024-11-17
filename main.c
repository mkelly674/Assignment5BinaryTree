/*
            COP 3502C Assignment 5
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
Node * insertion(Node * root, Node * temp);
Node * add(Node * root, Node * temp);
Node * deduct(Node * root, int deduct, char * name);
Node * delete(Node * root, Node * del, char * name);

//prototypes for void functions
void height_balance(Node * root);

//prototypes for return functions
double average(Node * root);
int calc_below(Node * root,char * name);
int isLeaf(Node * root);
int rightChildOnly(Node * root);
int leftChildOnly(Node * root);
int getHeight(Node * root);
int sum(Node * root);
int count(Node * root);

Node *search(Node * root, char * name){

    // check if nodes in tree
    if(root != NULL){
        //found the Node
        if(strcmp(root->name, name) == 0)
            return root;
            
        //traverse left
        if(strcmp(root->name, name) > 0)
            return search(root->Left, name);
            
        //traverse Right    
        else
            return search(root->Right, name);
    }
    else
        return root;
}

Node * createNode(int fine, char * name){
    Node * temp;
    temp = (Node *) malloc(sizeof(Node));
    temp->fine = fine;
    temp->name = strdup(name);
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

Node * insertion(Node * root, Node * temp){
    //create the tree or input node
    if(root == NULL){
        root = temp;
        return root;
    }
    
    
        //traverse to the left to input the node
        if (strcmp(temp->name, root->name) < 0) {
            root->Left = insertion(root->Left, temp);
        } 
        
        //traverse right to input the node
        if (strcmp(temp->name, root->name) > 0) {
            root->Right = insertion(root->Right, temp);
        } 
    
    
    return root;

}

Node * add(Node * root, Node * temp){
    //if no tree, create tree
    if(root == NULL){
        root = insertion(root, temp);
        int hei = getHeight(root);
        printf("%s %d %d \n", temp->name, temp->fine, hei);
        return root;
    }
    
    //adds the person when they are not in the tree
    if(search(root, temp->name) == NULL){
        root = insertion(root, temp);
        int hei = getHeight(root);
        printf("%s %d %d \n", temp->name, temp->fine, hei);
        return root;
    }
    
    //adds to the fine when the person is in the tree
    else{
        Node * res = search(root, temp->name);
        res->fine = res->fine + temp->fine;
        return root;
    }
    
    return root;

}

Node * deduct(Node * root, int deduct, char * name){\
    Node * res = search(root, name);
    //if there is any any node
    if(res == NULL)
        return root;

    
    res->fine = res->fine - deduct;
    
    //if the person still has a fine
    if(res->fine > 0){
        int hei = getHeight(root);
        printf("%s, %d, %d", res->name, res->fine, hei);
    }
        
    
    //if the payment went below zero
    if(res->fine <= 0){
        printf("%s removed \n", name);
        root = delete(root, res, name);
    }
    return root;
}

Node * delete(Node * root, Node * del, char * name){
    Node *delnode, *new_del_node, *save_node;
    Node *par;
    char * saveName = (char *) malloc (sizeof(char)*25);
    delnode = search(root, name); // Get a pointer to the node to delete.
    par = parent(root, delnode); // Get the parent of this node.
    // Take care of the case where the node to delete is a leaf node.
    if (isLeaf(delnode)) {// case 1
        // Deleting the only node in the tree.
        if (par == NULL) {
            free(delnode->name);
            free(delnode); // free the memory for the node.
            return NULL;
        }
        // Deletes the node if it's a left child.
        if (strcmp(name, par->name) < 0) {
            free(par->Left->name);
            free(par->Left); // Free the memory for the node.
            par->Left = NULL;
        }
        // Deletes the node if it's a right child.
        else {
            free(par->Right->name);
            free(par->Right); // Free the memory for the node.
            par->Right = NULL;
        }
        return root; // Return the root of the new tree.
    }
    // Take care of the case where the node to be deleted only has a left
    // child.
    if (leftChildOnly(delnode)) {
        // Deleting the root node of the tree.
        if (par == NULL) {
            save_node = delnode->Left;
            //need to free name and node
            free(delnode->name);
            free(delnode); // Free the node to delete.
            return save_node; // Return the new root node of the resulting tree.
        }
        // Deletes the node if it's a left child.
        if (strcmp(name, par->name) < 0) {
            save_node = par->Left; // Save the node to delete.
            par->Left = par->Left->Left; // Readjust the parent pointer.
            //need to free name and node
            free(save_node->name);
            free(save_node); // Free the memory for the deleted node.
        }
        // Deletes the node if it's a right child.
        else {
            save_node = par->Right; // Save the node to delete.
            par->Right = par->Right->Left; // Readjust the parent pointer.
            //need to free name and node
            free(save_node->name);
            free(save_node); // Free the memory for the deleted node.
        }
        return root; // Return the root of the tree after the deletion.
    }
    // Takes care of the case where the deleted node only has a right child.
    if (rightChildOnly(delnode)) {
    // Node to delete is the root node.
    if (par == NULL) {
        save_node = delnode->Right;
        //need to free name and node
        free(delnode->name);
        free(delnode);
        return save_node;
    }
    // Delete's the node if it is a left child.
    if (strcmp(name, par->name) < 0) {
        save_node = par->Left;
        par->Left = par->Left->Right;
        //need to free name and node
        free(save_node->name);
        free(save_node);
    }
    // Delete's the node if it is a right child.
    else {
        save_node = par->Right;
        par->Right = par->Right->Right;
        free(save_node->name);
        free(save_node);
    }
    return root;
    }
    //if your code reaches hear it means delnode has two children
    // Find the new physical node to delete.
    new_del_node = minVal(delnode->Right);
    free(delnode->name);
    delnode->name = strdup(new_del_node->name);
    delete(root, new_del_node, name); // Now, delete the proper value.
    return root;
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
        printf(" balanced \n");
    

    else
        printf(" not balanced \n");
}

double average(Node * root){
    //get the sum and number of nodes in tree
    int summed= 0;
    int counted = 0;
    double res = 0;
    
    //get the sum
    summed = summed + sum(root);
    
    //get the count
    counted = count(root);

    //divid the sum with count to get average
    res = (double)summed/(double)counted;

    return res;
}

int sum(Node * root){
    if(root == NULL){
        return 0;
    }
    int res = root->fine;
    

    //traverse to the right
    if(root != NULL){
        res = res + sum(root->Right);
        res = res + sum(root->Left);
        return res;
    }

    return res;
}

//taken from BST code to count the numnodes
int count(Node * root){
    //return when hitting null
    if (root == NULL) 
        return 0;
    //count the number of nodes
    return 1 + count(root->Left) + count(root->Right);
}

int getHeight(Node * root){
   

    // empty list
    if(root == NULL)
        return -1;
        
    int rHei = getHeight(root->Right);
    int lHei = getHeight(root->Left);
    
    //get the max hiegth on either side
    return 1 + (lHei > rHei ? lHei : rHei);
}

int calc_below(Node  * root, char * name){
    if(root == NULL)
        return 0;
    
    int res = 0;
    
    //getting the first node smaller than the name
    if(strcmp(root->name, name) < 0)
       res = root->fine;
    
    if(strcmp(root->name, name) > 0)
        res = res + calc_below(root->Left, name);
    
    else{
        res = res + calc_below(root->Left, name);
        res = res + calc_below(root->Right, name);
    }
    

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
    char command[20];

    //get the Node
    Node * root = NULL;
    Node * temp;

    //get the fine
    int fin = 0;

    //get the deduction
    int deduc = 0;

    //get the name
    char name[24];

    for(int i = 0; i < numcom; i++){

        scanf("%s", command);
        if(strcmp(command, "add") == 0){
            
            //get the name to be added
            scanf("%s", name);

            //get the fine to be added
            scanf("%d", &fin);

            temp = createNode(fin, name);

            root = add(root, temp);
            
            
        }

        if(strcmp(command, "deduct") == 0){
            //get the name
            scanf("%s", name);

            //get the amount deducted
            scanf("%d", &deduc);

            deduct(root, deduc, name);
            
        }

        if(strcmp(command, "search") == 0){
            //get the name
            scanf("%s", name);

            Node * temp = search(root, name);
            if(temp == NULL)
                printf("%s not found\n", name);

            else{
                int hei = getHeight(temp);
                printf("%s, %d, %d \n", name, temp->fine, hei);
            }
            
        }

        if(strcmp(command, "average") == 0){
            //get the average
            double ave = 0;

            ave = average(root);

            printf("%.2f \n", ave);
           
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

    printf("%d", numcom);
    
    return 0;
}
