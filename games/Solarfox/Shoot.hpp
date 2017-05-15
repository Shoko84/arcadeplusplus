/*
** Shoot.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/games/Solarfox
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Sat Apr 08 23:20:28 2017 cauvin-m
** Last update Sat Apr 08 23:21:13 2017 cauvin-m
*/

#ifndef SHOOT_HPP_
#define  SHOOT_HPP_

# include "AGame.hpp"

namespace arcade
{
  class Shoot
  {
    Pos         _pos;
    Pos         _dir;
    StatusType  _type;
    char        _life;

  public:
    Shoot(Pos pos, Pos dir, StatusType type, int const& life) : _pos(pos), _dir(dir), _type(type), _life(life) {}
    virtual ~Shoot() {}

    Pos         getPos() const {return (this->_pos);}
    Pos         getDir() const {return (this->_dir);}
    StatusType  getType() const {return (this->_type);}
    char        getLife() const {return (this->_life);}

    void        setPos(Pos const& pos) {this->_pos = pos;}
    void        setDir(Pos const& dir) {this->_dir = dir;}
    void        setLife(char const& life) {this->_life = life;}
  };
}

#endif
