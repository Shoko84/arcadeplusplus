/*
** AProtocol.hpp for cpp_arcade in /home/enguerrand/delivery/cpp_arcade/AProtocol.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Sun Mar 26 15:12:05 2017 Enguerrand Allamel
** Last update Tue Apr 04 21:03:02 2017 cauvin-m
*/

#ifndef CPP_ARCADE_APROTOCOL_HPP
#define CPP_ARCADE_APROTOCOL_HPP

#include <unistd.h>
#include <stdlib.h>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <map>
#include "AGame.hpp"
#include "Protocol.hpp"

namespace arcade
{
  class AProtocol : public AGame
  {
   public:
    enum class MoveDirection : int
    {
      UP,
      DOWN,
      LEFT,
      RIGHT,
      FORWARD,
      DEFAULT
    };
   public:
    AProtocol();
    virtual ~AProtocol() {}

    void 			execAction(CommandType commandType);

    virtual void 		setDirectionPlayer(arcade::AProtocol::MoveDirection move) = 0;
    virtual struct GetMap 	*getMap() = 0;
    virtual struct WhereAmI 	*getPlayer() = 0;
    virtual void		shoot() = 0;
    virtual void		playProtocol() = 0;
  };
}

#endif //CPP_ARCADE_APROTOCOL_HPP
