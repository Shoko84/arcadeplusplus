##
## Makefile for Rendu in /home/cauvin_m/Rendu/cpp_arcade/games/Qix
##
## Made by cauvin-m
## Login   <cauvin_m@epitech.net>
##
## Started on  Wed Apr 05 11:37:25 2017 cauvin-m
## Last update Wed Apr 05 11:37:25 2017 cauvin-m
##

NAME    =     lib_arcade_qix.so

CC      =    	g++ -shared

RM      =  		rm -f

CPPFLAGS  =   -W -Wall -Wextra -Werror -fPIC -std=c++14

CPPFLAGS +=		-I ./												\
							-I ../../Interfaces/IGraphicLib			\
							-I ../../Objects/AGraphicLib/ 			\
							-I ../../Interfaces/IGame				\
							-I ../../Objects/AGame					\
							-I ../Protocol/

SRC =			./Qix.cpp \
				../Protocol/AProtocol.cpp

OBJ = 		$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
