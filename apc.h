#ifndef APC_H
#define APC_H

/* Return codes */
#define SUCCESS 0
#define FAILURE -1


/* Comparison results */
#define GREATER   1
#define EQUAL     0
#define LESS     -1

typedef int data_t;

/* Doubly linked list node: `prev` and `next` pointers and a single digit `data`. */
typedef struct node
{
	struct node *prev;
	data_t data;
	struct node *next;
}Dlist;



// ------------------> Helper functions <-------------------

// Check and return sign of string: + / - or default.
static int check_sign(const char *s);

// Validate Command Line arguments (argc, argv) for your program;
int validate_arguments(int argc , char* argv[]);

// Convert numeric string to doubly linked list (one digit per node).
int string_to_list(Dlist **head, Dlist **tail, char *str);

// Insert a digit at the end (tail) of the list.
int insert_at_end(Dlist **head, Dlist **tail, data_t data);

// Insert a digit at the beginning (head) of the list.
int insert_at_begin(Dlist **head, Dlist **tail, data_t data);

// Return the number of nodes (digits) in the list.
int find_length(Dlist *head);

// Compare two numbers represented by lists: return GREATER, EQUAL or LESS.
int compare_numbers(Dlist *h1, Dlist *h2);

// Print the number stored in the list.
void print_list(Dlist *head);

// Remove sign char from input string and also set digits pointer.
char remove_sign(const char *s, const char **digits);

// Operation handler - Performs the requested operation and prints results as needed.
int perform_operation(const char *op, char sign1, char sign2, Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, const char *digits1, const char *digits2);

// Remove Leading Zero's
void remove_leading_zeros(Dlist **head);

// Checks if the given number list represents zero (all digits are 0); returns SUCCESS if true, else FAILURE.
int result_is_zero(Dlist *head);

// delete_list: frees all nodes in the list and resets head/tail to NULL
int delete_list(Dlist **head, Dlist **tail);


// ------------------> Arithmetic operations <-------------------

// Addition
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);

// Subtraction
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);

// Multiplication
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);

// Square
int square(Dlist **head1, Dlist **tail1, Dlist **headR);

// Division
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);

// Modulus
int modulus(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);

#endif
