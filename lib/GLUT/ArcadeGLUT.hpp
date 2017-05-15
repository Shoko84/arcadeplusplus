/*
** ArcadeGLUT.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/lib/GLUT
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Fri Mar 24 10:06:42 2017 cauvin-m
** Last update Tue Apr 04 18:20:09 2017 cauvin-m
*/

#ifndef ARCADE_GLUT_HPP
#define  ARCADE_GLUT_HPP

# include <iostream>
# include <iomanip>
# include <cmath>
# include <GL/freeglut.h>
# include "AGraphicLib.hpp"

# define  CELLSIZE  (15.0f)
# define  GET_RED(color)   ((color >> 16) & 0xFF)
# define  GET_GREEN(color) ((color >> 8) & 0xFF)
# define  GET_BLUE(color)  (color & 0xFF)

namespace arcade
{
  class ArcadeGLUT : public AGraphicLib
  {
    int                                       _window;
    EventKeyBoard                             _key;

  public:
    ArcadeGLUT();
    virtual ~ArcadeGLUT();

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

    virtual Pos                               getTransformPosition(Pos const& pos);
  };
}

#endif /* ARCADE_LIBCACA_HPP */
