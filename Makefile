NAME	= Cub3D
LIBFT	= libft/libft.a
MLX		= minilibx/libmlx.a
SRC		= main.c parse_cub.c read_map.c sprite.c sprite_utils.c window.c window_utils.c \
			raycasting.c event.c fct.c bonus.c bonus_2.c
OBJ_DIR	= objs/
OBJ		= ${addprefix ${OBJ_DIR}, ${SRC:.c=.o}}
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

${OBJ_DIR}%.o:	srcs/%.c
			${CC} -g ${CFLAGS} -I includes/ -c $< -o $@

${NAME}:	${OBJ_DIR} ${OBJ} ${LIBFT} ${MLX}
			${CC} ${CFLAGS} -o $@ ${OBJ} ${LIBFT} ${MLX} -lXext -lX11 -lm

${OBJ_DIR}:
			mkdir -p ${OBJ_DIR}

${LIBFT}:	
			${MAKE} bonus -C libft

${MLX}:
			${MAKE} -C minilibx

all:		${NAME}

clean:
			rm -rf ${OBJ_DIR}
			${MAKE} clean -C libft
			${MAKE} clean -C minilibx

fclean:		clean
			rm -rf ${NAME}
			${MAKE} fclean -C libft

re: 		fclean all

.PHONY: 	all clean fclean re
