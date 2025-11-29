
/********************************************************************************************************************************************************************
 * Function: perform_operation
 * ---------------------------
 *  Performs arithmetic operations (+, -, *, /, ^) on two large numbers
 *  represented as doubly linked lists.
 *
 *  Each number has a sign ('+' or '-') and digits stored in separate lists.
 *
 *  Handles all combinations of signs and operations, and prints the final result.
 *
 *  Parameters:
 *     op        → Operator symbol: "+", "-", "*", "/", "^"
 *     sign1     → Sign of first number ('+' or '-')
 *     sign2     → Sign of second number ('+' or '-')
 *     head1, tail1 → Head and tail of first number's linked list
 *     head2, tail2 → Head and tail of second number's linked list
 *     headR, tailR → Head and tail pointers for result list
 *     digits1, digits2 → Input digit strings (used to check for zero cases)
 *
 *  Returns:
 *     SUCCESS (0) after performing and printing the result.
 *     FAILURE is not used here but can be extended if an operation fails.
*******************************************************************************************************************************************************************/


#include <stdio.h>      
#include <stdlib.h>
#include <string.h>
#include "apc.h"

int perform_operation(const char *op, 
                      char sign1, char sign2, 
                      Dlist **head1, Dlist **tail1, 
                      Dlist **head2, Dlist **tail2, 
                      Dlist **headR, Dlist **tailR, 
                      const char *digits1, const char *digits2)
{
    // Step 1: Compare the magnitudes of the two numbers
    int compare = compare_numbers(*head1 , *head2);
    char result_sign = '+'; // default sign of result

    /* =========================== ADDITION and SUBTRACTION =========================== */
    if(strcmp(op, "+") == 0 || strcmp(op, "-") == 0)
    {
        /* ---------------- Case 1: +a and +b ---------------- */
        if(sign1 == '+' && sign2 == '+')
        {
            if (strcmp(op, "+") == 0)      // +a + +b
            {
                addition(head1, tail1, head2, tail2, headR);
                result_sign = '+';
            }
            else if(strcmp(op, "-") == 0)  // +a - +b 
            {
                // If both numbers are equal, result is zero
                if(compare == EQUAL)
                {
                    printf("Result          : 0\n");
                    return SUCCESS;
                }

                subtraction(head1, tail1, head2, tail2, headR);
                result_sign = (compare == GREATER) ? '+' : '-';
            }        
        }

        /* ---------------- Case 2: -a and -b ---------------- */
        else if(sign1 == '-' && sign2 == '-')       
        {
            if (strcmp(op, "+") == 0)      // -a + -b 
            {
                addition(head1, tail1, head2, tail2, headR);
                result_sign = '-';
            }
            else if(strcmp(op, "-") == 0)  // -a - -b 
            {
                if(compare == EQUAL)
                {
                    printf("Result          : 0\n");
                    return SUCCESS;
                }

                subtraction(head1, tail1, head2, tail2, headR);
                // Result sign depends on which absolute value is larger
                result_sign = (compare == GREATER) ? '-' : '+';
            }  
        }

        /* ---------------- Case 3: +a and -b ---------------- */
        else if(sign1 == '+' && sign2 == '-')
        {
            if (strcmp(op, "+") == 0)      // +a + -b 
            {
                if(compare == EQUAL)
                {
                    printf("Result          : 0\n");
                    return SUCCESS;
                }

                subtraction(head1, tail1, head2, tail2, headR);
                result_sign = (compare == GREATER) ? '+' : '-';
            }
            else if(strcmp(op, "-") == 0)  // +a - -b 
            {
                addition(head1, tail1, head2, tail2, headR);
                result_sign = '+';
            }  
        }

        /* ---------------- Case 4: -a and +b ---------------- */
        else if(sign1 == '-' && sign2 == '+')
        {
            if (strcmp(op, "+") == 0)      // -a + +b 
            {
                if(compare == EQUAL)
                {
                    printf("Result          : 0\n");
                    return SUCCESS;
                }

                subtraction(head1, tail1, head2, tail2, headR);
                result_sign = (compare == GREATER) ? '-' : '+';
            }
            else if(strcmp(op, "-") == 0)  // -a - +b 
            {
                addition(head1, tail1, head2, tail2, headR);
                result_sign = '-';
            }  
        }

        // Print the final result for + and - operations
        printf("Result          : %c", result_sign);
        remove_leading_zeros(headR);
        print_list(*headR);
        return SUCCESS;
    }

    /* =========================== MULTIPLICATION =========================== */
    else if(strcmp(op, "*") == 0)
    {
        // Check for zero multiplication cases
        if((strcmp(digits1, "0") == 0) || (strcmp(digits2, "0") == 0))
        {
            printf("Result          : 0\n");
            return SUCCESS;
        }

        // Perform multiplication
        multiplication(head1, tail1, head2, tail2, headR);

        // Determine result sign based on input signs
        if((sign1 == '-' && sign2 == '+') || (sign1 == '+' && sign2 == '-'))
            result_sign = '-';
        else
            result_sign = '+';

        // Clean result (remove unnecessary zeros)
        remove_leading_zeros(headR);

        // Check if the final list represents zero
        if(result_is_zero(*headR) == SUCCESS)
        {
            printf("Result          : 0\n");
            return SUCCESS;
        }
        printf("Result          : %c", result_sign);
        print_list(*headR);
        return SUCCESS;
    }

    /* =========================== SQUARE (^) =========================== */
    else if(strcmp(op, "^") == 0)
    {
        // Case: 0 raised to anything is 0
        if(strcmp(digits1, "0") == 0)
        {
            printf("Result          : 0\n");
            return SUCCESS;
        }
        else
        {
            // The provided 'square()' function handles only squaring (a^2)
            square(head1 ,tail1 ,headR);
            printf("Result          : +");
            remove_leading_zeros(headR);
            print_list(*headR);
            return SUCCESS;
        }
    }

    /* =========================== DIVISION =========================== */
    else if(strcmp(op, "/") == 0)
    {
        // Case: 0 ÷ anything = 0
        if(strcmp(digits1, "0") == 0)
        {
            printf("Result          : 0\n");
            return SUCCESS;
        }

        // Case: Division by zero is invalid
        else if(strcmp(digits2, "0") == 0)
        {
            printf("Result          : Cannot divide by Zero!\n");
            return SUCCESS;
        }

        else
        {
            // Perform division
            division(head1, tail1, head2, tail2, headR);

            // Determine result sign (negative if signs differ)
            if((sign1 == '-' && sign2 == '+') || (sign1 == '+' && sign2 == '-'))
                result_sign = '-';
            else
                result_sign = '+';   

            // Clean result (remove unnecessary zeros)
            remove_leading_zeros(headR);

            // Check if the final list represents zero
            if(result_is_zero(*headR) == SUCCESS)
            {
                printf("Result          : 0\n");
                return SUCCESS;
            }
            printf("Result          : %c", result_sign);
            print_list(*headR);
            return SUCCESS;
        
        }
    }

    /* =========================== MODULUS =========================== */
    else if(strcmp(op, "%") == 0)
    {
        // Case: 0 ÷ anything = 0
        if(strcmp(digits1, "0") == 0)
        {
            printf("Result          : 0\n");
            return SUCCESS;
        }

        // Case: Division by zero is invalid
        else if(strcmp(digits2, "0") == 0)
        {
            printf("Result          : Cannot perform modulus by Zero!\n");
            return SUCCESS;
        }

        else
        {
            // Perform division
            modulus(head1, tail1, head2, tail2, headR);

            result_sign = sign1;
            // Clean result (remove unnecessary zeros)
            remove_leading_zeros(headR);

            // Check if the final list represents zero
            if(result_is_zero(*headR) == SUCCESS)
            {
                printf("Result          : 0\n");
                return SUCCESS;
            }
            printf("Result          : %c", result_sign);
            print_list(*headR);
            return SUCCESS;
        }
    }
}