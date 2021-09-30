NAME	= philo

CC		= clang
CFLAGS	= -Wall -Wextra -Werror

SRCSF	=  main.c utils.c error_manager.c prog.c

SRCSD	= srcs/
INCL	= include/

SRCS	=	$(addprefix ${SRCSD},${SRCSF}) # $(wildcard $(SRC_DIR)/*.c)
OBJS	=	${SRCS:.c=.o}


.c.o	:	${INCL}philo.h 
			${CC} ${CFLAGS} -I ${INCL} -c $< -o ${<:.c=.o}


${NAME} :	${OBJS}
			${CC} -lpthread -o ${NAME} ${OBJS}


all		:	${NAME}

clean	:
			find . -type f -name "*.o" -delete

fclean	:	clean
			find . -type f -name "*.a" -delete
			rm -rf ${NAME}

re		:	fclean all

.PHONY	:	re clean fclean