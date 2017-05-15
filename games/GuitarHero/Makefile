##
## Makefile for Rendu in /home/cauvin_m/Rendu/cpp_arcade/games/DDR
##
## Made by cauvin-m
## Login   <cauvin_m@epitech.net>
##
## Started on  Mon Apr 03 13:44:53 2017 cauvin-m
## Last update Thu Apr  6 19:57:10 2017 Maxime Cauvin
##

NAME    =     lib_arcade_guitarhero.so

CC      =    	g++ -shared

RM      =  		rm -f

CPPFLAGS  =   -W -Wall -Wextra -Werror -fPIC -std=c++14

CPPFLAGS +=		-I ./																\
							-I ../../Interfaces/IGraphicLib			\
							-I ../../Objects/AGraphicLib/ 			\
							-I ../../Interfaces/IGame						\
							-I ../../Objects/AGame							\
							-I ../../Objects/ArcadeError				\

SRC =			./GuitarHero.cpp

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
