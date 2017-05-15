/*
** AProtocol.cpp for cpp_arcade in /home/enguerrand/delivery/cpp_arcade/AProtocol.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Sun Mar 26 15:12:05 2017 Enguerrand Allamel
** Last update Sun Mar 26 15:12:05 2017 Enguerrand Allamel
*/

#include "AProtocol.hpp"

arcade::AProtocol::AProtocol()
{
}

void arcade::AProtocol::execAction(CommandType commandType)
{
  arcade::GetMap *map = NULL;
  arcade::WhereAmI *player = NULL;

  switch (commandType)
    {
      case CommandType::WHERE_AM_I:
	player = this->getPlayer();
      	std::cout.write(reinterpret_cast<char *>(player), sizeof(arcade::WhereAmI) + (player->lenght * sizeof(arcade::Position)));
	break;
      case CommandType::GET_MAP:
	map = this->getMap();
      	std::cout.write(reinterpret_cast<char *>(map), sizeof(arcade::GetMap) + (map->width * map->height * sizeof(arcade::TileType)));
	break;
      case CommandType::GO_UP:
	this->setDirectionPlayer(MoveDirection::UP);
      	break;
      case CommandType::GO_DOWN:
	this->setDirectionPlayer(MoveDirection::DOWN);
      	break;
      case CommandType::GO_LEFT:
	this->setDirectionPlayer(MoveDirection::LEFT);
      	break;
      case CommandType::GO_RIGHT:
	this->setDirectionPlayer(MoveDirection::RIGHT);
      	break;
      case CommandType::GO_FORWARD:
	this->setDirectionPlayer(MoveDirection::FORWARD);
      	break;
      case CommandType::SHOOT:
	this->shoot();
	break;
      case CommandType::ILLEGAL:
	// Stand by not defined
	break;
      case CommandType::PLAY:
	this->playProtocol();
      	break;
      default:
	std::cout << "Not found commandType" << std::endl;
    }
}