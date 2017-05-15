/*
** ArcadeLibcaca.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/lib/ArcadeLibcaca
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Sun Mar 19 01:16:23 2017 cauvin-m
** Last update Tue Apr 04 18:12:47 2017 cauvin-m
*/

#ifndef ARCADE_LIBCACA_HPP
#define  ARCADE_LIBCACA_HPP

# include <iostream>
# include <iomanip>
# include <cmath>
# include <caca.h>
# include "AGraphicLib.hpp"

# define  CELLSIZEX (2)
# define  CELLSIZEY (1)

namespace arcade
{
  class ArcadeLibcaca : public AGraphicLib
  {
    caca_display_t                            *_window;
    caca_canvas_t                             *_canvas;

  public:
    ArcadeLibcaca();
    virtual ~ArcadeLibcaca();

    virtual int                               initWin();
    virtual int                               openWin(Pos const& pos);
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

    virtual uint32_t                          convertU64ToU32(size_t color);
  };
}

#endif /* ARCADE_LIBCACA_HPP */
