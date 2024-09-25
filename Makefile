NAME		= minishell
LIBFT_DIR	= libft/
LIBFT		= ${LIBFT_DIR}libft.a
SRC			= main.c utils.c free.c \
			  lexer.c \
			  parser.c parser_utils.c \
			  syntax_checker.c \
			  expander.c expander_utils.c\
			  executor.c executor_utils.c\
			  child.c \
			  path.c \
			  redirect.c redirect_utils.c \
			  builtins.c echo.c cd.c pwd.c export.c unset.c env.c exit.c \
			  export_utils.c
OBJ_DIR		= objects/
OBJ			= ${addprefix ${OBJ_DIR}, ${SRC:%.c=%.o}}
VPATH		= sources sources/builtin
INCLUDES	= headers/ ${LIBFT_DIR}
INCLUDES	:= ${addprefix -I, ${INCLUDES}}
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
RLFLAGS		= -lreadline
RM			= rm -rf

DEFAULT = \033[0;39m
GREEN = \033[0;92m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m

all: ${NAME}

$(NAME): ${LIBFT} ${OBJ_DIR} ${OBJ}
	${CC} ${CFLAGS} ${OBJ} ${INCLUDES} ${LIBFT} ${RLFLAGS} -o ${NAME}
	@echo "$(GREEN)Minishell compiled :3$(MAGENTA) UwU!$(DEFAULT)"

clean:
	make clean -C ${LIBFT_DIR}
	${RM} ${OBJ_DIR}
	@echo "$(BLUE)Minishell objects awe cweean UwU!$(DEFAULT)"

fclean: clean
	make fclean -C ${LIBFT_DIR}
	${RM} ${NAME}
	@echo "$(CYAN)Minishell executor is cweean!$(DEFAULT)"

re: fclean all
	@echo "$(GREEN)I cweeaned and rebuilt evewithing for u daddy UwU!$(DEFAULT)"

${LIBFT}:
	make -C ${LIBFT_DIR}

${OBJ_DIR}:
	mkdir -p ${OBJ_DIR}

${OBJ_DIR}%.o: %.c
	${CC} -c ${CFLAGS} ${INCLUDES} $< -o $@

.PHONY: all clean fclean re
.SILENT: