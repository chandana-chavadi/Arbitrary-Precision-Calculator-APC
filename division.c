/*******************************************************************************************************************************************************************
* Title            : Division
* Description      : This function performs division of two large numbers represented as doubly linked lists (list1 ÷ list2)
*                    and stores the quotient in the resultant list.
*
* Prototype        : int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*
* Input Parameters : 
*     head1  : Pointer to the first node of the dividend (numerator)
*     tail1  : Pointer to the last node of the dividend
*     head2  : Pointer to the first node of the divisor (denominator)
*     tail2  : Pointer to the last node of the divisor
*     headR  : Pointer to the first node of the resultant (quotient) list
*
* Output           : Status (SUCCESS / FAILURE)
*
* Notes:
*     - The numbers are assumed to be non-negative.
*     - Each node in the list represents a single digit.
*     - The function performs simple integer division (no remainder stored).
*******************************************************************************************************************************************************************/
#include <stdio.h>      
#include <stdlib.h>
#include "apc.h"

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
	// Validate input lists
	if(*head1 == NULL || *head2 == NULL)
	{
		printf("ERROR : One or Both input Lists are Empty! \n");
		return FAILURE;
	}

	// Remove meaningless leading zeros like 000123 → 123
	remove_leading_zeros(head1);
	remove_leading_zeros(head2);

	// Compare magnitudes of dividend and divisor
	int compare = compare_numbers(*head1, *head2);

	if(compare == LESS)
	{
		// If dividend < divisor → quotient is 0
		insert_at_end(headR, tail1, 0);
		return SUCCESS;
	}
	else if (compare == EQUAL)
    {
        // If numbers are equal → quotient is 1
        insert_at_end(headR, tail1, 1);
        return SUCCESS;
    }

	// Temporary remainder list (what we keep subtracting divisor from)
	Dlist *rem_head = NULL;
	Dlist *rem_tail = NULL;
	// Quotient list (final answer)
	Dlist *quot_head = NULL;
	Dlist *quot_tail = NULL;
	// Iterate digit by digit from the dividend (left to right)
	Dlist *digit = *head1;

	while(digit)
	{
		// Bring current digit into the remainder buffer
		insert_at_end(&rem_head, &rem_tail, digit->data);
		// Remove leading zeros after adding new digit
		remove_leading_zeros(&rem_head);

		// This will store how many times divisor fits in remainder
		int count = 0;

		// While remainder >= divisor
		while (compare_numbers(rem_head, *head2) != LESS)
		{
			Dlist *new_rem = NULL;
			// Perform remainder = remainder - divisor
			subtraction(&rem_head, &rem_tail, head2, tail2, &new_rem);
			// Free old remainder and update to the new one
			delete_list(&rem_head, &rem_tail);
			rem_head = new_rem;
			rem_tail = rem_head;	// Move rem_tail to the last node of updated remainder

			while(rem_tail && rem_tail->next)
			{
				rem_tail = rem_tail->next;
			}
			count++;	// Increase quotient digit count
		}

		// Append this quotient digit to quotient list
		insert_at_end(&quot_head, &quot_tail, count);
		// Move to next dividend digit (long division style)
		digit = digit->next;
	}
	// Remove extra zeros at the front of the quotient
	remove_leading_zeros(&quot_head);
	// Store final quotient in result pointer
	*headR = quot_head;
	return SUCCESS;
}




