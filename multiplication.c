/*******************************************************************************************************************************************************************
 * Function: MUTLIPLICATION
 * -------------------------
 *  Multiplies two large numbers represented as doubly linked lists.
 *  Each node in the linked list stores a single digit (most significant at head).
 *
 *  Example:
 *     List1: 1 <-> 2 <-> 3   (represents 123)
 *     List2: 4 <-> 5         (represents 45)
 *     Result: 5 <-> 5 <-> 3 <-> 5  (represents 5535)
 *
 *  Algorithm:
 *     - Perform digit-by-digit multiplication similar to manual long multiplication.
 *     - For each digit in the second number (starting from least significant),
 *       multiply it by all digits of the first number.
 *     - Generate partial results, shift appropriately (append zeros),
 *       and add to cumulative result.
 *
 *  Parameters:
 *     head1, tail1 → pointers to first and last node of first number
 *     head2, tail2 → pointers to first and last node of second number
 *     headR        → pointer to the head of result list (stores result)
 *
 *  Returns:
 *     SUCCESS (0) if multiplication succeeds
 *     FAILURE (-1) if any error occurs
 *
*******************************************************************************************************************************************************************/
#include <stdio.h>      
#include <stdlib.h>
#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
    // Validate input lists (both numbers must exist)
	if(*head1 == NULL || *head2 == NULL)
	{
		printf("ERROR : One or Both input Lists are Empty! \n");
		return FAILURE;
	}

    // Final result list
    Dlist *result_head = NULL, *result_tail = NULL;

    // Start multiplying from LSB of second number
	Dlist *t2 = *tail2;
	int shift = 0;  // How many zeroes to append (place value)

	while(t2 != NULL)
	{
        // Partial product list for each digit of num2
		Dlist *partial_head = NULL, *partial_tail = NULL;
		int carry = 0;

		// Start from LSB of first number
		Dlist *t1 = *tail1;

        // Multiply one digit of num2 with entire num1
		while(t1 != NULL)
		{
			int product = (t1->data * t2->data) + carry;    // multiply + carry
			carry = product / 10;                          // next carry
			product = product % 10;                        // single digit result

            // Insert at front because we are traversing digits right→left
			insert_at_begin(&partial_head, &partial_tail, product);

			t1 = t1->prev;   // move to next more significant digit
		}

        // If leftover carry exists, add it at the beginning
		if(carry)
		{
			insert_at_begin(&partial_head, &partial_tail, carry);
		}

        // Append zeros at the end to match place value of current digit in num2
		for(int i = 0; i < shift; i++)
		{
			insert_at_end(&partial_head, &partial_tail, 0);
		}

        // First partial product → directly copy to result
		if(result_head == NULL)
		{
			Dlist *temp = partial_head;
			while(temp)
			{
				insert_at_end(&result_head, &result_tail, temp->data);
				temp = temp->next;
			}
		}
        else
		{
            // Add partial product to cumulative result
			Dlist *new_head = NULL , *new_tail = NULL;

			addition(&result_head, &result_tail, &partial_head, &partial_tail, &new_head);

            // Delete old result and replace with updated one
			delete_list(&result_head, &result_tail);
			result_head = new_head;

            // Move to tail of the updated result
			Dlist *temp = result_head;
			while(temp && temp->next)
			{
				temp = temp->next;
			}
			result_tail = temp;
		}

        // Clear partial list after use
		delete_list(&partial_head, &partial_tail);

        // Next digit of num2 gets one more trailing zero
		shift++;

        // Move to next more significant digit of num2
        t2 = t2->prev; 
	}

    // Store final result list
	*headR = result_head;
	return SUCCESS;
}


