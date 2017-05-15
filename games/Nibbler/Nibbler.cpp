/*
** ArcadeSFML.cpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/lib/SFML
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Mon Mar 13 13:28:04 2017 cauvin-m
** Last update Sun Apr 09 13:50:47 2017 cauvin-m
*/

#include "Nibbler.hpp"

arcade::Nibbler::Nibbler()
{
  Position position;

  this->_dir = arcade::AProtocol::MoveDirection::RIGHT;
  this->_lastDir = arcade::AProtocol::MoveDirection::RIGHT;
  this->_waitForMove = 5;
  this->_wait_i = 0;

  this->setGameSize(Pos(50, 50));

  this->_lenght = 4;

  position.x = 20;
  position.y = 20;
  for (size_t i = 0; i < this->_lenght; ++i)
    {
      position.x = position.x - 1;
      this->_snake.push_back(position);
    }

  this->addBlock();
  this->addPowerup();

  this->_playLevelUp = false;
  this->_speed = 5;
}

arcade::Nibbler::~Nibbler()
{
}

int arcade::Nibbler::play()
{
  static int i = 0;

  if (i == this->_speed)
    {
      this->playProtocol();
      i = 0;
    }
  i += 1;
  return (0);
}

int arcade::Nibbler::initGame(arcade::IGraphicLib *graphicLib, Score const &highScore)
{
  this->_highScore = highScore;

  graphicLib->addSprite("em_snake_sand.png", 0x000000, " ");

  graphicLib->addSprite("em_snake_body.png", 0xf2e800, " ");
  graphicLib->addSprite("em_snake_head.png", 0xbebf4c, " ");

  graphicLib->addSprite("em_snake_powerup.png", 0xCC4956, " ");

  graphicLib->addSprite("block.png", 0xFFFFFF, " ");

  graphicLib->addSprite("bg.png", 0x000000, " ");
  graphicLib->addSprite("border.png", 0xFFFFFF, " ");

  return (0);
}

int arcade::Nibbler::actionOfEvent(EventKeyBoard const &event)
{
  if (event == arcade::EventKeyBoard::EK_ESCAPE)
    return (-3);
  else if (event == arcade::EventKeyBoard::EK_NUMPAD9)
    return (-2);
  else if (event == arcade::EventKeyBoard::EK_NUMPAD8)
    return (-1);

  if (event == arcade::EventKeyBoard::EK_LEFT)
    setDirectionPlayer(arcade::Nibbler::MoveDirection::LEFT);
  else if (event == arcade::EventKeyBoard::EK_RIGHT)
    setDirectionPlayer(arcade::Nibbler::MoveDirection::RIGHT);
  else if (event == arcade::EventKeyBoard::EK_UP)
    setDirectionPlayer(arcade::Nibbler::MoveDirection::UP);
  else if (event == arcade::EventKeyBoard::EK_DOWN)
    setDirectionPlayer(arcade::Nibbler::MoveDirection::DOWN);

  return (0);
}

int arcade::Nibbler::display(IGraphicLib *graphicLib)
{
  graphicLib->p_backGround("bg");

  this->displayPlayer(graphicLib);
  this->displayFood(graphicLib);
  this->displayBlocks(graphicLib);
  this->displayBorder(graphicLib);
  this->displayScore(graphicLib);

  if (this->_playLevelUp)
    {
      graphicLib->p_sound("em_snake_levelup.wav", SoundType::ST_SOUND);
      this->_playLevelUp = false;
    }

  return (0);
}

extern "C" arcade::Nibbler *CObject()
{
  return (new arcade::Nibbler);
}

extern "C" void DObject(arcade::Nibbler *obj)
{
  delete obj;
}

/*
 * My functions
 */

int arcade::Nibbler::movePlayer(arcade::AProtocol::MoveDirection move, int value)
{
  Position add;

  add = (*this->_snake.begin());
  if (move == arcade::AProtocol::MoveDirection::LEFT &&
	  this->_lastDir != arcade::AProtocol::MoveDirection::RIGHT
	  )
    add.x -= value;
  else if (move == arcade::AProtocol::MoveDirection::RIGHT &&
	  this->_lastDir != arcade::AProtocol::MoveDirection::LEFT
	  )
    add.x += value;
  else if (move == arcade::AProtocol::MoveDirection::UP &&
	  this->_lastDir != arcade::AProtocol::MoveDirection::DOWN
	  )
    add.y -= value;
  else if (move == arcade::AProtocol::MoveDirection::DOWN &&
	  this->_lastDir != arcade::AProtocol::MoveDirection::UP
	  )
      add.y += value;
  else
    {
      this->_dir = this->_lastDir;
      this->movePlayer(this->_lastDir, 1);
      return (0);
    }

  this->_snake.push_front(add);

  if (this->_snake.size() > this->_lenght)
    this->_snake.pop_back();

  if (checkPosition() == 1)
    this->setGameState(GameState::EXIT_ON_SUCCESS);
  checkIsPowerup();
  return (0);
}

int arcade::Nibbler::checkPosition() const
{
  if ((*this->_snake.begin()).x <= 0 || (*this->_snake.begin()).x >= 40)
    return (1);
  else if ((*this->_snake.begin()).y <= 0 || (*this->_snake.begin()).y >= 40)
    return (1);
  for (auto it = std::next(this->_snake.begin()); it != this->_snake.end(); ++it)
    {
      if ((*this->_snake.begin()).x == (*it).x && (*this->_snake.begin()).y == (*it).y)
	return (1);
    }
  for (auto it = this->_blocks.begin(); it != this->_blocks.end(); ++it)
    {
      if ((*this->_snake.begin()).x == (*it).x && (*this->_snake.begin()).y == (*it).y)
	return (1);
    }
  return (0);
}

int arcade::Nibbler::checkIsPowerup()
{
  for (auto it = this->_foods.begin(); it != this->_foods.end(); ++it)
    {
      if ((*this->_snake.begin()).x == (*it).x && (*this->_snake.begin()).y == (*it).y)
	{
	  this->_foods.erase(it);
	  this->_lenght += 1;
	  this->setScore(std::to_string(std::stoi(this->getScore()) + 100));
	  this->_playLevelUp = true;
	  if ((std::stol(this->getScore()) % 1000) == 0 && this->_speed > 1)
	    this->_speed -= 1;
	  return (1);
	}
    }
  return (0);
}

void arcade::Nibbler::addPowerup()
{
  Position position;

  std::srand(std::time(0));
  position.x = (std::rand() % 38) + 1;
  position.y = (std::rand() % 38) + 1;

  for (auto it = this->_snake.begin(); it != this->_snake.end();)
    {
      if (position.x == (*it).x || position.y == (*it).y)
	{
	  it = this->_snake.begin();
	  position.x = (std::rand() % 40);
	  position.y = (std::rand() % 40);
	}
      else
	{
	  ++it;
	}
    }
  this->_foods.push_back(position);
}

void arcade::Nibbler::addBlock()
{
  size_t nb_block = 40;
  Position position;

  for (size_t i = 0; i < nb_block ; ++i)
    {
      std::srand(std::time(0));
      position.x = (std::rand() % 40);
      position.y = (std::rand() % 40);
      for (auto it = this->_blocks.begin() ; it != this->_blocks.end() ;)
	{
	  if (position.x == (*it).x || position.y == (*it).y)
	    {
	      it = this->_blocks.begin();
	      position.x = (std::rand() % 40);
	      position.y = (std::rand() % 40);
	    }
	  else
	    {
	      ++it;
	    }
	}
      this->_blocks.push_back(position);
    }
}

void arcade::Nibbler::displayPlayer(IGraphicLib *graphicLib) const
{
  Position other;

  other = *(this->_snake.begin());
  for (auto it = this->_snake.begin(); it != this->_snake.end(); ++it)
    {
      if (it == this->_snake.begin())
	graphicLib->p_cell(Pos((*it).x + 5, (*it).y + 5), "em_snake_head.png", 0);
      else
	graphicLib->p_cell(Pos((*it).x + 5, (*it).y + 5), "em_snake_body.png", 0);
      other = (*it);
    }
}

void arcade::Nibbler::displayFood(IGraphicLib *graphicLib) const
{
  for (auto it = this->_foods.begin(); it != this->_foods.end(); ++it)
    {
      graphicLib->p_cell(Pos((*it).x + 5, (*it).y + 5), "em_snake_powerup.png", 0);
    }
}

void arcade::Nibbler::displayBlocks(IGraphicLib *graphicLib) const
{
  for (auto it = this->_blocks.begin(); it != this->_blocks.end(); ++it)
    {
      graphicLib->p_cell(Pos((*it).x + 5, (*it).y + 5), "block.png", 0);
    }
}

void arcade::Nibbler::displayBorder(IGraphicLib *graphicLib) const
{
  graphicLib->p_hLine(Pos(5, 5), 40, "border.png", 0);
  graphicLib->p_hLine(Pos(5, 45), 40, "border.png", 0);
  graphicLib->p_vLine(Pos(5, 5), 40, "border.png", 0);
  graphicLib->p_vLine(Pos(45, 5), 41, "border.png", 0);
}

void arcade::Nibbler::displayScore(IGraphicLib *graphicLib) const
{
  graphicLib->p_text(Pos(2, 2), "Score", 0xf2e800, 16);
  graphicLib->p_text(Pos(10, 2), this->getScore(), 0xCC4956, 16);
  graphicLib->p_text(Pos(15, 2), "HighScore", 0xf2e800, 16);
  graphicLib->p_text(Pos(26, 2), this->_highScore.name, 0x1562CA, 16);
  graphicLib->p_text(Pos(30, 2), this->_highScore.score, 0xCC4956, 16);
}

/*
 * Protocol functions
 */

struct arcade::GetMap	*arcade::Nibbler::getMap()
{
  struct arcade::GetMap	*map;

  if ((map = new arcade::GetMap[sizeof(arcade::GetMap) + (40 * 40 * sizeof(arcade::TileType))]) == NULL)
    return NULL;
  map->type = arcade::CommandType::GET_MAP;
  map->height = 40;
  map->width = 40;
  for (int i = 0 ; i < map->height ; i++)
    {
      for (int j = 0 ; j < map->width ; j++)
	{
	  map->tile[(i * map->width) + j] = arcade::TileType::EMPTY;
	}
    }
  for (auto it = this->_foods.begin(); it != this->_foods.end(); ++it)
    {
      map->tile[((*it).y * map->width) + (*it).x] = arcade::TileType::POWERUP;
    }
  return map;
}

struct arcade::WhereAmI 	*arcade::Nibbler::getPlayer()
{
  struct arcade::WhereAmI	*player;

  if ((player = new arcade::WhereAmI[sizeof(arcade::WhereAmI) + (this->_lenght * sizeof(arcade::Position))]) == NULL)
  	return NULL;
  player->type = arcade::CommandType::WHERE_AM_I;
  player->lenght = this->_lenght;
  int i = 0;
  for (auto it = this->_snake.begin(); it != this->_snake.end(); ++it)
    {
      player->position[i].x = (*it).x;
      player->position[i].y = (*it).y;
      i += 1;
    }
  return player;
}

void arcade::Nibbler::setDirectionPlayer(arcade::AProtocol::MoveDirection move)
{
  this->_lastDir = this->_dir;
  this->_dir = move;
}

void 	arcade::Nibbler::playProtocol()
{
  if (this->_foods.empty())
    this->addPowerup();

  this->movePlayer(this->_dir, 1);
}


// Protocol Play
extern "C" void Play(void)
{
  arcade::CommandType n;

  arcade::Nibbler *game = new arcade::Nibbler();
  while (std::cin.read(reinterpret_cast<char *>(&n), sizeof(n)))
      game->execAction(n);
  delete game;
};
