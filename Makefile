NAME		=	minishell

SRC_DIR		=	srcs/

OBJ_DIR     =   objs/


SRCS		=	builtin/builtin.c
SRCS		+=	builtin/cd.c
SRCS		+=	builtin/echo.c
SRCS		+=	builtin/env.c
SRCS		+=	builtin/exit.c
SRCS		+=	builtin/export.c
SRCS		+=	builtin/export_utils.c
SRCS		+=	builtin/pwd.c
SRCS		+=	builtin/unset.c

SRCS		+=	env/env.c
SRCS		+=	env/env_utils.c

SRCS		+=	close/close.c

SRCS		+=	exec/exec.c
SRCS		+=	exec/cmd_process.c
SRCS		+=	exec/exec_utils.c
SRCS		+=	exec/exec_utils2.c
SRCS		+=	exec/exec_utils3.c
SRCS		+=	exec/find_path_cmd.c
SRCS		+=	exec/init_exec.c
SRCS		+=	exec/redir.c
SRCS		+=	exec/pipe_process.c
SRCS		+=	exec/main_exec.c
SRCS		+=	exec/main_exec_utils.c
SRCS		+=	exec/free_exec.c
SRCS		+=	exec/fork_utils.c
SRCS		+=	exec/heredoc.c
SRCS		+=	exec/wait.c
SRCS		+=	exec/subshell.c

SRCS		+=	signal/signal.c
SRCS		+=	signal/signal_utils.c

SRCS		+= lexing/lexer.c
SRCS		+= lexing/lexer_utils.c
SRCS		+= lexing/lexer_utils2.c
SRCS		+= lexing/lexer_validate.c
SRCS		+= lexing/lexer_stradd.c
SRCS		+= lexing/lexer_int2str.c

SRCS		+= parsing/parsing.c
SRCS		+= parsing/parsing_init.c
SRCS		+= parsing/parsing_utils.c
SRCS		+= parsing/parsing_utils2.c
SRCS		+= parsing/parsing_print.c
SRCS		+= parsing/parsing_print2.c

SRCS		+= stack/stack.c
SRCS		+= stack/stack_utils.c

SRCS		+= queue/queue.c
SRCS		+= queue/queue_utils.c

SRCS		+= print_logo.c
SRCS		+= main.c

SRCS 		+= wildcard/wildcard.c
SRCS 		+= wildcard/wildcard_utils.c

vpath %.c $(SRC_DIR)

OBJS		=	$(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

CC			=	cc
CFLAGS		=	-g3 -Wall -Wextra -Werror
LIBFT 		= 	libft/libft.a
INCLUDES 	= 	-I includes/ -I libft/includes/
LIBS		=   -L libft -lft -lreadline
RM			=	rm -f

GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
END=\033[0m
BOLD_START=\e[1m
BOLD_END=\e[0m

ifeq ($(debug), true)
	CFLAGS += -g3 -fsanitize=address,undefined
endif

define PRINT_LOADING
	@printf "$(GREEN)Compiling libft["
	@for i in $(shell seq 0 10 100); do \
		printf "▓"; \
		sleep 0.1; \
	done
	@printf "] 100%%$(RESET)\n$(END)"
endef

all: 			$(LIBFT) ${NAME}
				@echo "$(GREEN)$(BOLD_START)${NAME} created$(BOLD_END)$(END)"

bonus: 			$(LIBFT) ${NAME_BONUS}
				@echo "$(GREEN)$(BOLD_START)${NAME_BONUS} created$(BOLD_END)$(END)"

$(LIBFT):
				@$(PRINT_LOADING)
				$(MAKE) --no-print-directory -C libft/

${NAME_BONUS}: 	${OBJS} $(OBJS_BONUS)
				$(CC) $(CFLAGS) ${OBJS} $(OBJS_BONUS) $(LIBS) -o $(NAME_BONUS)

${NAME}: 		${OBJS}
				$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)%.o: %.c
				@echo "$(BLUE)Compiling: $@ $(END)"
				mkdir -p $(OBJ_DIR) $(OBJ_DIR)builtin/ $(OBJ_DIR)env/ $(OBJ_DIR)exec/ $(OBJ_DIR)lexing/ $(OBJ_DIR)parsing/ $(OBJ_DIR)close/ $(OBJ_DIR)stack/ $(OBJ_DIR)queue/ $(OBJ_DIR)signal/ $(OBJ_DIR)wildcard/
				$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
				$(RM) -r $(OBJ_DIR)
				${RM} ${OBJS} ${BOBJS}
				@echo "$(RED)Clean libft$(END)"
				$(MAKE) --no-print-directory clean -C ./libft/
				@echo "$(GREEN)$(BOLD_START)Clean done$(BOLD_END)$(END)"

fclean: clean
				${RM} ${NAME} ${NAME_BONUS}
				@echo "$(RED)Fclean libft$(END)"
				$(MAKE) --no-print-directory fclean -C ./libft/
				@echo "$(GREEN)$(BOLD_START)Fclean done$(BOLD_END)$(END)"

re: fclean all

.PHONY: all clean fclean re bonus libft
.SILENT:
