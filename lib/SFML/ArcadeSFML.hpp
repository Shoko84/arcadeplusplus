/*
** ArcadeSFML.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/lib/SFML
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Mon Mar 13 13:28:22 2017 cauvin-m
** Last update Sun Apr 09 14:07:47 2017 cauvin-m
*/

#ifndef ARCADE_SFML_HPP
#define  ARCADE_SFML_HPP

# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>
# include <iostream>
# include <unordered_map>
# include <unistd.h>
# include <dirent.h>
# include "ArcadeError.hpp"
# include "AGraphicLib.hpp"

# define  CELLSIZE  (20)
# define  GET_RED(color)   ((color >> 16) & 0xFF)
# define  GET_GREEN(color) ((color >> 8) & 0xFF)
# define  GET_BLUE(color)  (color & 0xFF)
# define  GET_COLOR(color) sf::Color(GET_RED(color), GET_GREEN(color), GET_BLUE(color))

namespace arcade
{
  class ArcadeSFML : public AGraphicLib
  {
    sf::RenderWindow                                  _window;
    sf::SoundBuffer                                   _sbuffer;
    sf::Sound                                         _sound;
    sf::Music                                         _music;
    sf::Font                                          _font;
    std::map<std::string, sf::Texture>                _txList;

    std::unordered_map<std::string, sf::Music>        _musicList;

  public:
    ArcadeSFML();
    virtual ~ArcadeSFML();

    virtual void                              addSprite(std::string const& imageName, size_t const& color, std::string const& asciiImage);

    virtual int                               initWin();
    virtual int                               openWin(Pos const& gameSize);
    virtual int                               closeWin();

    virtual EventKeyBoard                     getEvent();
    virtual int                               clearWin();
    virtual int                               refreshWin();

    virtual int                               p_backGround(std::string const& image);
    virtual int                               p_cell(Pos const& pos, std::string const& image, int const way);
    virtual int                               p_hLine(Pos const& pos, int const length, std::string const& image, int const way);
    virtual int                               p_vLine(Pos const& pos, int const length, std::string const& image, int const way);
    virtual int                               p_text(Pos const& pos, std::string const& str, size_t const color, int const size);
    virtual int                               p_sound(std::string const& soundName, SoundType const& soundType);
  };
}

#endif /* ARCADE_SFML_HPP */
