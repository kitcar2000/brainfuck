#include "tape.c"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define CODE_MAX_LENGTH 2048
#define STACK_SIZE 16

int main(int argc, const char **argv)
{
    struct char_tape *tape = create_tape('\x00', NULL, NULL);
    char **stk = (char **)malloc(STACK_SIZE * sizeof(char *));
    *stk = (char *)malloc(CODE_MAX_LENGTH);
    char **stk_top = stk;
    switch (argc)
    {
    case 1:
        gets(*stk);
        break;
    case 2:
    {
        FILE *f = fopen(argv[1], "rb");
        size_t length = fread(*stk, sizeof(char), CODE_MAX_LENGTH, f);
        //*stk_top = realloc(*stk_top, length);
        fclose(f);
        break;
    }
    default:
        printf("%i", argc);
        return 1;
    }
    while (**stk != '\0')
    {
        switch (**stk)
        {
        case '+':
            ++*stk;
            increment_tape(tape);
            break;
        case '-':
            ++*stk;
            decrement_tape(tape);
            break;
        case '>':
            ++*stk;
            tape = get_tape_right(tape, '\x00');
            break;
        case '<':
            ++*stk;
            tape = get_tape_left(tape, '\x00');
            break;
        case '[':
            if (tape->value)
            {
                ++*stk;
                *++stk = *(stk - 1);
            }
            else
            {
                int depth = 1;
                while (depth > 0)
                    switch (*++*stk)
                    {
                    case '[':
                        ++depth;
                        break;
                    case ']':
                        --depth;
                        break;
                    }
                ++*stk;
            }
            break;
        case ']':
            if (tape->value)
                *stk = *(stk - 1);
            else
                *(--stk) = *(stk + 1) + 1;
            break;
        case '.':
            ++*stk;
            putchar(tape->value);
            break;
        case ',':
            ++*stk;
            tape->value = getchar();
            break;
        default:
            ++*stk;
        }
    }
    //free((void *)*stk_top);
    free((void *)stk_top);
    destroy_tape(tape);
    return 0;
}