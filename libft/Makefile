CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

AR		= ar rc
RM		= /bin/rm -rf

NAME	= libft.a
SRCDIR = src
OBJDIR = build
SRCS	= 	ft_isascii.c ft_isprint.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
			ft_tolower.c ft_toupper.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
			ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
			ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_free.c\
			ft_memchr.c ft_memcmp.c ft_strdup.c ft_calloc.c  ft_strcmp.c\
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_split.c ft_strmapi.c ft_striteri.c \
			ft_putstr_limit_fd.c ft_putchar_times_fd.c ft_strndup.c \
			ft_isspace.c ft_countchr.c ft_min_nbr.c ft_max_nbr.c\
			ft_lst_1.c ft_lst_2.c \
			ft_deque_1.c ft_deque_2.c \
			ft_printf.c ft_printf_aux.c ft_printf_csp.c \
			ft_printf_nbr.c ft_printf_ntoa.c ft_printf_ptr.c ft_printf_str.c \
			ft_printf_utils.c \
			get_next_line.c ft_strjoin_realloc.c ft_str_realloc.c \
			ft_dict_is1.c ft_dict_is2.c
SRCS := $(SRCS:%=$(SRCDIR)/%)

#OBJS	= $(SRCS:.c=.o)
# $(patsubst search_pattern, replace_pattern, text)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))


all:		$(NAME)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
			@mkdir -p $(OBJDIR)

clean:
			$(RM) $(OBJDIR)


fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re