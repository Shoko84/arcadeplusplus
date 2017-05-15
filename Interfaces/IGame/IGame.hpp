/*
** IGame.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/Interfaces/IGame
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Tue Apr 04 17:38:13 2017 cauvin-m
** Last update Tue Apr 04 22:47:03 2017 cauvin-m
*/

#ifndef IGAME_HPP_
# define IGAME_HPP_

#include <iostream>
#include "IGraphicLib.hpp"

namespace arcade
{

  enum class GameState : int
    {
      EXIT_ON_ERROR = -1,   // le jeu quitte avant la fin
      DEFAULT = 0,          // le jeu n'a pas encore commencé
      EXIT_ON_SUCCESS = 1,  // le jeu quitte normalement
      PAUSE,                // le jeu est en pause
      RUN                   // le jeu est en marche
    };

  struct Score
  {
    Score(void){}
    Score(std::string const& _name, std::string const& _score) : name(_name), score(_score){}

    std::string         name;
    std::string         score;
  };

  class IGame
  {
  public:
    virtual ~IGame() {}
    virtual int         initGame(IGraphicLib* graphicLib, Score const& highScore) = 0; // Musique du jeu par exemple

  public:
    virtual GameState   getGameState(void) const = 0;
    virtual size_t      getFps(void) const = 0;
    virtual Pos         getGameSize(void) const = 0;
    virtual std::string getScore(void) const = 0;
    virtual void        setGameState(GameState const& gameState) = 0;
    virtual void        setScore(std::string const& score) = 0;
    virtual void        setGameSize(Pos const& gameSize) = 0;
    virtual int         play(void) = 0;
    virtual int         actionOfEvent(EventKeyBoard const& event) = 0;
    virtual int         display(IGraphicLib* graphicLib) = 0;
  };

}

#endif
