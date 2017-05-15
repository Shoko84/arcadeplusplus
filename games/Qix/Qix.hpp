/*
** Qix.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/games/Qix
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Wed Apr 05 11:12:19 2017 cauvin-m
** Last update Sun Apr 09 21:39:50 2017 cauvin-m
*/

#ifndef QIX_HPP
#define  QIX_HPP

# include <map>
# include <cmath>
# include "AProtocol.hpp"

namespace arcade
{
  class Qix : public AProtocol
  {
    std::vector<std::vector<int>>     _map;
    std::map<int, std::string>        _assetsList;
    Player                            _player;
    Pos                               _qix;
    std::vector<Player>               _sparks;
    int                               _cellTravelled;
    std::map<EventKeyBoard, bool>     _keysPressed;
    std::vector<std::vector<Pos>>     _formsList;
    size_t                            _turns;
    size_t                            _level;
    size_t                            _cellsToFill;
    size_t                            _cellsFilled;
    Score                             _highScore;
    IGraphicLib                       *_graphicLib;

  public:
    Qix();
    virtual ~Qix();

    virtual int         initGame(IGraphicLib *graphicLib, Score const& highScore);

    virtual int         play();
    virtual int         actionOfEvent(EventKeyBoard const& event);
    virtual int         display(IGraphicLib *graphicLib);

    void                resetGame();
    void                resetKeysPressed();

    Pos                 movePlayer();
    void                moveQix();
    void                moveSparks();
    void                playerActions(Pos const& pos);
    bool                playerCanMove(Pos const& nextPos) const;
    bool                hasCollidedWithTrail(Pos const& pos) const;
    bool                hasCollidedWithPlayer(Player const& player, Pos const& pos) const;

    void                findForms();
    void                differentiateFormInMap(std::vector<std::vector<int>> & map, Pos const& pos, int const& id) const;
    int                 fillInForm(std::vector<std::vector<int>> const& map, int const& id);

    /*
 * Protocol functions
 */

    virtual void 		setDirectionPlayer(arcade::AProtocol::MoveDirection move);
    virtual struct GetMap 	*getMap();
    virtual struct WhereAmI 	*getPlayer();
    virtual void		shoot();
    virtual void		playProtocol();
  };
}

#endif
