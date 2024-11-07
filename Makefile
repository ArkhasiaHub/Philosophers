NAME = philo

CC = cc

FLAGS = -Wall -Wextra -Werror -MMD -MP -I includes -g -pthread -fsanitize=thread

SRCS = ./srcs/ft_atol.c \
./srcs/ft_calloc.c \
./srcs/ft_strlen.c \
./srcs/getters.c \
./srcs/parse_input.c \
./srcs/philosophers.c \
./srcs/setters.c \
./srcs/utils.c \
./srcs/init.c \
./srcs/dinner.c \
./srcs/ft_isdigit.c \
./srcs/ft_bzero.c \
./srcs/wait_all_threads.c \
./srcs/check_philo.c \
./srcs/one_philosopher.c \
./srcs/eating.c

all:	${NAME}

OBJ = ${SRCS:.c=.o}

OBJ_D = ${OBJ:.o=.d}

%.o : %.c
		$(CC) $(FLAGS) -c $< -o $@

-include ${OBJ_D}

${NAME} : ${OBJ}
		${CC} ${FLAGS} ${OBJ} -o ${NAME}

clean:
		rm -f ${OBJ} ${OBJ_D}

fclean: clean
		rm -f ${NAME}

re: fclean all

.PHONY: clean fclean re all
