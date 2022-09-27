NAME	= philo
BNAME	= philo_bonus

INC_DIR	= includes/
SRC_DIR	= srcs/
OBJ_DIR	= objs/

INC_FIL	= philo
SRC_FIL	= philo \
			philo_init philo_time philo_life philo_forks \
			utils validator \
			error_handler

INCS	= $(addprefix -I, $(INC_DIR))
SRCS	= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FIL)))
OBJS	= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FIL)))

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -g
RM		= rm -rf

RED		= "\033[0;31m"
BGREEN	= "\033[1;32m"
MAG		= "\033[0;35m"
ENDCL	= "\033[0;37m"

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCS) $(SRCS) -o $(NAME)
	@echo $(BGREEN)"... philo ..."$(ENDCL)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# bonus:

clean:
	@$(RM) $(OBJ_DIR)
	@echo $(MAG)"... finished cleaning"$(ENDCL)

fclean:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@$(RM) $(NAME).dSYM
	@echo $(MAG)"... finished f-cleaning"$(ENDCL)

re: fclean all

.PHONY: all clean fclean re bonus
