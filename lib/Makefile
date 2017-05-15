##
## Makefile for Rendu in /home/cauvin_m/Rendu/cpp_arcade/lib
##
## Made by cauvin-m
## Login   <cauvin_m@epitech.net>
##
## Started on  Mon Mar 13 13:45:47 2017 cauvin-m
## Last update Fri Mar 24 15:17:53 2017 cauvin-m
##

all: lib_arcade_sfml.so lib_arcade_libcaca.so lib_arcade_opengl.so

lib_arcade_sfml.so:
	make -C ./SFML
	mv ./SFML/lib_arcade_sfml.so .
	@printf "\033[0;32mSFML compiled successfully !\n\033[0m"

lib_arcade_libcaca.so:
	make -C ./Libcaca
	mv ./Libcaca/lib_arcade_libcaca.so .
	@printf "\033[0;32mLibcaca compiled successfully !\n\033[0m"

lib_arcade_opengl.so:
	make -C ./GLUT
	mv ./GLUT/lib_arcade_opengl.so .
	@printf "\033[0;32mOpenGL compiled successfully !\n\033[0m"

clean:
	make clean -C ./SFML
	make clean -C ./Libcaca
	make clean -C ./GLUT

fclean:
	make fclean -C ./SFML
	make fclean -C ./Libcaca
	make fclean -C ./GLUT
	$(RM) ./lib_arcade_sfml.so
	$(RM) ./lib_arcade_libcaca.so
	$(RM) ./lib_arcade_opengl.so

re: fclean all
