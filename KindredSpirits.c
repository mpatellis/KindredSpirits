// Michael Patellis
// mi328379

#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"

// Struct for nodes of a linked list
// Used to capture the traversal data
typedef struct linkedNode
{
    int data;

    struct linkedNode *next;
}linkedNode;

// Linked list struct
// Head and tail pointers make it faster
// to insert and compare
typedef struct linkedList
{
    linkedNode *head;
    linkedNode *tail;
}linkedList;

// Creates a linked list
// Sets the head and tail pointer to NULL
linkedList *createList(void)
{
    return calloc(1, sizeof(linkedList));
}

// Creates nodes in the linked list
// Parameter takes in the data and sets
// the next pointer equal to NULL
linkedNode *createLinkedNode(int data)
{
    linkedNode *n = malloc(sizeof(linkedNode));

    n->data = data;
    n->next = NULL;

    return n;
}

// Inserts data at the of list
// Also updates the tail pointer and the previous's
// node's next pointer
void tailInsert(linkedList *list, int data)
{
    if(list == NULL)
        return;

    else if(list->tail == NULL)
    {
        list->head = list->tail = createLinkedNode(data);
    }

    else
    {
        list->tail->next = createLinkedNode(data);
        list->tail = list->tail->next;
    }

}

// Destroys the nodes of a linked list
linkedNode *destroyNodes(linkedNode *head)
{
    if(head == NULL)
        return NULL;

    destroyNodes(head->next);
    free(head);

    return NULL;
}

// Destroys the linked list
linkedList *destroyList(linkedList *list)
{
    if(list == NULL)
        return NULL;

    destroyNodes(list->head);
    free(list);

    return NULL;
}

// Creates a tree node
node *createNode(int data)
{
	node *n = malloc(sizeof(node));

	n->data = data;
	n->left = n->right = NULL;

	return n;
}

// Preorder traversal
// Inserts the values into a list for comparison
void preOrder(node *root, linkedList *list)
{
    // Ensure the parameter's are not NULL
    if(root == NULL || list == NULL)
        return;

    // Preorder outputs value first then continues
    tailInsert(list, root->data);
    preOrder(root->left, list);
    preOrder(root->right, list);
}


// Postorder traversal
// Inserts the values into a list for comparison
void postOrder(node *root, linkedList *list)
{
    // Ensure the parameter's are not NULL
    if(root == NULL || list == NULL)
        return;

    // Postorder reaches the end of the tree then
    // outputs the values
    postOrder(root->left, list);
    postOrder(root->right, list);
    tailInsert(list, root->data);
}

// Compares two linked lists to determine if they hold
// the same values in the same order
// Returns 1 if they are the same, otherwise it returns 0
int compare(linkedNode *aHead, linkedNode *bHead)
{
    // Ensure that the parameters are not null
    // If one is NULL but not the other the lists do not
    // hold the same number of values so they are different
    if(aHead == NULL && bHead == NULL)
        return 1;
    else if((aHead == NULL && bHead != NULL) || (aHead != NULL && bHead == NULL))
        return 0;

    // If the data is the same continue the recursive calls until they are both NULL
    if(aHead->data == bHead->data)
        compare(aHead->next, bHead->next);
    else
        return 0;
}

// Checks two trees to see if they are reflections
int isReflection(node *a, node *b)
{
    int check;

    // If both a and b are NULL then they are reflections of each other, at least
    // at that node
    // If a or b is NULL while the other is not then they are not reflections of
    // each other
    if(a == NULL && b == NULL)
        return 1;
    if((a == NULL && b != NULL) || (a != NULL && b == NULL))
        return 0;

    // Check is a variable that tracks whether the recursive calls are returning that
    // the tree is a reflection. Otherwise, it breaks out the function and returns 0
    check = 1;

    if(a->data == b->data)
    {
        // As long as the data is the same, the program will work its way down the tree till it
        // reaches the base case of a and b equaling NULL. The base case returns 1 which makes
        // check 1
        // If the pointers a->left and b->right are mismatched in terms of being non-NULL or NULL
        // then tree is not a reflection
        if(a->left != NULL  && b->right != NULL)
            check = isReflection(a->left, b->right);
        else if(a->left == NULL && b->right == NULL)
            return 1;
        else
            return 0;

        // If check is zero then traversing down the other side of the tree is a waste of time
        // so it exits with return 0.
        if(!check)
            return 0;

        // Same as above but switched directions since it is traversing down a different side of
        // the tree
        if(a->right != NULL && b->left != NULL)
            check = isReflection(a->right, b->left);
        else if(a->right == NULL && b->left == NULL)
            return 1;
        else
            return 0;

        if(!check)
            return 0;
    }

    // If the data is not the same then the tree is not a reflection
    if(a->data != b->data)
        return 0;
}

// Constructs a tree that is a reflection of the parameter's tree
node *makeReflection(node *root)
{
    // If the root is NULL then return NULL
    if(root==NULL)
        return NULL;

    // Initial declaration for the node
    node *n;

    // Creating the node and assigning the value
    n=createNode(root->data);

    // Recursively iterate through root but when root goes one
    // direction n goes the other to create the reflection
    n->left=makeReflection(root->right);
    n->right=makeReflection(root->left);

    return n;
}

// Checks if two trees are kindred spirits
int kindredSpirits(node *a, node *b)
{
    // result is whether the two trees are kindred spirits or not
    // The two linked lists are to check the traversals to see if they are the same
    int result = 0;
    linkedList *aList = createList();
    linkedList *bList = createList();

    // Traversal calls
    preOrder(a, aList);
    postOrder(b, bList);

    // Updating result
    result = compare(aList->head, bList->head);

    // Free memory associated with the lists
    aList = destroyList(aList);
    bList = destroyList(bList);

    // If result is 1 then a and b are kindred spirits and returns 1
    if(result)
        return result;

    // If the initial check did not return 1 then a and b need to be switched
    // in case they are kindred spirits in the opposite direction
    // The same as above just with a going through a postorder and b a preorder
    aList = createList();
    bList = createList();

    preOrder(b, bList);
    postOrder(a, aList);

    result = compare(aList->head, bList->head);

    destroyList(aList);
    destroyList(bList);

    if(result)
        return result;
    else
        return 0;

}

double difficultyRating(void)
{
    return 2.5;
}

double hoursSpent(void)
{
    return 5;
}
