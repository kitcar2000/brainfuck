#include <stdlib.h>

// Represents a stack of char.  Nothing exciting.  Could have mostly reused char_tape.
struct char_ptr_stack
{
    char *head;                  // The value at the current cell.
    struct char_ptr_stack *tail; // The cell to the right of the current.
};

// Create a stack (pointer to a char_ptr_stack structure).
struct char_ptr_stack *create_stack(char *value, struct char_ptr_stack *tail)
{
    struct char_ptr_stack *stack = (struct char_ptr_stack *)malloc(sizeof(struct char_ptr_stack));
    *stack = (struct char_ptr_stack){.head = value, .tail = tail};
    return stack;
}

// Free memory used by stack.
void destroy_stack(struct char_ptr_stack *stack)
{
    struct char_ptr_stack *currentStack, *nextStack;

    nextStack = stack;
    while (nextStack != NULL)
    {
        currentStack = nextStack;
        nextStack = nextStack->tail;
        free((void *)currentStack);
    }
}

// Pop from stack, return popped value.
char *stack_pop(struct char_ptr_stack **stack)
{
    char *result = (*stack)->head;
    struct char_ptr_stack *new = (*stack)->tail;
    free(*stack);
    *stack = new;
    return result;
}

// Push a value to a stack.
void stack_push(struct char_ptr_stack **stack, char *value)
{
    *stack = create_stack(value, *stack);
}