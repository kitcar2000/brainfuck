#include "stack.c"
#include "tape.c"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define CODE_MAX_LENGTH 2048

int main(int argc, const char **argv)
{
    struct char_tape *tape = create_tape('\x00', NULL, NULL);
    char *code = malloc(CODE_MAX_LENGTH);
    struct char_ptr_stack *stk = create_stack(code, NULL);
    switch (argc)
    {
    case 1:
        gets(code);
        break;
    case 2:
    {
        FILE *f = fopen(argv[1], "rb");
        size_t length = fread(code, sizeof(char), CODE_MAX_LENGTH, f);
        fclose(f);
        break;
    }
    default:
        printf("%i", argc);
        return 1;
    }
    while (*(stk->head) != '\0')
    {
        switch (*(stk->head))
        {
        case '+':
            ++(stk->head);
            increment_tape(tape);
            break;
        case '-':
            ++(stk->head);
            decrement_tape(tape);
            break;
        case '>':
            ++(stk->head);
            tape = get_tape_right(tape, '\x00');
            break;
        case '<':
            ++(stk->head);
            tape = get_tape_left(tape, '\x00');
            break;
        case '[':
            if (tape->value)
            {
                ++(stk->head);
                stack_push(&stk, stk->head);
            }
            else
            {
                int depth = 1;
                while (depth > 0)
                    switch (*(++(stk->head)))
                    {
                    case '[':
                        ++depth;
                        break;
                    case ']':
                        --depth;
                        break;
                    }
                ++(stk->head);
            }
            break;
        case ']':
            if (tape->value)
                stk->head = stk->tail->head;
            else
            {
                char *p = stack_pop(&stk);
                stk->head = p + 1;
            }
            break;
        case '.':
            ++(stk->head);
            putchar(tape->value);
            break;
        case ',':
            ++(stk->head);
            tape->value = getchar();
            break;
        default:
            ++(stk->head);
        }
    }
    free((void *)code);
    destroy_stack(stk);
    destroy_tape(tape);
    return 0;
}