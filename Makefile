# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 15:48:51 by nnourine          #+#    #+#              #
#    Updated: 2024/04/19 09:22:08 by nnourine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color
COLOR = \033[0;34m
RESET_COLOR = \033[0m

# Executable name
NAME = minishell

# Directories
SRCDIR = src
OBJDIR = obj
INCDIR = include
LIBFT = lib/libft

# Files
SRCS =  $(SRCDIR)/main.c \
		$(SRCDIR)/utility.c \
		$(SRCDIR)/create_cmd_list.c \
		$(SRCDIR)/create_file_list.c \
		$(SRCDIR)/create_raw_cmd.c \
		$(SRCDIR)/fill_raw_cmd_list.c \
		$(SRCDIR)/fill_index_cmd_list.c \
		$(SRCDIR)/fill_heredoc_cmd_list.c \
		$(SRCDIR)/cmd_count.c
		
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Compiler and flags
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
GENERAL_LIB_FLAGS = -L$(LIBFT) -lft
ADDRESS_SANITIZE = -fsanitize=address
LLDB = -g
READLINE = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

# Phony targets
.PHONY: all clean fclean re address lldb

# Default target
all: $(NAME)

# Linking
$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT)
	@$(CC) $(CFLAGS) $(GENERAL_LIB_FLAGS) $(READLINE) $(OBJS) -o $@
	@echo "$(COLOR)Compiling and linking: done$(RESET_COLOR)"

# Compiling
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Clean-up
clean:
	@$(RM) -r $(OBJDIR)
	@$(MAKE) -C $(LIBFT) clean
	@echo "$(COLOR)Clean-up: done$(RESET_COLOR)"

# Full clean
fclean:
	@$(RM) -r $(OBJDIR)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@echo "$(COLOR)Full clean: done$(RESET_COLOR)"

# Recompile
re: fclean all

# Address sanitizer
address: fclean
address: CFLAGS += $(ADDRESS_SANITIZE)
address: all

# LLDB
lldb: fclean
lldb: CFLAGS += $(LLDB)
lldb: CC = clang
lldb: all