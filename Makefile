NAME			= cub3d
CC				= cc
FLAGS			= -Wall -Wextra -fsanitize=address #-Werror 
MLXFLAGS		= minilibx-linux/libmlx.a -lXext -lX11 -lm
MINILIBX_PATH	= minilibx-linux/
MINILIBX		= $(MINILIBX_PATH)/libmlx.a
SRC				= srcs/2drays.c srcs/init.c srcs/main.c srcs/moves.c srcs/parsing_map.c srcs/renders.c srcs/rays.c srcs/hooks.c \
				srcs/parsing/parse_map_file.c srcs/parsing/parse_rgb_values.c \
				srcs/utils/utils1.c srcs/utils/utils2.c srcs/utils/utils3.c srcs/utils/ft_utils.c srcs/utils/ft_utils2.c srcs/utils/ft_split.c \
				srcs/utils/get_next_line.c srcs/utils/debug.c srcs/utils/leave.c

OBJ_DIR			= objs
OBJ				= $(SRC:srcs/%.c=$(OBJ_DIR)/%.o)

CLR_RMV		= \033[0m
RED		    = \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
CLEARBLUE	= \033[1;94m
CYAN 		= \033[1;36m
PURPLE		= \033[1;35m
WHITE 		= \033[1;37m
BLACK 		= \033[1;30m
GREY 		= \033[0;37m

all: ${MINILIBX} ${NAME}

${MINILIBX}:
	@make -C ${MINILIBX_PATH}

${NAME}: $(OBJ)
	clear
	@$(CC) $(FLAGS) $(OBJ) $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)Compiled ${CLR_RMV}${CYAN}$(NAME)${CLR_RMV}$(GREEN) with sucess ${CLR_RMV} "

$(OBJ_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $^ -o $@ 

clean:	
	@rm -rf $(OBJ) objs
	@echo "$(RED)Deleting $(PURPLE)-> $(YELLOW)$(NAME) $(CLR_RMV)$(RED)[objs]$(GREEN) ${CLR_RMV}"

fclean: clean
	@rm -rf $(NAME) $(OBJ)

re: fclean all

run: re
	@./cub3d maps/good/42.cub

norm:
	clear && norminette srcs && norminette cubed.h

.PHONY: all clean fclean re run norm
