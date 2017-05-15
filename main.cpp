/*
** main.cpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Mon Mar 13 10:41:44 2017 cauvin-m
** Last update Sun Mar 19 16:20:55 2017 cauvin-m
*/

#include "Arcade.hpp"

int main(int ac, char **av)
{
  if (ac != 2)
  {
    std::cerr << av[0] << ": Invalid arguments number." << std::endl << "Usage: " << av[0] << " [path_to_graphic_library.so]" << std::endl;
    return (-1);
  }
  arcade::Arcade  game(av[1]);
  game.mainLoop();
  return (0);
}
