SRCS	= ft_printf.c

OBJS	= ${SRCS:.c=.o}

NAME	= libftprintf.a

RM		= rm -f

CC		= cc

AR		= ar rcs

ARB		= ar qs

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

test:		${CC} ${CFLAGS} printf.out -L. -lftprintf

.PHONY:		all clean fclean re test