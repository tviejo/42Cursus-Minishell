NAME = libft.a
LIB = $(NAME)

### SRCS #######################################################################

PATH_SRCS = ./

SRCS += ft_isalpha.c
SRCS += ft_isdigit.c
SRCS += ft_isalnum.c
SRCS += ft_isascii.c
SRCS += ft_isprint.c
SRCS += ft_strlen.c
SRCS += ft_memset.c
SRCS += ft_bzero.c
SRCS += ft_memcpy.c
SRCS += ft_memmove.c
SRCS += ft_strlcpy.c
SRCS += ft_strlcat.c
SRCS += ft_toupper.c
SRCS += ft_tolower.c
SRCS += ft_strchr.c
SRCS += ft_strrchr.c
SRCS += ft_strncmp.c
SRCS += ft_memchr.c
SRCS += ft_memcmp.c
SRCS += ft_strnstr.c
SRCS += ft_atoi.c
SRCS += ft_calloc.c
SRCS += ft_strdup.c

SRCS += ft_substr.c
SRCS += ft_strjoin.c
SRCS += ft_strtrim.c
SRCS += ft_split.c
SRCS += ft_itoa.c
SRCS += ft_strmapi.c
SRCS += ft_striteri.c
SRCS += ft_putchar_fd.c
SRCS += ft_putstr_fd.c
SRCS += ft_putendl_fd.c
SRCS += ft_putnbr_fd.c

BONUS_SRCS += ft_lstnew_bonus.c
BONUS_SRCS += ft_lstadd_front_bonus.c
BONUS_SRCS += ft_lstsize_bonus.c
BONUS_SRCS += ft_lstlast_bonus.c
BONUS_SRCS += ft_lstadd_back_bonus.c
BONUS_SRCS += ft_lstdelone_bonus.c
BONUS_SRCS += ft_lstclear_bonus.c
BONUS_SRCS += ft_lstiter_bonus.c
BONUS_SRCS += ft_lstmap_bonus.c

BONUS_SRCS += ft_split_seps.c
BONUS_SRCS += get_next_line_bonus.c
BONUS_SRCS += get_next_line_utils_bonus.c

vpath %.c $(PATH_SRCS)

### OBJS #######################################################################

OBJS := $(SRCS:.c=.o)
BONUS_OBJS := $(BONUS_SRCS:.c=.o)

### INCLUDES ###################################################################

HEADER = -I ./

### COMPILATION ################################################################

CC = cc
CFLAGS += -Werror
CFLAGS += -Wall
CFLAGS += -Wextra

### RULE ######################################################################

all: $(LIB)

$(NAME): bonus
#	$(AR) -rcs $(LIB) $(OBJS)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)

$(BONUS_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)

bonus: $(OBJS) $(BONUS_OBJS)
	$(AR) -rcs $(LIB) $(OBJS) $(BONUS_OBJS)

clean:
	$(RM) -r *.o
	
fclean: clean
	$(RM) $(LIB)
	
re: fclean
	$(MAKE)

.PHONY: clean fclean re all bonus
