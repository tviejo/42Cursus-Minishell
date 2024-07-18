NAME = libftprintf.a
TEST = testlib.out

### SRCS #######################################################################

PATH_SRCS = srcs/
#PATH_SRCS = ./

SRCS += ft_printf.c
SRCS += ft_printf2.c
SRCS += ft_sprintf.c
SRCS += ft_sprintf2.c
SRCS += ft_atoi.c
SRCS += ft_itoa.c
SRCS += ft_ltoa.c
SRCS += ft_ultoa.c
SRCS += ft_utoa.c
SRCS += ft_parse_format_id.c
SRCS += ft_i2s_format.c
SRCS += ft_i2s_format2.c
SRCS += ft_i2s_padding.c
SRCS += ft_i2s_get_i2s_fmt.c
SRCS += ft_double2str.c
SRCS += ft_double2str_hlp.c
SRCS += ft_math.c
SRCS += ft_math_ln.c
SRCS += ft_find_next_prime.c
SRCS += ft_string.c
SRCS += ft_string2.c
SRCS += ft_string3.c

vpath %.c $(PATH_SRCS)

### OBJS #######################################################################

PATH_OBJS = objs/

OBJS = $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))

### INCLUDES ###################################################################

INCLUDES = includes/
#INCLUDES = ./

HEADER += -I $(INCLUDES)

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

$(NAME): $(OBJS)
		$(AR) -rcs $(NAME) $(OBJS)

$(OBJS): $(PATH_OBJS)/%.o: %.c
		mkdir -p $(PATH_OBJS)
		mkdir -p $(PATH_OBJS)/test
		$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)

bonus: $(NAME)

clean:
	$(RM) -r $(PATH_OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST)

re: fclean
	$(MAKE)

tests: $(NAME)
	$(CC) $(PATH_SRCS)test/*.c $(NAME) $(HEADER) -lm -o $(TEST)

.PHONY: all clean fclean re tests bonus
