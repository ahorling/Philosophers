# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ahorling <ahorling@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/05/10 22:10:10 by ahorling      #+#    #+#                  #
#    Updated: 2023/05/16 22:40:30 by ahorling      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

############## COLOUR CODES ##########

BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

############## CONSTANTS #############

NAME := philo
CC := gcc
CFLAGS := -Wall -Wextra -Werror -pthread #-g -fsanitize=thread

############### SOURCES ##############

SOURCES 	:=	main.c \
				eating.c \
				frees.c \
				init_philos.c \
				locked_functions.c \
				paramedic.c \
				parsing.c \
				philo_utils.c \
				philos.c \
				utils/ft_atoi.c \
				utils/ft_strlen.c\
				utils/ft_strncmp.c 

INCLUDES	:=	-I include \
				-I include/utils 
				
SOURCE_DIR 	:=	src
OBJECT_DIR	:=	objects
OBJECTS 	:= 	$(addprefix $(OBJECT_DIR)/, $(SOURCES:.c=.o))

############### MESSAGES ########

MESSAGE		:=	"Making $(NAME)"
MESSAGE_FIN	:=	"COMPILATION COMPLETE"
MESSAGE_RM	:=	"OBJECTS CLEANED"
MESSAGE_FRM	:=	"EVERYTHING CLEANED"
MESSAGE_LIB	:=	"LIBRARIES READY"

############### RUNNING ##############

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^
	@echo "$(GREEN)$(BOLD)$(MESSAGE_FIN)$(RESET)"

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

run:
	make && ./$(NAME)

clean:
	@rm -f $(OBJECTS)
	@echo "$(RED)$(MESSAGE_RM)$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@if [ -d "$(OBJECT_DIR)" ]; then rm -rf $(OBJECT_DIR); fi
	@echo "$(RED)$(MESSAGE_FRM)$(RESET)"

re: fclean all

.PHONY: all clean fclean re libraries