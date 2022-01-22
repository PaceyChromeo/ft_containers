NAME_STD	= std_vector

NAME_FT	= ft_vector

CC		= clang++

FLAGS += -g -fsanitize=address

CFLAGS	= -Wall -Werror -Wextra -std=c++98

SRCS	= main.cpp
		 
OBJS	= $(SRCS:.cpp=.o)

%.o:%.cpp
	$(CC) $(CFLAGS) $(NAMSPC) -c $< -o $@

$(NAME_STD) : NAMSPC= -D NAMESPACE=std
$(NAME_FT) : NAMSPC= -D NAMESPACE=ft

all:	$(NAME_FT)

$(NAME_FT):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME_FT) $(OBJS)

std: clean $(NAME_STD)
$(NAME_STD):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME_STD) $(OBJS)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME_FT)
			rm -f $(NAME_STD)

re:			fclean all

.PHONY:		all clean fclean re

