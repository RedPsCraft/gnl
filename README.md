*This project has been created as part of the 42 curriculum by jloechle.*

## Description

Get Next Line reads and returns one line at a time from a file descriptor. This project teaches static variables, buffer management, and efficient file I/O in C.

**Goal:** Create a function that reads a file line by line through successive calls, handling any BUFFER_SIZE and edge cases (empty files, missing trailing newline, etc.).

## Instructions

**Compilation:**
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

## Resources

**Documentation:**
- [read(2) man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [C Static Variables](https://www.geeksforgeeks.org/static-variables-in-c/)

**AI Usage:**
AI was not used for code generation.

## Algorithm

**Core concept:** Use a static variable `left` to preserve data between function calls.

**Workflow:**
1. **Validate** fd and BUFFER_SIZE
2. **Read** from fd into buffer until `\n` found or EOF
3. **Accumulate** data in static variable `left`
4. **Extract** first line from `left` (up to and including `\n`)
5. **Update** `left` with remaining data for next call
6. **Return** line (or NULL if EOF/error)

**Example with buffer "Hello\nWorld\n42":**
```
Call 1: Returns "Hello\n"    → left = "World\n42"
Call 2: Returns "World\n"    → left = "42"
Call 3: Returns "42"         → left = NULL
Call 4: Returns NULL         → EOF
```

**Key decisions:**
- **Static variable:** Preserves unconsumed data between calls
- **Dynamic BUFFER_SIZE:** Works with any value (1, 42, 1000000)
  - Small = more read() calls (slower)
  - Large = fewer read() calls (faster but more memory)
- **Memory management:** Caller must free returned line; internal allocations freed on error/EOF
- **Edge cases:** Empty files, no trailing newline, lines with only `\n` all handled correctly