#include<assert.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>
#include "bst.h"
#include<stddef.h>
#include "../adaptive queues/queue.h"

BST bst_new(){
    BST bst = { NULL, 0};
    return bst;
}

uint32_t bst_count(const BST *tree){
    assert( tree != NULL);
    return tree->mass;
}

static TreeNode* _get_new_node(int32_t ele) {
    TreeNode *newnode = (TreeNode*)malloc(sizeof(TreeNode));
    newnode->data = ele;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

BST* bst_add(BST *tree, int32_t element) {
    assert( (tree != NULL));
    TreeNode *current, *parent;

    current = parent = tree->root;

    while ( current != NULL && element != current->data ){
        parent = current;
        if ( element < current->data ){
            current = current->left;
        } else if ( element > current->data ){
            current = current->right;
        }
    }

    if ( current == NULL ){
        TreeNode *newnode = _get_new_node(element);
        if ( parent == NULL ){
            tree->root = newnode;
        }else if ( element < parent->data ){
            parent->left = newnode;
        }else if ( element > parent->data ){
            parent->right = newnode;
        }
        ++tree->mass;
    }
    return tree;
}

uint8_t bst_lookup(const BST *tree, int32_t key){
    assert ( tree != NULL );
    TreeNode *current = tree->root;

    while ( current != NULL && key != current->data ){
        if ( key < current->data ){
            current = current->left;
        }else if ( key > current ->data ){
            current = current->right;
        }
    }
    return (current != NULL);
}

static TreeNode* _findMin_(TreeNode *node){
    if (node->left == NULL){
        return node;
    }else {
        return (_findMin_(node->left));
    }
}

static TreeNode* _delete_(BST *tree, TreeNode *node, int32_t element){
    TreeNode *temp;

    if ( node == NULL ){
        return node;
    }else if (element < node->data){
       node->left = _delete_(tree,node->left,element);
    }else if (element > node->data){
        node->right = _delete_(tree,node->right,element);
    }else if ( node->left && node->right){
        temp = _findMin_(node->right);
        node->data = temp->data;
        node->right = _delete_(tree,node->right,node->data);
    }else{
        temp = node;
        if ( node->right == NULL ){
            node = node->left;
        }else{
            node = node->right;
        }
        free(temp);
        --tree->mass;
    }
    return node;
}

BST* bst_delete(BST *tree, int32_t element){
    assert ( tree != NULL );
    tree->root = _delete_(tree,tree->root,element);

    return tree;
}

static void _inorder_(TreeNode *node){
    if(node){
        _inorder_(node->left);
        printf("%d\t",node->data);
        _inorder_(node->right);
    }
}

void bst_inorder(BST *tree){
    assert(tree != NULL);
    _inorder_(tree->root);
}

static void _preorder_(TreeNode *node){
    if(node){
        printf("%d\t",node->data);
        _preorder_(node->left);
        _preorder_(node->right);
    }
}
void bst_preorder(BST *tree){
    assert(tree != NULL);
    _preorder_(tree->root);
}

static void _postorder_(TreeNode *node){
    if(node){
        _postorder_(node->left);
        _postorder_(node->right);
         printf("%d\t",node->data);
    }
}
void bst_postorder(BST *tree){
    assert(tree != NULL);
    _postorder_(tree->root);
}

void  bst_levelordertraversal(BST *tree){
assert (tree!=NULL);
Queue q1=queue_new(tree->mass);
Queue *q=&q1;
QueueResult res;
TreeNode *node=tree->root;
queue_add(q,node,&res);

while(!queue_empty(q)){
    queue_delete(q,&res);
    node=(TreeNode*)res.data;
    if(node->left){
        queue_add(q,node->left,&res);

    }
    if(node->right){
        queue_add(q,node->right,&res);
    }
    printf("%d\t",node->data);
}

}

static int _height_(TreeNode *node){
    if ( node == NULL ){
        return 0;
    }else{
        int lDepth = _height_(node->left);
        int rDepth = _height_(node->right);

        if ( lDepth > rDepth ){
            return lDepth+1;
        }else{
            return rDepth+1;
        }
    }
}
int maxDepth(BST *tree){
    assert ( tree != NULL );
    return _height_(tree->root);

}

static int _leafcount_(TreeNode *node){
    if(node == NULL){
        return 0;
    }

    if(node->left == NULL && node->right==NULL) {
        return 1;
    }
    else {
        return _leafcount_(node->left)+ _leafcount_(node->right);
    }

}

int getLeafCount(BST *tree){
    assert ( tree != NULL );
    return _leafcount_(tree->root);
}

int minimum(BST *tree){
    assert ( tree != NULL );

    while ( tree->root != NULL && tree->root->left != NULL){
        tree->root = tree->root->left;
    }
    return tree->root->data;
}

int32_t maximum(BST *tree){
    assert ( tree != NULL );
    TreeNode *node = tree->root;

    while (node != NULL && node->right != NULL){
        node = node->right;
    }
    return node->data;
}

static void _descendingorder_(TreeNode *node){
    if(node){
        _descendingorder_(node->right);
        printf("%d\t",node->data);
        _descendingorder_(node->left);

    }
}

void bst_descendingorder(BST *tree){
    assert ( tree != NULL );
    _descendingorder_(tree->root);
}
