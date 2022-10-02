# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchetana <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 19:30:12 by cchetana          #+#    #+#              #
#    Updated: 2022/10/02 13:12:00 by cchetana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus

INC_DIR	= includes/
SRC_DIR	= srcs/
OBJ_DIR	= objs/

INC_FIL	= philo_bonus
SRC_FIL	= philo_bonus \
			philo_init philo_life philo_forks \
			philo_error philo_helper philo_checker

INCS	= $(addprefix -I, $(INC_DIR))
SRCS	= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FIL)))
OBJS	= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FIL)))

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -g
RM		= rm -rf

BORG	= "\033[1;38;5;220m"
SYEL	= "\033[38;5;229m"
ENDCL	= "\033[0;37m"

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCS) $(SRCS) -o $(NAME)
	@echo $(BORG)"... philo ... bonus ..."$(ENDCL)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

bonus: all

clean:
	@$(RM) $(OBJ_DIR)
	@echo $(SYEL)"... finished cleaning ..."$(ENDCL)

fclean: clean
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@$(RM) $(NAME).dSYM
	@echo $(SYEL)"... finished f-cleaning ..."$(ENDCL)

re: fclean all

.PHONY: all clean fclean re bonus
