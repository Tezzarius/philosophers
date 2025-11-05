#Makefile for Philosophers Project

# Project name
NAME = philo

# Suppress directory change
MAKEFLAGS += --no-print-directory

# Colours
GREEN = \033[0;32m
RED = \033[0;31m

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -pthread
INCLUDES = -I./inc

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRC =	src/forks.c\
		src/init.c\
		src/main.c\
		src/monitor.c\
		src/philo.c\
		src/setup.c\
		src/utils.c

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
HEAD = inc/philo.h

# Rules
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) Compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEAD)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)🧹 Object files removed!"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)🧹 $(NAME) removed!"

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug