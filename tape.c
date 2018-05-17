#include <stdlib.h>

// Represents a tape similar to that of a Turing Machine with a char value at each cell.
// Basically a linked list.
struct char_tape
{
    char value;              // The value at the current cell.
    struct char_tape *left;  // The cell to the left of the current.
    struct char_tape *right; // The cell to the right of the current.
};

// Create a tape (pointer to a char_tape structure).
struct char_tape *create_tape(char value, struct char_tape *left, struct char_tape *right)
{
    struct char_tape *tape = (struct char_tape *)malloc(sizeof(struct char_tape));
    *tape = (struct char_tape){.value = value, .left = left, .right = right};
    return tape;
}

// Free memory used by tape.
void destroy_tape(struct char_tape *tape)
{
    if (tape->left != NULL)
    {
        tape->left->right = NULL; // Prevent infinite recursion when destroying left tape.
        destroy_tape(tape->left);
    }
    if (tape->right != NULL)
    {
        tape->right->left = NULL; // Prevent infinite recursion when destroying right tape.
        destroy_tape(tape->left);
    }
    free((void *)tape);
}

// Get the cell to the left of the current on a char_tape structure.
struct char_tape *get_tape_left(struct char_tape *tape, char default_value)
{
    if (tape->left == NULL) // If undefined, create new cell.
        tape->left = create_tape(default_value, NULL, tape);
    return tape->left;
}

// Get get the cell to the right of the current on a char_tape structure.
struct char_tape *get_tape_right(struct char_tape *tape, char default_value)
{
    if (tape->right == NULL) // If undefined, create new cell.
        tape->right = create_tape(default_value, tape, NULL);
    return tape->right;
}

// Increment the current value on a char_tape structure.
void increment_tape(struct char_tape *tape)
{
    if (tape->value == '\xff')
        tape->value = '\x00';
    else
        ++tape->value;
}

// Decrement the current value on a char_tape structure.
void decrement_tape(struct char_tape *tape)
{
    if (tape->value == '\x00') // Handle underflow when decrementing past 0.
        tape->value = '\xff';
    else
        --(tape->value);
}