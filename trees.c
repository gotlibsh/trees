/************************************************************************************
This is a collection of various functions and algorithms handling tree data-structure
************************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// defines a macro which returns the maximum of 2 elements
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )

// defines a macro which returns the minimum of 2 elements
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )

// defines a tree node with a data integer
typedef struct _Node
{
    int data;
    
    struct _Node* left;
    struct _Node* right;
} Node;

// defines the boolean type and values
#define bool  short
#define true  1
#define false 0

// returns a new allocated tree node
Node* create_node()
{
    Node* node = (Node*)malloc(sizeof(Node));
    
    if(node == NULL)
        exit(EXIT_FAILURE);
        
    node->left = node->right = NULL;
    node->data = 0;
        
    return node;
}

// returns a new allocated tree node with the specified data
Node* create_node_with_data(int data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    
    if(node == NULL)
        exit(EXIT_FAILURE);
        
    node->left = node->right = NULL;
    node->data = data;
        
    return node;
}

// prints the data of the given tree node or NULL if the node is NULL
void print_node_data(const Node* node)
{
    if(node == NULL)
        printf("NULL ");
    else
        printf("%d ", node->data);
}

// adds a given node to a binary search tree
// returns whether the node was added or not
bool add_node_to_binary_search_tree(Node** proot, Node* new_node, bool duplicate)
{
    if(*proot == NULL)
    {
        *proot = new_node;
        return true;
    }
        
    if(new_node->data > (*proot)->data)
        return add_node_to_binary_search_tree(&((*proot)->right), new_node, duplicate);
    else if(new_node->data < (*proot)->data || duplicate)
        return add_node_to_binary_search_tree(&((*proot)->left), new_node, duplicate);
    else
        return false;
}

void free_tree(Node** proot)
{
    if(*proot == NULL)
        return;
        
    free_tree(&((*proot)->left));
    free_tree(&((*proot)->right));
    
    free(*proot);
    *proot = NULL;
}

// prints a binary tree in 'pre order'
void print_binary_tree_pre_order(const Node* root)
{
    if(root == NULL)
        return;
        
    print_node_data(root);
    print_binary_tree_pre_order(root->left);
    print_binary_tree_pre_order(root->right);
}

// prints a binary tree in 'in order'
void print_binary_tree_in_order(const Node* root)
{
    if(root == NULL)
        return;
        
    print_binary_tree_in_order(root->left);
    print_node_data(root);
    print_binary_tree_in_order(root->right);
}

// prints a binary tree in 'post order'
void print_binary_tree_post_order(const Node* root)
{
    if(root == NULL)
        return;
        
    print_binary_tree_post_order(root->left);
    print_binary_tree_post_order(root->right);
    print_node_data(root);
}

// prints a binary search tree sorted
void print_binary_search_tree_sorted(const Node* root)
{
    print_binary_tree_in_order(root);
}

// prints a binary tree by level
void print_binary_tree_by_level(const Node* root)
{
    
}

// helper function, do NOT call this directly
unsigned int get_binary_tree_depth_helper(const Node* root, int depth)
{
    if(root == NULL)
        return depth;
        
    return max(get_binary_tree_depth_helper(root->left, depth + 1),
               get_binary_tree_depth_helper(root->right, depth + 1));
}

// returns the depth of a binary tree
// if root is NULL -1 is returned, if root is the only node in the tree 0 is returned, etc.
unsigned int get_binary_tree_depth(const Node* root)
{
    return get_binary_tree_depth_helper(root, -1);
}

// helper function, do NOT call this directly
void get_binary_tree_depth_efficient_helper(const Node* root, unsigned int* max_level, int cur_level)
{
    if(root == NULL)
        return;
        
    if(cur_level > *max_level)
        *max_level = cur_level;
        
    get_binary_tree_depth_efficient_helper(root->left, max_level, cur_level+1);
    get_binary_tree_depth_efficient_helper(root->right, max_level, cur_level+1);
}

// returns the depth of a binary tree, this is a more efficient algorithm
// if root is NULL -1 is returned, if root is the only node in the tree 0 is returned, etc.
unsigned int get_binary_tree_depth_efficient(const Node* root)
{
    unsigned int max_level = 0;
    
    if(root == NULL)
        return -1;
    
    get_binary_tree_depth_efficient_helper(root, &max_level, 0);
    
    return max_level;
}

// returns a pointer to the first tree node with the specified data if found, otherwise null
const Node* find_data_in_binary_search_tree(const Node* root, int data)
{
    if(root == NULL)
        return NULL;
        
    if(root->data == data)
        return root;
    else if(root->data > data)
        return find_data_in_binary_search_tree(root->left, data);
    else
        return find_data_in_binary_search_tree(root->right, data);
}

// returns the size of a binary tree
// if root is NULL 0 is returned, if root is the only node in the tree 1 is returned, etc.
int get_binary_tree_size(const Node* root)
{
    if(root == NULL)
        return 0;
        
    return 1
           + get_binary_tree_size(root->left)
           + get_binary_tree_size(root->right);
}

// helper function, do NOT call this directly
void get_binary_tree_in_pre_order_helper(const Node* root, int* arr, int* index)
{
    if(root == NULL)
        return;
        
    arr[(*index)] = root->data;
    (*index)++;
    
    get_binary_tree_in_pre_order_helper(root->left, arr, index);
    get_binary_tree_in_pre_order_helper(root->right, arr, index);
}

// returns a new allocated array containing a binary-tree's data in pre-order
// assigns the array-size to out_arr_size parameter
int* get_binary_tree_in_pre_order(const Node* root, int* out_arr_size)
{
    int* arr;
    int tree_size, index = 0;
    
    tree_size = get_binary_tree_size(root);
    arr = (int*)malloc(tree_size * sizeof(int));
    
    if(arr == NULL)
        exit(EXIT_FAILURE);
        
    get_binary_tree_in_pre_order_helper(root, arr, &index);
    
    if(out_arr_size != NULL)
        *out_arr_size = tree_size;
    
    return arr;
}

// helper function, do NOT call this directly
void get_binary_tree_in_in_order_helper(const Node* root, int* arr, int* index)
{
    if(root == NULL)
        return;
        
    get_binary_tree_in_in_order_helper(root->left, arr, index);
    
    arr[(*index)] = root->data;
    (*index)++;
    
    get_binary_tree_in_in_order_helper(root->right, arr, index);
}

// returns a new allocated array containing a binary-tree's data in in-order
// assigns the array-size to out_arr_size parameter
int* get_binary_tree_in_in_order(const Node* root, int* out_arr_size)
{
    int* arr;
    int tree_size, index = 0;
    
    tree_size = get_binary_tree_size(root);
    arr = (int*)malloc(tree_size * sizeof(int));
    
    if(arr == NULL)
        exit(EXIT_FAILURE);
        
    get_binary_tree_in_in_order_helper(root, arr, &index);
    
    if(out_arr_size != NULL)
        *out_arr_size = tree_size;
    
    return arr;
}

// helper function, do NOT call this directly
void get_binary_tree_in_post_order_helper(const Node* root, int* arr, int* index)
{
    if(root == NULL)
        return;
        
    get_binary_tree_in_post_order_helper(root->left, arr, index);
    get_binary_tree_in_post_order_helper(root->right, arr, index);
    
    arr[(*index)] = root->data;
    (*index)++;
}

// returns a new allocated array containing a binary-tree's data in post-order
// assigns the array-size to out_arr_size parameter
int* get_binary_tree_in_post_order(const Node* root, int* out_arr_size)
{
    int* arr;
    int tree_size, index = 0;
    
    tree_size = get_binary_tree_size(root);
    arr = (int*)malloc(tree_size * sizeof(int));
    
    if(arr == NULL)
        exit(EXIT_FAILURE);
        
    get_binary_tree_in_post_order_helper(root, arr, &index);
        
    if(out_arr_size != NULL)
        *out_arr_size = tree_size;
    
    return arr;
}

// prints an array of integers
void print_int_array(int* arr, int size)
{
    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);
}

// helper function, do NOT call this directly
int find_root_index_in_in_order(int* in_order, int in_order_size, int root)
{
    for(int i = 0; i < in_order_size; i++)
        if(in_order[i] == root)
            return i;
            
    return -1;
}

// builds a binary tree from a given pre-order array and in-order array
// NOTE: if the tree contains duplicated data, there's no promise the rebuilt tree will be exactly like the original
void build_binary_tree_from_preorder_and_inorder(Node** proot, int* pre_order, int* in_order, int size)
{
    if(size == 0)
    {
        *proot = NULL;
        return;
    }
    
    int data, root_index_in_order;
    int* in_order_left, *in_order_right, *pre_order_left, *pre_order_right;
    int left_size, right_size;
    
    data = pre_order[0];
    *proot = create_node_with_data(data);
    
    root_index_in_order = find_root_index_in_in_order(in_order, size, (*proot)->data);
    
    // divide the in-order array into 2 sub-arrays representing 2 sub-trees of current root
    left_size = root_index_in_order;
    right_size = size - (left_size + 1);
    
    pre_order_left = pre_order + 1;                 // first element was used for current node
    pre_order_right = pre_order_left + left_size;   // right sub-array starts right after left sub-array
    
    in_order_left = in_order;                       // left sub-array is in the start of in-order
    in_order_right = in_order_left + left_size + 1; // right sub-array starts right after the current node data's index in in-order
    
    // recursive call for the 2 sub trees of the current node
    build_binary_tree_from_preorder_and_inorder(&((*proot)->left), pre_order_left, in_order_left, left_size);
    build_binary_tree_from_preorder_and_inorder(&((*proot)->right), pre_order_right, in_order_right, right_size);
}

// main function
int main()
{
    Node* root = NULL, *new_tree = NULL, *temp;
    int* pre_order_array, *in_order_array, *post_order_array;
    int arr_size, max_data = 10;
    bool no_duplicates = false, with_duplicates = true;
    
    srand(time(NULL));
    
    for(int i = 0; i < max_data; i++)
    {
        int data = rand() % max_data;
        temp = create_node_with_data(data);
        
        if(!add_node_to_binary_search_tree(&root, temp, no_duplicates))
            free(temp);
    }
    printf("tree built!\n");
    
    printf("post-order: \n");
    pre_order_array = get_binary_tree_in_pre_order(root, &arr_size);
    in_order_array = get_binary_tree_in_in_order(root, NULL);
    post_order_array = get_binary_tree_in_post_order(root, NULL);
    
    printf("\npre:  ");
    print_int_array(pre_order_array, arr_size);
    printf("\nin:   ");
    print_int_array(in_order_array, arr_size);
    printf("\npost: ");
    print_int_array(post_order_array, arr_size); 
    //pre_order_array = get_binary_tree_in_pre_order(root, &arr_size);
    //printf("pre-array: ");
    //print_int_array(pre_order_array, arr_size);
    //printf("\nin-array:  ");
    //in_order_array = get_binary_tree_in_in_order(root, &arr_size);
    //print_int_array(in_order_array, arr_size);
    
    //build_binary_tree_from_preorder_and_inorder(&new_tree, pre_order_array, in_order_array, arr_size);
    //printf("rebuilt tree!\n");
    //printf("\nnew, pre: ");
    //print_binary_tree_pre_order(new_tree);
    //printf("\nnew, in:  ");
    //print_binary_tree_in_order(new_tree);

    printf("\nsize of tree: %d\n", get_binary_tree_size(root));

    printf("tree depth: %d\n", get_binary_tree_depth_efficient(root));
    //printf("new-tree depth: %d\n", get_binary_tree_depth_efficient(new_tree));

    //if(memcmp(pre_order_array, get_binary_tree_in_pre_order(new_tree, NULL), arr_size) == 0 &&
    //   memcmp(in_order_array, get_binary_tree_in_in_order(new_tree, NULL), arr_size) == 0)
    //   printf("\nalogrithm works!\n");
    //else
    //    printf("\nalogrithm doesn't work!\n");

    // clean-up
    free_tree(&root);
    //free_tree(&new_tree);
    //free(pre_order_array);
    //free(in_order_array);

    return 0;
}
