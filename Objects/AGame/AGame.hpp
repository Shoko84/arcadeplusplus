/*
** AGame.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/Objects/AGame
**
** Made by Maxime Cauvin
** Login   <cauvin_m@epitech.net>
**
** Started on  Wed Mar 08 15:13:14 2017 cauvin-m
** Last update Sat Apr 08 23:19:59 2017 cauvin-m
*/

#ifndef AGAME_HPP_
# define AGAME_HPP_

#include "IGame.hpp"

namespace arcade
{
  enum class StatusType : int
  {
    ALLY = 0,
    ENEMY = 1
  };

  class Player
  {
    Pos         _pos;
    Pos         _dir;
    StatusType  _type;

  public:
    Player() {};
    Player(Pos const& pos, Pos const& dir, StatusType type) : _pos(pos), _dir(dir), _type(type) {}
    virtual ~Player() {};

    void        setPos(Pos const& pos) {this->_pos = pos;}
    void        setDir(Pos const& dir) {this->_dir = dir;}
    void        setType(StatusType const& type) {this->_type = type;}

    Pos         getPos() const {return (this->_pos);}
    Pos         getDir() const {return (this->_dir);}
    StatusType  getType() const {return (this->_type);}
  };

  class AGame : public IGame
  {
  public:
    AGame(void) : _gameState(GameState::RUN), _gameSize(Pos(35, 35)), _highScore(Score("", "0")) {}
    virtual ~AGame(void) {}

  public:
    virtual int         initGame(IGraphicLib *graphicLib, Score const& highScore) = 0;

  public:
    virtual int         play() = 0;
    virtual int         actionOfEvent(EventKeyBoard const& event) = 0;
    virtual int         display(IGraphicLib *graphicLib) = 0;

  public:
    GameState           getGameState(void) const {return (this->_gameState);}
    size_t              getFps(void) const {return (this->_fps);}
    void                setGameSize(Pos const& gameSize) {this->_gameSize = gameSize;}
    Pos                 getGameSize(void) const {return (this->_gameSize);}
    std::string         getScore(void) const {return (this->_score);}
    void                setGameState(GameState const& gameState) {this->_gameState = gameState;}
    void                setScore(std::string const& score) {this->_score = score;}

  protected:
    GameState           _gameState;
    int                 _fps = 100;
    Pos                 _gameSize;
    std::string         _score = "0";
    Score               _highScore;
  };

}

#endif
