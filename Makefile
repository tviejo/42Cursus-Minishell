NAME = minishell
LIBFT = libft_ades/libft_ades.a
LIBS = -L libft_ades -lft_ades -lreadline

### SRCS #######################################################################

PATH_SRCS = srcs/
FOLDERS_SRCS = builtin env exec parsing

SRCS += builtin/builtin.c
SRCS += env/env.c
SRCS += exec/exec.c
SRCS += parsing/parsing.c
SRCS += parsing/parsing_utils.c

vpath %.c $(PATH_SRCS)

### OBJS #######################################################################

PATH_OBJS = objs/
DIRS_OBJS = $(patsubst %, $(PATH_OBJS)%, $(FOLDERS_SRCS))

OBJS = $(patsubst %.c, $(PATH_OBJS)%.o, $(SRCS))

### INCLUDES ###################################################################

INCLUDES_PATH = includes

INCLUDES += $(INCLUDES_PATH)/minishell.h
INCLUDES += $(INCLUDES_PATH)/mini_ade_sarr.h
INCLUDES += $(INCLUDES_PATH)/mini_tviejo.h

HEADER += -I $(INCLUDES_PATH)

### COMPILATION ################################################################

CC = cc
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror

ifeq ($(debug), true)
	CFLAGS += -fsanitize=address,undefined -g3
endif
ifeq ($(debugger), true)
	CFLAGS += -g3
endif

### RULE ######################################################################

all: $(NAME)

$(LIBFT):
	$(MAKE) -C libft_ades

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(OBJS): $(PATH_OBJS)%.o: %.c $(INCLUDES)
		mkdir -p $(DIRS_OBJS)/
		$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)

bonus: $(NAME)

clean:
	$(MAKE) clean -C libft_ades
	$(RM) -r $(PATH_OBJS)

fclean:
	$(MAKE) fclean -C libft_ades
	$(RM) -r $(PATH_OBJS)
	$(RM) $(NAME)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re bonus
