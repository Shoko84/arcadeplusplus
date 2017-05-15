##
## Makefile for Rendu in /home/cauvin_m/Rendu/cpp_arcade
##
## Made by cauvin-m
## Login   <cauvin_m@epitech.net>
##
## Started on  Mon Mar 13 10:28:22 2017 cauvin-m
## Last update Mon May 15 02:20:28 2017 Maxime Cauvin
##

NAME    		=     arcade

CC      		=    	g++

RM      		=  		rm -f

CPPFLAGS  	=   	-W -Wall -Wextra -Werror -std=c++14 -fPIC												\

CPPFLAGS    +=  	-I ./Objects/Arcade 																						\
									-I ./Objects/AGame																							\
									-I ./Objects/AGraphicLib																				\
									-I ./Objects/DLLoader																						\
									-I ./Objects/ArcadeError																				\

CPPFLAGS		+=		-I ./Interfaces/IGame																						\
									-I ./Interfaces/IGraphicLib																			\

SRC					= 		./main.cpp																											\

SRC					+=		./Objects/Arcade/Arcade.cpp																			\

OBJ     		= 		$(SRC:.cpp=.o)

LDFLAGS			=			-Wl,-rpath=./lib/SFML/Dependencies/SFML-2.4.2/lib							\
									-Wl,-rpath=./lib/Libcaca/Dependencies/libcaca-0.99.beta19/lib		\
									-Wl,-rpath=./lib/GLUT/Dependencies/GLUT/lib											\
									-L./lib/SFML/Dependencies/SFML-2.4.2/lib												\
									-L./lib/Libcaca/Dependencies/libcaca-0.99.beta19/lib						\
									-L./lib/GLUT/Dependencies/GLUT/lib															\
									-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 				\
									-lcaca																													\
									-lglut																													\

all: $(NAME)

$(NAME): $(OBJ) lib_games lib_graph
	$(CC) $(OBJ) -ldl -o $(NAME) $(LDFLAGS)
	@printf "\033[0;32mArcade compiled successfully !\n\033[0m"

lib_games:
	@printf "\033[0;32mBuilding games libs..\n\033[0m"
	make -C	./games

lib_graph:
	@printf "\033[0;32mBuilding graphic libs..\n\033[0m"
	make -C	./lib

clean:
	$(RM) $(OBJ)
	make clean -C ./lib
	make clean -C ./games

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./lib
	make fclean -C ./games

re: fclean all

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
