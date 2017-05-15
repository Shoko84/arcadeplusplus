/*
** MapEditorSolarfox.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/games/MapEditorSolarfox
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Tue Apr 04 19:36:55 2017 cauvin-m
** Last update Sat Apr 08 23:45:09 2017 cauvin-m
*/

#ifndef MAPEDITOR_SOLARFOX_HPP
#define  MAPEDITOR_SOLARFOX_HPP

# include <fstream>
# include <vector>
# include <map>
# include "AGame.hpp"

namespace arcade
{
  enum class SelectType : int
  {
    MAPEDIT = 0,
    SIZEEDIT = 1,
    LEVELEDIT = 2
  };

  class MapEditorSolarfox : public AGame
  {
    std::map<int, std::string>                  _assetsList;
    std::vector<std::vector<int>>               _map;
    Pos                                         _mapSize;
    size_t                                      _level;
    Pos                                         _cursorPos;
    std::map<EventKeyBoard, bool>               _keysPressed;
    SelectType                                  _type;

  public:
    MapEditorSolarfox();
    virtual ~MapEditorSolarfox();

    virtual int         initGame(IGraphicLib *graphicLib, Score const& highScore);

    virtual int         play();
    virtual int         actionOfEvent(EventKeyBoard const& event);
    virtual int         display(IGraphicLib *graphicLib);

    void                mapEditEvents();
    void                sizeEditEvents();
    void                levelEditEvents();

    void                createCell(IGraphicLib *graphicLib, Pos const& pos, Pos const& size, std::string const& asset) const;
    bool                fileExist(std::string const& filepath) const;
    bool                mapIsEmpty() const;
    void                resetKeysPressed();
  };
}

#endif
