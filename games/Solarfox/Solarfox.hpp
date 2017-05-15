/*
** Solarfox.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/games/Solarfox
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Sun Apr 02 02:24:38 2017 cauvin-m
** Last update Sun Apr 09 21:31:24 2017 cauvin-m
*/

#ifndef SOLARFOX_HPP_
#define  SOLARFOX_HPP_

# include <map>
# include <vector>
# include <fstream>
# include <ctime>
# include <cstdlib>
# include <dirent.h>
# include "Shoot.hpp"
# include "AProtocol.hpp"
# include "ArcadeError.hpp"

namespace arcade
{
  class Solarfox : public AProtocol
  {
  private:
    size_t                                              _turns;
    int                                                 _level;
    std::map<int, std::map<int, std::map<int, int>>>    _map;
    std::map<int, int>                                  _powerupsList;
    std::map<int, std::map<int, int>>                   _curMap;
    Player                                              _player;
    bool                                                _playerHasMoved;
    size_t                                              _nbPowerups;
    std::vector<Shoot>                                  _shoots;
    std::vector<Player>                                 _enemies;
    bool                                                _isPaused;
    int                                                 _boost;
    Score                                               _highScore;
    IGraphicLib                                         *_graphicLib;

  public:
    Solarfox();
    virtual ~Solarfox();

    virtual int         initGame(IGraphicLib *graphicLib, Score const& highScore);
    virtual int         play();
    virtual int         actionOfEvent(EventKeyBoard const& event);
    virtual int         display(IGraphicLib *graphicLib);

    bool                playerHasCollidedWithBullet(Player const& player, StatusType const& type) const;

    Pos                 loadSolarfoxMaps();
    Pos                 getPlayerPosInMap(std::map<int, std::map<int, int>> map) const;

    void                createEnemies();
    void                movePlayer();
    void                moveShoots();
    void                moveEnemies() ;
    void                createEnemyShoots();
    void                resetEnemiesDirections();
    bool                powerupsHandler(Shoot const& shoot);
    void                breakingShoots(Shoot const& shoot);

    bool                hasOnlyDigits(std::string const& str) const;


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
