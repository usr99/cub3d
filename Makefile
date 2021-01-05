NAME		= Cub3D
LIBFT		= libft/libft.a
MLX			= minilibx/libmlx.a
INC			= ./includes
SRC			= main.c parse_cub.c read_map.c sprite.c sprite_utils.c window.c window_utils.c \
				raycasting.c event.c fct.c
BONUS		= main_bonus.c parse_cub_bonus.c read_map_bonus.c sprite_bonus.c sprite_utils_bonus.c window_bonus.c window_utils_bonus.c \
				raycasting_bonus.c event_bonus.c fct_bonus.c bonus.c bonus_2.c
OBJ_DIR		= objs/
OBJ			= ${addprefix ${OBJ_DIR}, ${SRC:.c=.o}}
OBJ_BONUS	= ${addprefix ${OBJ_DIR}, ${BONUS:.c=.o}}
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

${OBJ_DIR}%.o:	srcs/%.c
			${CC} -g ${CFLAGS} -I ${INC} -c $< -o $@

${OBJ_DIR}%.o:	bonus/%.c
			${CC} -g ${CFLAGS} -I ${INC} -c $< -o $@

${NAME}:	${OBJ_DIR} ${OBJ} ${LIBFT} ${MLX} ${INC}
			${CC} ${CFLAGS} -o $@ ${OBJ} ${LIBFT} ${MLX} -lXext -lX11 -lm

${OBJ_DIR}:
			mkdir -p ${OBJ_DIR}

${LIBFT}:	
			${MAKE} bonus -C libft

${MLX}:
			${MAKE} -C minilibx

all:		${NAME}

bonus:		${OBJ_DIR} ${OBJ_BONUS} ${LIBFT} ${MLX} ${INC}
			${CC} ${CFLAGS} -o ${NAME} ${OBJ_BONUS} ${LIBFT} ${MLX} -lXext -lX11 -lm

clean:
			rm -rf ${OBJ_DIR}
			${MAKE} clean -C libft
			${MAKE} clean -C minilibx

fclean:		clean
			rm -rf ${NAME}
			${MAKE} fclean -C libft

re: 		fclean all

.PHONY: 	all clean fclean re
