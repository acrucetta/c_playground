# Compiler
CC = gcc

# Compiler flags
CFLAGS = -pthread -Wall -Wextra

# Source files
SRCS = approx_counter.c conc_ds.c conc_linkedlist.c conc_list.c counter.c

# Executable names (same as source files without .c extension)
EXES = $(SRCS:.c=)

# Default target
all: $(EXES)

# Rule to build each executable
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean target
clean:
	rm -f $(EXES)
	rm -f *.o
	rm -f *~ core

# Phony targets
.PHONY: all clean
