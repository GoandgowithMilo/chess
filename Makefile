# Project files
OBJS = main.c interface.c

# Executable Name
NAME = chess.out

# Compiler
CC = gcc

# Compiler flags
COMPILER_FLAG = -Wall -Werror

# Linker flags
LINKER_FLAGS = -lSDL2

# Target
all: $(OBJS) 
	$(CC) $(OBJS) $(COMPILER_FLAG) $(LINKER_FLAGS) -o $(NAME)