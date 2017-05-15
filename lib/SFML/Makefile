##
## Makefile for Rendu in /home/cauvin_m/Rendu/cpp_arcade/lib/SFML
##
## Made by cauvin-m
## Login   <cauvin_m@epitech.net>
##
## Started on  Mon Mar 13 13:21:46 2017 cauvin-m
## Last update Mon Mar 13 13:21:46 2017 cauvin-m
##

NAME    		=     lib_arcade_sfml.so

CC      		=    	g++ -shared

RM      		=  		rm -f

CPPFLAGS  	=   	-W -Wall -Wextra -Werror -fPIC -std=c++14

CPPFLAGS		+=		-I ./																												\
									-I ./Dependencies/SFML-2.4.2/include 												\
									-I ../../Interfaces/IGraphicLib/ 														\
									-I ../../Objects/AGraphicLib/ 															\
									-I ../../Objects/ArcadeError/ 															\
									-L./Dependencies/SFML-2.4.2/lib 														\
									-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC					=			./ArcadeSFML.cpp

OBJ     		= 		$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CPPFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
