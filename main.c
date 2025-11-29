/**************************************************************************************************************************************************************
* Title          : APC (Arbitrary Precision Calculator)
* Description    :
*                  The Arbitrary Precision Calculator (APC) is a C program designed to perform arithmetic operations 
*                  on very large integers that exceed the size limits of standard data types such as int or long. 
*                  The program represents each number as a doubly linked list, where each node stores a single digit. 
*                  This allows accurate computation of large values without overflow. 
*                  
*                  The APC supports addition (+), subtraction (-), multiplication (*), division (/), square (^), 
*                  and modulus (%) operations. It handles positive and negative numbers and includes 
*                  validation for invalid inputs or division/modulus by zero. 
*                  
*                  The project uses linked lists to execute arithmetic operations. 
*                  It provides a command-line interface for user interaction, where inputs are taken as:
*                      ./a.out <number1> <operator> <number2>
*                       note : For shell interpretation, enclose * / ^ % in quotes.
*                  
*                  Example:
*                      ./a.out +12345 "*" -56
*                  
*                  Output:
*                      Operand 1       : +12345
*                      Operation       : *
*                      Operand 2       : -56
*                      ----------------------------------------
*                      Result          : -691320
*                      ----------------------------------------
*                      APC Calculator Execution Completed.
*                  
*                  This project highlights the power of data structures in solving real-world problems 
*                  like arbitrary precision arithmetic.
*
* Name           : C Chandana
* Admission id   : 25017_241
* Date           : 3/11/2025
**************************************************************************************************************************************************************/


/* =========================================================================================
* Function       : main function (Driver function)
* Description    : Entry point for the APC (Arbitrary Precision Calculator) program.
*                  This function drives the execution of all arithmetic operations 
*                  using doubly linked list representations of large numbers.
* ========================================================================================= */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apc.h"

int main(int argc, char *argv[])
{
    // Validate command-line arguments (e.g., ./a.out <num1> <operator> <num2>)
    if (validate_arguments(argc, argv) == FAILURE)
        return 0;

    // Declare head and tail pointers for all operand and result lists
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *headR = NULL, *tailR = NULL;;

    // Extract sign and digit portions from input strings
    const char *digits1 , *digits2;
    char sign1 = remove_sign(argv[1], &digits1);
    char sign2 = remove_sign(argv[3], &digits2);

    // ---------- Convert strings (digits only) to lists ----------
    if (string_to_list(&head1, &tail1, (char *)digits1) == FAILURE)
    {
        printf("ERROR: Failed to create list for operand 1.\n");
        return 0;
    }

    if (string_to_list(&head2, &tail2, (char *)digits2) == FAILURE)
    {
        printf("ERROR: Failed to create list for operand 2.\n");
        return 0;
    }
    remove_leading_zeros(&head1);
    remove_leading_zeros(&head2);


    // ---------- Display input operands ----------
    printf("Operand 1       : %c", sign1);
    print_list(head1);
    printf("Operation       : %s\n",argv[2]);
    printf("Operand 2       : %c", sign2);
    print_list(head2);

    printf("----------------------------------------\n");

    /* ---------------- Perform the requested arithmetic operation ----------------
       argv[2] contains the operator symbol: "+", "-", "*", "/", "^", "%".
       perform_operation() calls the appropriate function based on the operator and operand signs. */
    if (perform_operation(argv[2], sign1, sign2, &head1, &tail1, &head2, &tail2, &headR, &tailR, digits1, digits2) == FAILURE)
    {
        printf("ERROR : Operation Failed! \n");
    }
    printf("----------------------------------------\n");
    printf("APC Calculator Execution Completed.\n");
    return 0;
}


