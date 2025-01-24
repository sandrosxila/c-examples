#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 100 // supports 2^100 elements

typedef enum {
    RED,
    BLACK
} Color;

typedef enum {
    LEFT,
    RIGHT
} Direction;

typedef struct Node {
    int data, color;
    struct Node *child[2];
} Node;

Node *root = NULL;

// Create a red-black tree
Node *create_node(int data)
{
    Node *newnode;
    newnode = (Node *)malloc(sizeof(Node));
    newnode->data = data;
    newnode->color = RED;
    newnode->child[LEFT] = newnode->child[RIGHT] = NULL;
    return newnode;
}

// Insert an node
void insert(int data)
{
    Node *stack[MAX_STACK], *newnode, *xPtr, *yPtr;
    int dir[MAX_STACK], ht = 0, index;
    
    if (!root)
    {
        root = create_node(data);
        return;
    }

    stack[ht] = root;
    dir[ht++] = 0;
    for (Node *ptr = root; ptr != NULL; ptr = ptr->child[index])
    {
        if (ptr->data == data) {
            fprintf(stderr, "Duplicates Not Allowed!!\n");
            exit(EXIT_FAILURE);
        }
        index = data > ptr->data ? RIGHT : LEFT;
        stack[ht] = ptr;
        dir[ht++] = index;
    }
    stack[ht - 1]->child[index] = newnode = create_node(data);
    while ((ht >= 3) && (stack[ht - 1]->color == RED))
    {
        if (dir[ht - 2] == 0)
        {
            yPtr = stack[ht - 2]->child[RIGHT];
            if (yPtr != NULL && yPtr->color == RED)
            {
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = yPtr->color = BLACK;
                ht = ht - 2;
            }
            else
            {
                if (dir[ht - 1] == 0)
                {
                    yPtr = stack[ht - 1];
                }
                else
                {
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->child[RIGHT];
                    xPtr->child[RIGHT] = yPtr->child[LEFT];
                    yPtr->child[LEFT] = xPtr;
                    stack[ht - 2]->child[LEFT] = yPtr;
                }
                xPtr = stack[ht - 2];
                xPtr->color = RED;
                yPtr->color = BLACK;
                xPtr->child[LEFT] = yPtr->child[RIGHT];
                yPtr->child[RIGHT] = xPtr;
                if (xPtr == root)
                {
                    root = yPtr;
                }
                else
                {
                    stack[ht - 3]->child[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }
        else
        {
            yPtr = stack[ht - 2]->child[LEFT];
            if ((yPtr != NULL) && (yPtr->color == RED))
            {
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = yPtr->color = BLACK;
                ht = ht - 2;
            }
            else
            {
                if (dir[ht - 1] == 1)
                {
                    yPtr = stack[ht - 1];
                }
                else
                {
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->child[LEFT];
                    xPtr->child[LEFT] = yPtr->child[RIGHT];
                    yPtr->child[RIGHT] = xPtr;
                    stack[ht - 2]->child[RIGHT] = yPtr;
                }
                xPtr = stack[ht - 2];
                yPtr->color = BLACK;
                xPtr->color = RED;
                xPtr->child[RIGHT] = yPtr->child[LEFT];
                yPtr->child[LEFT] = xPtr;
                if (xPtr == root)
                {
                    root = yPtr;
                }
                else
                {
                    stack[ht - 3]->child[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }
    }
    root->color = BLACK;
}

// Delete a node
void erase(int data)
{
    Node *stack[MAX_STACK], *ptr, *xPtr, *yPtr;
    Node *pPtr, *qPtr, *rPtr;
    int dir[MAX_STACK], ht = 0, diff, i;
    Color color;

    if (!root)
    {
        printf("Tree not available\n");
        return;
    }

    ptr = root;
    while (ptr != NULL)
    {
        if ((data - ptr->data) == 0)
            break;
        diff = (data - ptr->data) > 0 ? 1 : 0;
        stack[ht] = ptr;
        dir[ht++] = diff;
        ptr = ptr->child[diff];
    }

    if (ptr->child[RIGHT] == NULL)
    {
        if ((ptr == root) && (ptr->child[LEFT] == NULL))
        {
            free(ptr);
            root = NULL;
        }
        else if (ptr == root)
        {
            root = ptr->child[LEFT];
            free(ptr);
        }
        else
        {
            stack[ht - 1]->child[dir[ht - 1]] = ptr->child[LEFT];
        }
    }
    else
    {
        xPtr = ptr->child[RIGHT];
        if (xPtr->child[LEFT] == NULL)
        {
            xPtr->child[LEFT] = ptr->child[LEFT];
            color = xPtr->color;
            xPtr->color = ptr->color;
            ptr->color = color;

            if (ptr == root)
            {
                root = xPtr;
            }
            else
            {
                stack[ht - 1]->child[dir[ht - 1]] = xPtr;
            }

            dir[ht] = 1;
            stack[ht++] = xPtr;
        }
        else
        {
            i = ht++;
            while (1)
            {
                dir[ht] = 0;
                stack[ht++] = xPtr;
                yPtr = xPtr->child[LEFT];
                if (!yPtr->child[LEFT])
                    break;
                xPtr = yPtr;
            }

            dir[i] = 1;
            stack[i] = yPtr;
            if (i > 0)
                stack[i - 1]->child[dir[i - 1]] = yPtr;

            yPtr->child[LEFT] = ptr->child[LEFT];

            xPtr->child[LEFT] = yPtr->child[RIGHT];
            yPtr->child[RIGHT] = ptr->child[RIGHT];

            if (ptr == root)
            {
                root = yPtr;
            }

            color = yPtr->color;
            yPtr->color = ptr->color;
            ptr->color = color;
        }
    }

    if (ht < 1)
        return;

    if (ptr->color == BLACK)
    {
        while (1)
        {
            pPtr = stack[ht - 1]->child[dir[ht - 1]];
            if (pPtr && pPtr->color == RED)
            {
                pPtr->color = BLACK;
                break;
            }

            if (ht < 2)
                break;

            if (dir[ht - 2] == 0)
            {
                rPtr = stack[ht - 1]->child[RIGHT];

                if (!rPtr)
                    break;

                if (rPtr->color == RED)
                {
                    stack[ht - 1]->color = RED;
                    rPtr->color = BLACK;
                    stack[ht - 1]->child[RIGHT] = rPtr->child[LEFT];
                    rPtr->child[LEFT] = stack[ht - 1];

                    if (stack[ht - 1] == root)
                    {
                        root = rPtr;
                    }
                    else
                    {
                        stack[ht - 2]->child[dir[ht - 2]] = rPtr;
                    }
                    dir[ht] = 0;
                    stack[ht] = stack[ht - 1];
                    stack[ht - 1] = rPtr;
                    ht++;

                    rPtr = stack[ht - 1]->child[RIGHT];
                }

                if ((!rPtr->child[LEFT] || rPtr->child[LEFT]->color == BLACK) &&
                    (!rPtr->child[RIGHT] || rPtr->child[RIGHT]->color == BLACK))
                {
                    rPtr->color = RED;
                }
                else
                {
                    if (!rPtr->child[RIGHT] || rPtr->child[RIGHT]->color == BLACK)
                    {
                        qPtr = rPtr->child[LEFT];
                        rPtr->color = RED;
                        qPtr->color = BLACK;
                        rPtr->child[LEFT] = qPtr->child[RIGHT];
                        qPtr->child[RIGHT] = rPtr;
                        rPtr = stack[ht - 1]->child[RIGHT] = qPtr;
                    }
                    rPtr->color = stack[ht - 1]->color;
                    stack[ht - 1]->color = BLACK;
                    rPtr->child[RIGHT]->color = BLACK;
                    stack[ht - 1]->child[RIGHT] = rPtr->child[LEFT];
                    rPtr->child[LEFT] = stack[ht - 1];
                    if (stack[ht - 1] == root)
                    {
                        root = rPtr;
                    }
                    else
                    {
                        stack[ht - 2]->child[dir[ht - 2]] = rPtr;
                    }
                    break;
                }
            }
            else
            {
                rPtr = stack[ht - 1]->child[LEFT];
                if (!rPtr)
                    break;

                if (rPtr->color == RED)
                {
                    stack[ht - 1]->color = RED;
                    rPtr->color = BLACK;
                    stack[ht - 1]->child[LEFT] = rPtr->child[RIGHT];
                    rPtr->child[RIGHT] = stack[ht - 1];

                    if (stack[ht - 1] == root)
                    {
                        root = rPtr;
                    }
                    else
                    {
                        stack[ht - 2]->child[dir[ht - 2]] = rPtr;
                    }
                    dir[ht] = 1;
                    stack[ht] = stack[ht - 1];
                    stack[ht - 1] = rPtr;
                    ht++;

                    rPtr = stack[ht - 1]->child[LEFT];
                }
                if ((!rPtr->child[LEFT] || rPtr->child[LEFT]->color == BLACK) &&
                    (!rPtr->child[RIGHT] || rPtr->child[RIGHT]->color == BLACK))
                {
                    rPtr->color = RED;
                }
                else
                {
                    if (!rPtr->child[LEFT] || rPtr->child[LEFT]->color == BLACK)
                    {
                        qPtr = rPtr->child[RIGHT];
                        rPtr->color = RED;
                        qPtr->color = BLACK;
                        rPtr->child[RIGHT] = qPtr->child[LEFT];
                        qPtr->child[LEFT] = rPtr;
                        rPtr = stack[ht - 1]->child[LEFT] = qPtr;
                    }
                    rPtr->color = stack[ht - 1]->color;
                    stack[ht - 1]->color = BLACK;
                    rPtr->child[LEFT]->color = BLACK;
                    stack[ht - 1]->child[LEFT] = rPtr->child[RIGHT];
                    rPtr->child[RIGHT] = stack[ht - 1];
                    if (stack[ht - 1] == root)
                    {
                        root = rPtr;
                    }
                    else
                    {
                        stack[ht - 2]->child[dir[ht - 2]] = rPtr;
                    }
                    break;
                }
            }
            ht--;
        }
    }
}