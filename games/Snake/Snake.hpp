/*
** ArcadeSFML.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/lib/SFML
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Mon Mar 13 13:28:22 2017 cauvin-m
** Last update Tue Apr 04 21:04:00 2017 cauvin-m
*/

#ifndef ARCADE_SNAKE_HPP
#define  ARCADE_SNAKE_HPP

#include <iostream>
#include <list>
#include <ctime>
#include "../Protocol/AProtocol.hpp"

namespace arcade
{
  class Snake : public AProtocol
  {
   private:
    MoveDirection 			_dir;
    MoveDirection 			_lastDir;
    std::list<Position> 		_snake;
    size_t 				_lenght;
    size_t 				_waitForMove;
    size_t 				_wait_i;
    std::list<Position> 		_foods;
    bool 				_playLevelUp;
    int 				_speed;
   public:
    Snake();
    virtual ~Snake();

    /*
     * IGame functions
     */

    virtual int initGame(IGraphicLib *graphicLib, Score const &highScore);
    virtual int play();
    virtual int actionOfEvent(EventKeyBoard const &event);
    virtual int display(IGraphicLib *graphicLib);

    /*
     * My Functions
     */

    int 	movePlayer(arcade::AProtocol::MoveDirection move, int value);

    int 	checkPosition() const; 	// 0: Nothing / 1: GameOver
    int 	checkIsPowerup(); 	// 0: Nothing / 1: Powerup

    void 	addPowerup();

    void 	displayPlayer(IGraphicLib *graphicLib) const;
    void 	displayFood(IGraphicLib *graphicLib) const;
    void 	displayBorder(IGraphicLib *graphicLib) const;
    void 	displayScore(IGraphicLib *graphicLib) const;


    /*
     * Protocol functions
     */

    virtual struct GetMap 	*getMap();
    virtual struct WhereAmI 	*getPlayer();
    virtual void 		setDirectionPlayer(arcade::AProtocol::MoveDirection move);
    virtual void		shoot() {}
    virtual void 		playProtocol();
  };
}

#endif /* ARCADE_SFML_HPP */
