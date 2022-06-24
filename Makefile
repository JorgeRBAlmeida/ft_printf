SRCS	= ft_printf.c ft_printf_utils.c ft_printf_utils2.c

OBJS	= ${SRCS:.c=.o}

NAME	= libftprintf.a

RM		= rm -f

CC		= cc

AR		= ar rcs

CFLAGS	= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS} ${OBJB}
			${AR} ${NAME} ${OBJS} ${OBJB}

all:		$(NAME)

clean:
			${RM} ${OBJS} ${OBJB}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re