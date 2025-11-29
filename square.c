#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

/******************************************************************************************
 * Function: square
 * ----------------
 *  Computes the square of a large number represented as a doubly linked list.
 *
 *  Example:
 *     Input : 12
 *     Output: 144
 *
 *  Logic:
 *     Just multiply the number by itself using your existing multiplication function.
 *******************************************************************************************/

#include <stdio.h>      
#include <stdlib.h>
#include "apc.h"

int square(Dlist **head1, Dlist **tail1, Dlist **headR)
{
    if(*head1 == NULL)
    {
        printf("ERROR : Input list is Empty! \n");
        return FAILURE;
    }

    Dlist *head2 = NULL, *tail2 = NULL;     // duplicate number for squaring
    Dlist *temp = *head1;

    while(temp)                             // copy list1 into list2
    {
        if(insert_at_end(&head2, &tail2, temp->data) == FAILURE)
        {
            printf("ERROR: Node creation failed.\n");
            return FAILURE;
        }
        temp = temp->next;
    }

    // Perform multiplication: result = list1 × list2
    if(multiplication(head1, tail1, &head2, &tail2, headR) == FAILURE)
    {
        printf("ERROR: Square operation failed.\n");
        return FAILURE;
    }
    return SUCCESS;
}