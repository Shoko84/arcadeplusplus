##
## Makefile for Rendu in /home/cauvin_m/Rendu/cpp_arcade/lib
##
## Made by cauvin-m
## Login   <cauvin_m@epitech.net>
##
## Started on  Mon Mar 13 13:45:47 2017 cauvin-m
## Last update Sat Apr  8 17:56:34 2017 cauvin-m
##

all: lib_arcade_snake.so lib_arcade_pacman.so lib_arcade_solarfox.so lib_arcade_guitarhero.so lib_arcade_mapeditorsolarf.so lib_arcade_qix.so lib_arcade_nibbler.so lib_arcade_centipede.so

lib_arcade_snake.so:
	make -C ./Snake
	mv ./Snake/lib_arcade_snake.so .
	@printf "\033[0;32mSnake compiled successfully !\n\033[0m"

lib_arcade_pacman.so:
	make -C ./Pacman
	mv ./Pacman/lib_arcade_pacman.so .
	@printf "\033[0;32mPacman compiled successfully !\n\033[0m"

lib_arcade_solarfox.so:
	make -C ./Solarfox
	mv ./Solarfox/lib_arcade_solarfox.so .
	@printf "\033[0;32mSolarfox compiled successfully !\n\033[0m"

lib_arcade_guitarhero.so:
	make -C ./GuitarHero
	mv ./GuitarHero/lib_arcade_guitarhero.so .
	@printf "\033[0;32mGuitarHero compiled successfully !\n\033[0m"

lib_arcade_mapeditorsolarf.so:
	make -C ./MapEditorSolarfox
	mv ./MapEditorSolarfox/lib_arcade_mapeditorsolarf.so .
	@printf "\033[0;32mMapEditorSolarf compiled successfully !\n\033[0m"

lib_arcade_qix.so:
	make -C ./Qix
	mv ./Qix/lib_arcade_qix.so .
	@printf "\033[0;32mQix compiled successfully !\n\033[0m"

lib_arcade_nibbler.so:
	make -C ./Nibbler
	mv ./Nibbler/lib_arcade_nibbler.so .
	@printf "\033[0;32mNibbler compiled successfully !\n\033[0m"

lib_arcade_centipede.so:
	make -C ./Centipede
	mv ./Centipede/lib_arcade_centipede.so .
	@printf "\033[0;32mCentipede compiled successfully !\n\033[0m"

clean:
	make clean -C ./Snake
	make clean -C ./Pacman
	make clean -C ./Solarfox
	make clean -C ./GuitarHero
	make clean -C ./MapEditorSolarfox
	make clean -C ./Qix
	make clean -C ./Nibbler
	make clean -C ./Centipede

fclean:
	make fclean -C ./Snake
	make fclean -C ./Pacman
	make fclean -C ./Solarfox
	make fclean -C ./GuitarHero
	make fclean -C ./MapEditorSolarfox
	make fclean -C ./Qix
	make fclean -C ./Nibbler
	make fclean -C ./Centipede
	$(RM) ./lib_arcade_snake.so
	$(RM) ./lib_arcade_pacman.so
	$(RM) ./lib_arcade_solarfox.so
	$(RM) ./lib_arcade_guitarhero.so
	$(RM) ./lib_arcade_mapeditorsolarf.so
	$(RM) ./lib_arcade_qix.so
	$(RM) ./lib_arcade_nibbler.so
	$(RM) ./lib_arcade_centipede.so

re: fclean all
