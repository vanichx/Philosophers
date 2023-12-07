# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/27 10:06:26 by ipetruni          #+#    #+#              #
#    Updated: 2023/12/07 17:30:42 by ipetruni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SETUP OF THE PROGRAM

NAME = philo

# FILES AND PATH TO THEM

OBJ_DIR = obj/
SRC_DIR = src/

SRC	=	main \
		parse \
		routine \
		threads \
		utils 

SRCS =  $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

# COMMANDS

CC = gcc 
FLAGS = -Wall -Wextra -Werror 
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) was successfully created!$(DEFAULT)"
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I./includes -c $< -o $@
	

clean:
		@$(RM) $(OBJS)
		@$(RM) $(OBJ_DIR)
		@echo "$(YELLOW)philo objects files deleted!$(DEFAULT)"
	
fclean: clean
		@$(RM) $(NAME)
		@echo "$(RED)philo program and objects deleted!$(DEFAULT)"

re:		fclean all

.PHONY: all clean fclean re

# COLORS DEFENITIONS

RED = \033[1;31m
DEFAULT = \033[0m
GREEN = \033[1;32m
BOLD = \033[1m
YELLOW = \033[1;33m