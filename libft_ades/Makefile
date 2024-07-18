NAME = libft_ades.a

INCS_BASE   = $(wildcard base/*.h)
INCS_PRINTF = $(wildcard printf/includes/*.h)

SRCS_BASE   = $(wildcard base/*.c)
SRCS_PRINTF = $(wildcard printf/srcs/*.c)

OBJS_BASE = $(patsubst %.c, %.o, $(SRCS_BASE))
OBJS_PRINTF = $(patsubst printf/srcs/%.c, printf/objs/%.o, $(SRCS_PRINTF))

all: $(NAME)

$(NAME): $(SRCS_BASE) $(SRCS_PRINTF) $(INCS_BASE) $(INCS_PRINTF)
		$(MAKE) -C base
		$(MAKE) -C printf
		$(AR) -rcs $(NAME) $(OBJS_BASE) $(OBJS_PRINTF)

clean:
	$(MAKE) clean -C base
	$(MAKE) clean -C printf

fclean:
	$(MAKE) fclean -C base
	$(MAKE) fclean -C printf
	$(RM) $(NAME)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re