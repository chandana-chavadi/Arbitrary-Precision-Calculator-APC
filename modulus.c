/*******************************************************************************************************************************************************************
 * Function: modulus
 * -----------------
 *  Performs modulus operation (remainder) of two large numbers represented 
 *  as doubly linked lists.
 *
 *  Each node in the list stores one digit.
 *  Example:  17 % 5 = 2
 *
 *  Parameters:
 *     head1, tail1 → dividend (number to be divided)
 *     head2, tail2 → divisor
 *     headR        → result list that will store the remainder
 *
 *  Returns:
 *     SUCCESS if remainder is successfully computed
 *     FAILURE if divisor is zero or input lists are invalid
 *******************************************************************************************************************************************************************/
 
#include <stdio.h>      
#include <stdlib.h>
#include "apc.h"

int modulus(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
	// Validate input lists
	if(*head1 == NULL || *head2 == NULL)
	{
		printf("ERROR : One or Both input Lists are Empty! \n");
		return FAILURE;
	}

    // Remove garbage leading zeros from both operands 
	remove_leading_zeros(head1);
	remove_leading_zeros(head2);

    // Compare dividend and divisor 
    int compare = compare_numbers(*head1, *head2);

    // Case 1: dividend < divisor → remainder is dividend itself 
	if(compare == LESS)
	{
        Dlist *temp = *head1;
        // Copy entire dividend into result 
        while(temp)
        {
            insert_at_end(headR, tail1, temp->data);
            temp = temp->next;
        }
		return SUCCESS;
	}

    // Make a working copy of dividend (since we need to modify it) 
    Dlist *current_head = NULL, *current_tail = NULL;
    Dlist *ptr = *head1;

    while(ptr)
    {
        insert_at_end(&current_head, &current_tail, ptr->data);
        ptr = ptr->next;
    }

    // This will accumulate the running remainder 
    Dlist *rem_head = NULL;
	Dlist *rem_tail = NULL;
    ptr = current_head;

    // Long-division style remainder extraction 
    while(ptr)
    {
        // Step 1: Bring down next digit into remainder 
        insert_at_end(&rem_head, &rem_tail, ptr->data);
        // Remove zeros that appear at the front 
        remove_leading_zeros(&rem_head);
    
        // Step 2: While remainder >= divisor, subtract divisor 
        while (compare_numbers(rem_head, *head2) != LESS)
		{
			Dlist *temp = NULL;

            // rem_head = rem_head - divisor 
			subtraction(&rem_head, &rem_tail, head2, tail2, &temp);
            
            // Clean up old remainder list 
			delete_list(&rem_head, &rem_tail);

            // Replace remainder with newly computed one 
			rem_head = temp;
			rem_tail = rem_head;

            // Move tail to last node 
			while(rem_tail && rem_tail->next)
			{
				rem_tail = rem_tail->next;
			}
		}

        // Move to next digit of dividend 
        ptr = ptr->next;
    }

    // Remove any final leading zeros like 0003 → 3 
    remove_leading_zeros(&rem_head);
	// Store final remainder in result pointer 
    *headR = rem_head;

    return SUCCESS;
}