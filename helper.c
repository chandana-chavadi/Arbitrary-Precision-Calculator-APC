#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "apc.h"


/* =========================================================================================
 * Function: check_sign
 * -----------------------------------------------------------------------------------------
 *  Validates that the input string represents a valid signed number (+ / - optional).
 *  Ensures that all remaining characters after the sign are digits.
 *
 *  Returns: SUCCESS if valid, FAILURE if invalid or empty.
 * ========================================================================================= */

int check_sign(const char *s)
{
    if(s == NULL || *s == '\0')
    {
        return FAILURE;
    }

    int i=0;
    // Skip optional leading '+' or '-'
    if(s[0] == '+' || s[0] == '-')
    {
        i = 1;
    }

    // If only the sign exists without digits
    if(s[i] == '\0')
    {
        return FAILURE;
    }

    // Verify that all remaining characters are digits
    while (s[i] != '\0')
    {
        if(!isdigit(s[i]))
        {
            return FAILURE;
        }
        i++;
    }

    return SUCCESS;
}



/* =========================================================================================
 * Function: validate_arguments
 * -----------------------------------------------------------------------------------------
 *  Ensures valid command-line arguments and correct operator.
 *  Usage format: ./a.out <num1> <operator> <num2>
 *
 *  Allowed operators: +  -  *  /  ^  %
 *  Notes: For shell interpretation, enclose * / ^ % in quotes.
 * ========================================================================================= */

int validate_arguments(int argc , char* argv[])
{
    // Require exactly 4 arguments (program name + 3 inputs)
    if(argc != 4)
    {
        printf("ERROR : Invalid Number of Arguments!\n");
        printf("USAGE : ./a.out <num1> <operator> <num2>\n");
        printf("Operations that can be performed: \n");
        printf("+ --> Addition \n");
        printf("- --> subtraction \n");
        printf("* --> Multiplication \n");
        printf("/ --> Division \n");
        printf("^ --> Square \n");
        printf("%% --> Modulus \n");
        printf("Note: Use quotes for special symbols (*, /, ^, %%).\n");
        return FAILURE;
    }

    // Validate both operands
    if (check_sign(argv[1]) == FAILURE)
    {
        printf("ERROR : Operand 1 failed validation ->  %s\n", argv[1]);
    }
    if (check_sign(argv[3]) == FAILURE)
    {
        printf("ERROR : Operand 2 failed validation ->  %s\n", argv[3]);
    }
    
    // Validate operator
    if (strcmp(argv[2], "+") != 0 && strcmp(argv[2], "-") != 0 && strcmp(argv[2], "*") != 0 && strcmp(argv[2], "/") != 0 && strcmp(argv[2], "^") != 0 && strcmp(argv[2], "%") != 0)
    {
    {
        printf("ERROR : Enter Only these Operators [+,-,*,/,^,%%] \n");
        return FAILURE;
    }
    }
    return SUCCESS;
}


/* =========================================================================================
 * Function: remove_sign
 * -----------------------------------------------------------------------------------------
 *  Separates sign (+ / -) from the numeric string.
 *  Sets `*digits` pointer to the part of the string containing only digits.
 *
 *  Returns: '+' or '-' depending on sign of input.
 * ========================================================================================= */

char remove_sign(const char *s, const char **digits)
{
    char sign = '+';
    if (s[0] == '+' || s[0] == '-')
    {
        sign = s[0];
        *digits = s + 1;   // Skip sign
    }
    else
    {
        *digits = s;       // No sign, treat as positive
    }
    return sign;
}


/* =========================================================================================
 * Function: string_to_list
 * -----------------------------------------------------------------------------------------
 *  Converts a numeric string into a doubly linked list.
 *  Each digit is stored as a separate node in the list.
 *
 *  Returns: SUCCESS if successful, FAILURE otherwise.
 * ========================================================================================= */

int string_to_list(Dlist **head, Dlist **tail, char *str)
{
    if (!str || *str == '\0')        // empty or NULL input
    {
        printf("ERROR : Empty string input.\n");
        return FAILURE;
    }

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))       // reject non-digit characters
        {
            printf("ERROR : Invalid character '%c'\n", str[i]);
            return FAILURE;
        }

        if (insert_at_end(head, tail, str[i] - '0') == FAILURE)
        {
            printf("ERROR : Node creation failed.\n");
            return FAILURE;
        }
    }

    return SUCCESS;
}


/* =========================================================================================
 * Function: insert_at_end
 * -----------------------------------------------------------------------------------------
 *  Inserts a new node with given data at the end of the doubly linked list.
 *
 *  Returns: SUCCESS if inserted, FAILURE if memory allocation fails.
 * ========================================================================================= */

int insert_at_end(Dlist **head, Dlist **tail, data_t data)
{
    Dlist *newnode;
    newnode = malloc(sizeof(Dlist));
    if(newnode == NULL)
    {
        return FAILURE;
    }
    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;
    
    // If list is empty, new node becomes both head and tail
    if(*head == NULL)
    {
        *head = newnode;
        *tail = newnode;
        return SUCCESS;
    }

    // Link new node after tail
    newnode->prev = *tail;
    (*tail)->next = newnode;
    (*tail) = newnode;

    return SUCCESS;
}


/* =========================================================================================
 * Function: insert_at_begin
 * -----------------------------------------------------------------------------------------
 *  Inserts a new node with given data at the beginning of the list.
 *
 *  Returns: SUCCESS if successful, FAILURE if memory allocation fails.
 * ========================================================================================= */

int insert_at_begin(Dlist **head, Dlist **tail, data_t data)
{
    Dlist *newnode;
    newnode = malloc(sizeof(Dlist));
    if(newnode == NULL)
    {
        return FAILURE;
    }
    newnode->data = data;
    newnode->prev = NULL;
    newnode->next = *head;
    
    // If list is empty
    if (*head == NULL)
    {
        *head = *tail = newnode;
        return SUCCESS;
    }

    // Link new node before head
    (*head)->prev = newnode;
    *head = newnode;
    
    return SUCCESS;
}



/* =========================================================================================
 * Function: print_list
 * -----------------------------------------------------------------------------------------
 *  Prints all digits in the linked list (head → tail order).
 *  Displays an error if the list is empty.
 * ========================================================================================= */

void print_list(Dlist *head)
{
    if (head == NULL)               // no digits to print
    {
        printf("ERROR : Empty list\n");
        return;
    }
    Dlist *temp = head;

    while (temp != NULL)            // iterate list
    {
        printf("%d", temp->data);   // print digit
        temp = temp->next;          // move forward
    }

    printf("\n");                   // end of output
}


/* =========================================================================================
 * Function: find_length
 * -----------------------------------------------------------------------------------------
 *  Counts and returns the total number of nodes in a doubly linked list.
 * ========================================================================================= */

int find_length(Dlist *head)
{
    int length = 0;
    Dlist *temp = head;

    while(temp)             // walk through the list
    {
        length++;           // count each node
        temp = temp->next;  // move to next
    }
    return length;          // total number of nodes
}


/* =========================================================================================
 * Function: compare_numbers
 * -----------------------------------------------------------------------------------------
 *  Compares two numbers represented as doubly linked lists.
 *
 *  Returns:
 *     GREATER (1) if h1 > h2
 *     LESS    (-1) if h1 < h2
 *     EQUAL   (0)  if both are same
 * ========================================================================================= */

int compare_numbers(Dlist *h1, Dlist *h2)
{
    // Compare based on length first
    if(find_length(h1) > find_length(h2))
    {
        return GREATER;
    }

    else if(find_length(h1) < find_length(h2))
    {
        return LESS;
    }

    else
    {
        // Compare digit by digit if lengths are equal
        Dlist *p1 = h1, *p2 = h2;
        while(p1 && p2)
        {
            if(p1->data > p2->data)
            {
                return GREATER;
            }
            else if(p1->data < p2->data)
            {
                return LESS;
            }
            else
            {
                p1 = p1->next;
                p2 = p2->next;
            }
        }

        return EQUAL;
    }
}

/****************************************************************************************************
 * Function: remove_leading_zeros
 * ------------------------------
 * Removes redundant leading zeros from the result list.
 * Example: 000123 → 123, 0000 → 0
 ****************************************************************************************************/

void remove_leading_zeros(Dlist **head)
{
    if(*head == NULL)       // nothing to clean
    return;

    // delete zeros while more digits follow
    while((*head)->next && (*head)->data == 0)
    {
        Dlist *temp = *head;
        *head = (*head)->next;             // move head forward
        (*head)->prev = NULL;              // fix backward link
        free(temp);                        // free old zero node
    }

    // if single node AND it is zero → keep it (represents number 0)
    if((*head)->next == NULL && (*head)->data == 0)
    return;
}

/****************************************************************************************************
 * Function: result_is_zero
 * ------------------------
 * Checks if all digits in the given list are zero.
 ****************************************************************************************************/
 
int result_is_zero(Dlist *head)
{
    if(head == NULL)        // empty list treated as zero
    return SUCCESS;

    while(head)             // scan each digit
    {
        if(head->data != 0) // found a non-zero digit
        return FAILURE;
    head = head->next;
    }
    return SUCCESS;         // all digits were zero
}

/*****************************************************************************************
 * Function: delete_list
 * ------------------------
 * Frees all nodes in a doubly linked list and resets head and tail to NULL.
 * head, tail : Pointers to the list’s head and tail.
 * Removes every node to prevent memory leaks during operations like multiplication.
 * Returns SUCCESS.
 *****************************************************************************************/

int delete_list(Dlist **head, Dlist **tail)
{
    if(*head == NULL)   // Nothing to delete
    return SUCCESS;

    Dlist *temp = *head;
    // Traverse and free every node
    while(temp)
    {
        Dlist *next = temp->next;   // Save next pointer
        free(temp);                 // Free current node
        temp = next;                // Move ahead
    }
    *head = NULL;                   // Reset head
    *tail = NULL;                   // Reset tail
    return SUCCESS;
}