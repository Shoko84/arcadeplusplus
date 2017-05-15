##
## Makefile for Rendu in /home/cauvin_m/Rendu/cpp_arcade/games/Solarfox
##
## Made by cauvin-m
## Login   <cauvin_m@epitech.net>
##
## Started on  Sun Apr 02 02:22:54 2017 cauvin-m
## Last update Sun Apr 02 02:22:54 2017 cauvin-m
##

NAME    =     lib_arcade_solarfox.so

CC      =    	g++ -shared

RM      =  		rm -f

CPPFLAGS  =   -W -Wall -Wextra -Werror -fPIC -std=c++14

CPPFLAGS +=		-I ./												\
							-I ../../Interfaces/IGraphicLib			\
							-I ../../Objects/AGraphicLib 			\
							-I ../../Interfaces/IGame				\
							-I ../../Objects/AGame					\
							-I ../Protocol/	\
							-I ../../Objects/ArcadeError	\

SRC =			./Solarfox.cpp \
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
