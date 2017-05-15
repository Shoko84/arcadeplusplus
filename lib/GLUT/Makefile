	##
## Makefile for Rendu in /home/cauvin_m/Rendu/cpp_arcade/lib/Libcaca
##
## Made by cauvin-m
## Login   <cauvin_m@epitech.net>
##
## Started on  Sun Mar 19 01:14:12 2017 cauvin-m
## Last update Fri Mar 24 15:23:21 2017 cauvin-m
##

NAME    		=     lib_arcade_opengl.so

CC      		=    	g++ -shared

RM      		=  		rm -f

CPPFLAGS  	=   	-W -Wall -Wextra -Werror -fPIC -std=c++14

CPPFLAGS		+=		-I ./																				\
									-I ../../Interfaces/IGraphicLib/ 						\
									-I ../../Objects/AGraphicLib/ 							\
									-I ./Dependencies/GLUT/include 							\
									-L./Dependencies/GLUT/lib 									\
									-lglut																			\

SRC					=			./ArcadeGLUT.cpp

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
