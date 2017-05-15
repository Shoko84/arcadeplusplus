/*
** GuitarHero.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/games/GuitarHero
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Mon Apr 03 13:47:03 2017 cauvin-m
** Last update Sun Apr 09 23:03:51 2017 cauvin-m
*/

#ifndef GUITARHERO_HPP
#define  GUITARHERO_HPP

# include <iostream>
# include <fstream>
# include <dirent.h>
# include <map>
# include <ctime>
# include "AGame.hpp"
# include "ArcadeError.hpp"

namespace arcade
{
  enum class SelectType : int
  {
    MAPSELECT = 0,
    MAPPLAY = 1
  };

  class GuitarHero : public AGame
  {
    int                                         _keys[4];
    size_t                                      _turns;
    std::map<int, std::string>                  _assetsUnpressed;
    std::map<int, std::string>                  _assetsPressed;
    std::map<std::string, std::vector<Pos>>     _fallingNotes;
    std::string                                 _currentMap;
    size_t                                      _combo;
    Score                                       _highScore;
    SelectType                                  _stateType;
    std::clock_t                                _clkFade;
    bool                                        _fade;
    int                                         _mapIdxSelected;
    IGraphicLib                                 *_graphicLib;

  public:
    GuitarHero();
    virtual ~GuitarHero();

    virtual int         initGame(IGraphicLib *graphicLib, Score const& highScore);

    virtual int         play();
    virtual int         actionOfEvent(EventKeyBoard const& event);
    virtual int         display(IGraphicLib *graphicLib);

    void                loadGuitarHeroMaps();
    void                createNote(IGraphicLib *graphicLib, Pos const& pos, Pos const& size, std::string const& asset) const;
    bool                hitNotes(int const& keyIdx, int const& noteIdx);
    bool                hasOnlyDigits(std::string const& str) const;
  };
}

#endif
