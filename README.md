# Brainfuck Interpreter
A simple [brainfuck](https://esolangs.org/wiki/Brainfuck) interpreter, written in C.

## Usage
The program takes 1 optional argument, specifying the file to read the code from.  If unspecified, code will be read from STDIN.

Note: file input is currently untested.

## Brainfuck
There are multiple variants of how brainfuck should behave, however the basic structure consists of the following 8 commands, which manipulate an ordered list of numeric values, one of which is pointed to at a time.

### Commands
| Symbol | Behaviour | Code |
| - | - | - |
| `+` | Increment the value at the pointer by 1. | `++*p` |
| `-` | Decrement the value at the pointer by 1. | `--*p` |
| `>` | Move the pointer right by one. | `++p` |
| `<` | Move the pointer left by 1. | `--p` |
| `[` | Start of loop.  Skip to respective `]` if the value at the pointer is zero. | `*p == 0 ? skip_loop() : push(p)` |
| `]` | End of loop.  Jump back to respective `[` is the value at the pointer is non-zero. | `*p == 0 ? pop(p) : p = peek()` |
| `.` | Output value at pointer as a character. | `putchar(*p)` |
| `,` | Read one character to the value at the pointer. | `*p = getchar()` |
| Anything else | Ignore | `nop()` |

### Implementation

For my implementation, I used cells with values from 0-255 which wrap on overflow (`255+1=0`).  The tape is unbounded until the computer decides it's had enough however the loops can only currently be nested to 16 layers.  I intend to make this unbounded.
