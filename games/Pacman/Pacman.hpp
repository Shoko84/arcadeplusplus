/*
** Pacman.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/games/Pacman
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Mon Mar 27 11:51:40 2017 cauvin-m
** Last update Tue Apr 04 20:46:54 2017 cauvin-m
*/

#ifndef PACMAN_HPP_
#define  PACMAN_HPP_

# include <map>
# include <fstream>
# include <iostream>
# include <dirent.h>
# include <cmath>
# include "AProtocol.hpp"

namespace arcade
{
  class Pacman : public AProtocol
  {
  private:
    int                                                 _turns;
    int                                                 _level;
    size_t                                              _score;
    std::map<int, std::map<int, std::map<int, int>>>    _map;
    std::map<int, std::map<int, int>>                   _curMap;
    std::map<int, int>                                  _pacgumsList;
    int                                                 _curPacgums;
    std::vector<Pos>                                    _dir;
    Pos                                                 _pos;

  public:
    Pacman();
    virtual ~Pacman();

    /*
     * IGame functions
     */

    virtual int         initGame(IGraphicLib *graphicLib, Score const& highScore);
    virtual int         play();
    virtual int         actionOfEvent(EventKeyBoard const& event);
    virtual int         display(IGraphicLib *graphicLib);


    /*
     * Protocol functions
     */
    virtual void 		setDirectionPlayer(arcade::AProtocol::MoveDirection move);
    virtual struct GetMap 	*getMap();
    virtual struct WhereAmI 	*getPlayer();
    virtual void		shoot() {}
    virtual void		playProtocol();

    /*
     * Pacman functions
     */

    void	loadMaps();

  };
}

#endif
