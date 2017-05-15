/*
** ArcadeSFML.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/lib/SFML
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Mon Mar 13 13:28:22 2017 cauvin-m
** Last update Tue Apr 04 21:04:00 2017 cauvin-m
*/

#ifndef ARCADE_NIBBLER_HPP
#define  ARCADE_NIBBLER_HPP

#include <iostream>
#include <list>
#include <ctime>
#include "AProtocol.hpp"

namespace arcade
{
  class CentipedeBlock
  {
    Pos         _pos;
    size_t  	_nbLife;

   public:
    CentipedeBlock(Pos const& pos, int nbLife) : _pos(pos), _nbLife(nbLife) {};
    virtual ~CentipedeBlock() {}

    void        setPos(Pos const& pos) {this->_pos = pos;}
    void        setNbLife(int nbLife) {this->_nbLife = nbLife;}

    Pos         getPos() const {return (this->_pos);}
    size_t     	getNbLife() const {return (this->_nbLife);}
  };

  class CentipedeEnemy
  {
   private:
    std::vector<Pos>  _posList;
    Pos               _dir;

   public:
    CentipedeEnemy() {}
    virtual ~CentipedeEnemy() {}

    void        setPosList(std::vector<Pos> const& posList) {this->_posList = posList;}
    void        setDir(Pos dir) {this->_dir = dir;}

    std::vector<Pos> 	getPosList() const {return (this->_posList);}
    Pos     		getDir() const {return (this->_dir);}
  };

  class Centipede : public AProtocol
  {
   private:
    Position				_player;
    MoveDirection 			_dir;
    std::list<CentipedeBlock>		_blocks;
    int 				_speed;
    bool 				_isFire;
    Position				_shoot;
    std::map<size_t, std::string>	_blockLifeColor;
    std::vector<CentipedeEnemy>		_enemy;
    size_t 				_nbKill;
    size_t 				_soundPlay;
   public:
    Centipede();
    virtual ~Centipede();

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

    int 	checkIsBlock(int x, int y) const;
    int 	checkPosition() const; 	// 0: Nothing / 1: GameOver
    void	checkFire();

    int 	checkIsCentipedeEnemy(int x, int y);

    void	reset();

    void 	addBlock();
    void	removeLifeBlock(int x, int y);

    void	moveCentipedeEnemy();

    void 	displayPlayer(IGraphicLib *graphicLib) const;
    void 	displayBlocks(IGraphicLib *graphicLib);
    void 	displayBorder(IGraphicLib *graphicLib) const;
    void 	displayCentipedeEnemy(IGraphicLib *graphicLib) const;
    void 	displayShoot(IGraphicLib *graphicLib) const;
    void 	displayScore(IGraphicLib *graphicLib) const;


    /*
     * Protocol functions
     */

    virtual struct GetMap 	*getMap();
    virtual struct WhereAmI 	*getPlayer();
    virtual void 		setDirectionPlayer(arcade::AProtocol::MoveDirection move);
    virtual void		shoot();
    virtual void 		playProtocol();
  };
}

#endif /* ARCADE_NIBBLER_HPP */
