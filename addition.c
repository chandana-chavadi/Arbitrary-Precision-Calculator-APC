/*******************************************************************************************************************************************************************
 * Function: ADDITION
 * -------------------
 *  Performs addition of two numbers represented as doubly linked lists.
 *  Each node in the linked list stores a single digit.
 *  
 *  Example:
 *     List1: 9 <-> 9 <-> 9   (represents 999)
 *     List2: 1 <-> 0 <-> 1   (represents 101)
 *     Result: 1 <-> 1 <-> 0 <-> 0   (represents 1100)
 *
 *  Parameters:
 *     head1, tail1 → Pointers to the first and last node of the first number
 *     head2, tail2 → Pointers to the first and last node of the second number
 *     headR        → Pointer to the head of the result list (will store sum)
 *
 *  Returns:
 *     SUCCESS (0) if addition succeeds
 *     FAILURE (-1) if any error occurs (like empty input list or memory failure)
 *
*******************************************************************************************************************************************************************/

#include <stdio.h>      
#include <stdlib.h>
#include "apc.h"



int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
	// Check if either of the input lists is empty
	if(*head1 == NULL || *head2 == NULL)
	{
		printf("ERROR : One or Both input Lists are Empty! \n");
		return FAILURE;
	}

	// Start traversal from the last nodes (least significant digits)
	Dlist *temp1 = *tail1;
	Dlist *temp2 = *tail2;
	Dlist *tailR = NULL;   // To keep track of the result list’s tail
	 
	int sum = 0 , carry = 0;  // Initialize sum and carry

	// Continue until both lists and carry are processed
	while(temp1 != NULL || temp2 != NULL || carry != 0)
	{
		// Extract digits from current nodes; if NULL, use 0
		int digit1 = (temp1) ? temp1->data : 0;
		int digit2 = (temp2) ? temp2->data : 0;

		// Perform addition of digits plus carry
		sum = digit1 + digit2 + carry;

		// Compute new carry and the single-digit sum
		carry = sum / 10;    // Carry for next higher place
		sum = sum % 10;      // Store only single digit (0–9)

		// Insert result digit at beginning (MSD towards head)
		if(insert_at_begin(headR, &tailR, sum) == FAILURE)
		{
			printf("ERROR : Failed to insert the node in the result list. \n");
			return FAILURE;
		}

		// Move to previous node in both lists (next higher digit)
		if(temp1)
		{
			temp1 = temp1->prev;
		}

		if(temp2)
		{
			temp2 = temp2->prev;
		}
	}

	// Successfully completed addition
	return SUCCESS;
}

