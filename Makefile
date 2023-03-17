.PHONY:     			all $(NAME) mkbuild lib clean fclean re sanitize

NAME					= minishell

BUILD_DIR				= build/
	
HEADER_DIR				= header/
HEADER_FILE				= minishell.h

DIR						= src/
SRC			 			= main.c \
						  parsing/parsing.c \
						  parsing/input_operator_error.c \
						  parsing/split_line.c \
						  parsing/get_cmd.c \
						  parsing/get_file.c \
						  parsing/get_flag.c \
						  parsing/get_content.c \
						  parsing/get_utils.c \
						  parsing/list_utils.c \
						  parsing/convert_3d_array.c \
							
OBJECTS			    	= $(SRC:%.c=$(BUILD_DIR)%.o)
	
LIBFT					= libft.a
LIB_DIR					= libft/

	
GCC						= gcc
CFLAGS					= -Wall -Wextra -g3 #-Werror
LDLIBS					= -lreadline #-L/opt/homebrew/Cellar/readline/8.2.1/lib -I/opt/homebrew/Cellar/readline/8.2.1/include
SANITIZE				= $(CFLAGS) -fsanitize=address

RM 						= rm -rf

$(BUILD_DIR)%.o:		$(DIR)%.c $(HEADER_DIR)/$(HEADER_FILE) Makefile
						@mkdir -p $(@D)
						$(GCC) $(CFLAGS) -I$(HEADER_DIR) -I$(LIB_DIR) -c $< -o $@

all: 					mkbuild lib $(HEADER_DIR) $(NAME) 
						
mkbuild:
						@mkdir -p build
						
$(NAME): 				$(OBJECTS) $(LIB_DIR)$(LIBFT)
						$(GCC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LIB_DIR)$(LIBFT) $(LDLIBS)

sanitize :				$(OBJECTS) $(LIB_DIR)$(LIBFT)
						$(GCC) $(SANITIZE) $(OBJECTS) -o $(NAME) $(LIB_DIR)$(LIBFT)

lib:
						@make -C $(LIB_DIR)
					
clean:					
						@${RM} $(OBJECTS)
						@make clean -C $(LIB_DIR)
						@${RM} $(BUILD_DIR)

fclean:					clean
						@${RM} ${NAME}
						@make fclean -C $(LIB_DIR)

re:						fclean all
						$(MAKE) all
