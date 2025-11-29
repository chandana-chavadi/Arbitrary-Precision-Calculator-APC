/*******************************************************************************************************************************************************************
 * Function: SUBTRACTION
 * ---------------------
 *  Performs subtraction of two large numbers represented as doubly linked lists.
 *  Each node contains a single digit. The lists store digits from most significant
 *  (head) to least significant (tail).
 *
 *  Example:
 *     List1: 9 <-> 0 <-> 7   (represents 907)
 *     List2: 2 <-> 8 <-> 9   (represents 289)
 *     Result: 6 <-> 1 <-> 8   (represents 618)
 *
 *  Parameters:
 *     head1, tail1 → pointers to first and last node of first number
 *     head2, tail2 → pointers to first and last node of second number
 *     headR        → pointer to head of result list (stores result)
 *
 *  Returns:
 *     SUCCESS (0) if subtraction succeeds
 *     FAILURE (-1) if error (like empty list or borrow issue)
*******************************************************************************************************************************************************************/

#include <stdio.h>      
#include <stdlib.h>
#include "apc.h"

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
    // Validate input lists
	if(*head1 == NULL || *head2 == NULL)
	{
		printf("ERROR : One or Both input Lists are Empty! \n");
		return FAILURE;
	}
	 
    // Compare both numbers to determine which is larger
	int compare = compare_numbers(*head1 , *head2);

    /*
     * If head1 < head2 (LESS), swap both lists.
     * This ensures subtraction is always done as (larger - smaller).
     */
	if(compare == LESS)
	{
		Dlist *temp_head;
		Dlist *temp_tail;

        // Swap head pointers
		temp_head = *head1;
		*head1 = *head2;
		*head2 = temp_head;

        // Swap tail pointers
		temp_tail = *tail1;
		*tail1 = *tail2;
		*tail2 = temp_tail;
	}

    // Start subtraction from the least significant digit (tail)
	Dlist *temp1 = *tail1;
	Dlist *temp2 = *tail2;
	Dlist *tailR = NULL;   // Keeps track of the last node of result

	int difference = 0;
	
    // Traverse both lists from tail to head
	while(temp1 != NULL || temp2 != NULL)
	{
        // If one list ends earlier, treat its digit as 0
		int digit1 = (temp1) ? temp1->data : 0;
		int digit2 = (temp2) ? temp2->data : 0;

        // If borrowing is needed (digit1 < digit2)
		if(digit1 < digit2)
		{
            // Check if there is a previous node to borrow from
			if(temp1->prev == NULL)
			{
				printf("ERROR: Cannot borrow (no previous digit)\n");
                return FAILURE;
			}

            // Borrow logic: add 10 to current digit, and reduce previous by 1
			digit1 = 10 + digit1;
			temp1->prev->data = temp1->prev->data - 1;
		}

        // Perform subtraction for the current position
		difference = digit1 - digit2;

        // Insert result digit at the beginning of result list
		if(insert_at_begin(headR, &tailR, difference) == FAILURE)
		{
			printf("ERROR : Failed to insert the node in the result list. \n");
			return FAILURE;
		}

        // Move to previous digits in both lists
		if(temp1)
		{
			temp1 = temp1->prev;
		}

		if(temp2)
		{
			temp2 = temp2->prev;
		}

	}

    // Remove leading zeros from the result (e.g., 000123 → 123)
	while (*headR && (*headR)->data == 0 && (*headR)->next)
    {
        Dlist *temp = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(temp);
    }

    // Return success after subtraction
	return SUCCESS;
}

