/*
** ArcadeSFML.cpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/lib/SFML
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Mon Mar 13 13:28:04 2017 cauvin-m
** Last update Sun Apr 09 13:52:58 2017 cauvin-m
*/

#include "Centipede.hpp"

arcade::Centipede::Centipede()
{
  this->setGameSize(Pos(50, 50));

  this->_soundPlay = 0;

  this->_blockLifeColor =
	  {
		  {5, "em_centipede_block_5.png"},
		  {4, "em_centipede_block_4.png"},
		  {3, "em_centipede_block_3.png"},
		  {2, "em_centipede_block_2.png"},
		  {1, "em_centipede_block_1.png"},
	  };
  this->reset();
}

arcade::Centipede::~Centipede()
{
}

int arcade::Centipede::play()
{
  this->playProtocol();
  return (0);
}

int arcade::Centipede::initGame(arcade::IGraphicLib *graphicLib, Score const &highScore)
{
  this->_highScore = highScore;

  graphicLib->addSprite("em_centipede_player.png", 0xf2e800, " ");

  graphicLib->addSprite("em_centipede_fire.png", 0xCC4956, " ");

  graphicLib->addSprite("em_centipede_block_5.png", 0xFFFFFF, " ");
  graphicLib->addSprite("em_centipede_block_4.png", 0xCBCBCB, " ");
  graphicLib->addSprite("em_centipede_block_3.png", 0xA3A3A3, " ");
  graphicLib->addSprite("em_centipede_block_2.png", 0x8F8F8F, " ");
  graphicLib->addSprite("em_centipede_block_1.png", 0x686868, " ");

  graphicLib->addSprite("em_centipede_enemy.png", 0x1FC224, " ");

  graphicLib->addSprite("bg.png", 0x000000, " ");
  graphicLib->addSprite("border.png", 0xFFFFFF, " ");

  return (0);
}

int arcade::Centipede::actionOfEvent(EventKeyBoard const &event)
{
  if (event == arcade::EventKeyBoard::EK_ESCAPE)
    return (-3);
  else if (event == arcade::EventKeyBoard::EK_NUMPAD9)
    return (-2);
  else if (event == arcade::EventKeyBoard::EK_NUMPAD8)
    return (-1);

  if (event == arcade::EventKeyBoard::EK_LEFT)
    setDirectionPlayer(arcade::Centipede::MoveDirection::LEFT);
  else if (event == arcade::EventKeyBoard::EK_RIGHT)
    setDirectionPlayer(arcade::Centipede::MoveDirection::RIGHT);
  else if (event == arcade::EventKeyBoard::EK_UP)
    setDirectionPlayer(arcade::Centipede::MoveDirection::UP);
  else if (event == arcade::EventKeyBoard::EK_DOWN)
    setDirectionPlayer(arcade::Centipede::MoveDirection::DOWN);
  else if (event == arcade::EventKeyBoard::EK_SPACE)
    this->shoot();

  return (0);
}

int arcade::Centipede::display(IGraphicLib *graphicLib)
{
  graphicLib->p_backGround("bg");

  this->displayPlayer(graphicLib);
  this->displayBlocks(graphicLib);
  this->displayBorder(graphicLib);
  this->displayCentipedeEnemy(graphicLib);
  this->displayShoot(graphicLib);
  this->displayScore(graphicLib);

  switch (this->_soundPlay)
    {
      case 1:
	graphicLib->p_sound("em_centipede_shoot.wav", SoundType::ST_SOUND);
	break;
      case 2:
	graphicLib->p_sound("em_centipede_lose.wav", SoundType::ST_SOUND);
      	break;
      case 3:
	graphicLib->p_sound("em_centipede_blockSpawn.wav", SoundType::ST_SOUND);
      	break;
    }
  this->_soundPlay = 0;

  return (0);
}

extern "C" arcade::Centipede *CObject()
{
  return (new arcade::Centipede);
}

extern "C" void DObject(arcade::Centipede *obj)
{
  delete obj;
}

/*
 * My functions
 */

int arcade::Centipede::movePlayer(arcade::AProtocol::MoveDirection move, int value)
{
  if (move == arcade::AProtocol::MoveDirection::LEFT &&
	  this->_player.x > 1
	  && checkIsBlock(this->_player.x - 1, this->_player.y) == 0)
    this->_player.x -= value;
  else if (move == arcade::AProtocol::MoveDirection::RIGHT &&
	  this->_player.x < 39
	   && checkIsBlock(this->_player.x + 1, this->_player.y)  == 0)
    this->_player.x += value;
  else if (move == arcade::AProtocol::MoveDirection::UP &&
	  this->_player.y >= 33
	  && checkIsBlock(this->_player.x, this->_player.y - 1)  == 0)
    this->_player.y -= value;
  else if (move == arcade::AProtocol::MoveDirection::DOWN &&
	  this->_player.y < 39
	  && checkIsBlock(this->_player.x, this->_player.y + 1)  == 0)
    this->_player.y += value;

  this->_dir = AProtocol::MoveDirection::DEFAULT;
  if (checkPosition() == 1)
    this->setGameState(GameState::EXIT_ON_SUCCESS);
  return (0);
}

int arcade::Centipede::checkIsBlock(int x, int y) const
{
  for (auto it = this->_blocks.begin(); it != this->_blocks.end(); ++it)
    {
      if (x == (*it).getPos().x && y == (*it).getPos().y)
	return (1);
    }
  return (0);
}

int arcade::Centipede::checkPosition() const
{
  for (auto it = this->_enemy.begin(); this->_enemy.size() > 0 && it != this->_enemy.end(); ++it)
    {
      std::vector<Pos> posList;
      posList = (*it).getPosList();
      for (auto iu = posList.begin(); iu != posList.end(); ++iu)
	{
	  if ((*iu).x == this->_player.x && (*iu).y == this->_player.y)
	    return (1);
	}
    }
  return (0);
}

void arcade::Centipede::addBlock()
{
  size_t nb_block = 36;
  Pos 	position;

  for (size_t i = 0; i < nb_block ; ++i)
    {
      std::srand(std::time(0));
      position.x = (std::rand() % 36);
      position.y = (std::rand() % 36) + 2;
      for (auto it = this->_blocks.begin() ; it != this->_blocks.end() ;)
	{
	  if (position.x == (*it).getPos().x || position.y == (*it).getPos().y)
	    {
	      it = this->_blocks.begin();
	      position.x = (std::rand() % 36);
	      position.y = (std::rand() % 36) + 2;
	    }
	  else
	    {
	      ++it;
	    }
	}
      this->_blocks.push_back(CentipedeBlock(position, 5));
    }
}

void arcade::Centipede::displayPlayer(IGraphicLib *graphicLib) const
{
  graphicLib->p_cell(Pos(this->_player.x + 5, this->_player.y + 5), "em_centipede_player.png", 0);
}

void arcade::Centipede::displayBlocks(IGraphicLib *graphicLib)
{
  for (auto it = this->_blocks.begin(); it != this->_blocks.end(); ++it)
    {
      graphicLib->p_cell(Pos((*it).getPos().x + 5, (*it).getPos().y + 5), this->_blockLifeColor[(*it).getNbLife()], 0);
    }
}

void arcade::Centipede::displayBorder(IGraphicLib *graphicLib) const
{
  graphicLib->p_hLine(Pos(5, 5), 40, "border.png", 0);
  graphicLib->p_hLine(Pos(5, 45), 40, "border.png", 0);
  graphicLib->p_vLine(Pos(5, 5), 40, "border.png", 0);
  graphicLib->p_vLine(Pos(45, 5), 41, "border.png", 0);
}


void arcade::Centipede::displayShoot(IGraphicLib *graphicLib) const
{
  if (this->_isFire)
    graphicLib->p_cell(Pos(this->_shoot.x + 5, this->_shoot.y + 5), "em_centipede_fire.png", 0);
}

void arcade::Centipede::displayScore(IGraphicLib *graphicLib) const
{
  graphicLib->p_text(Pos(2, 2), "Score", 0xf2e800, 16);
  graphicLib->p_text(Pos(10, 2), this->getScore(), 0xCC4956, 16);
  graphicLib->p_text(Pos(15, 2), "HighScore", 0xf2e800, 16);
  graphicLib->p_text(Pos(26, 2), this->_highScore.name, 0x1562CA, 16);
  graphicLib->p_text(Pos(30, 2), this->_highScore.score, 0xCC4956, 16);
}

void	arcade::Centipede::checkFire()
{
  if (this->_isFire)
    {
      this->_shoot.y -= 1;
      if (this->_shoot.y <= 0 || this->checkIsBlock(this->_shoot.x, this->_shoot.y) == 1)
	{
	  this->removeLifeBlock(this->_shoot.x, this->_shoot.y);
	  this->_isFire = false;
	}
      else if (this->checkIsCentipedeEnemy(this->_shoot.x, this->_shoot.y) == 1)
	{
	  this->_isFire = false;
	  this->setScore(std::to_string(std::stoi(this->getScore()) + 100));
	  this->_blocks.push_back(CentipedeBlock(Pos(this->_shoot.x, this->_shoot.y), 5));
	}
    }
}

void	arcade::Centipede::removeLifeBlock(int x, int y)
{
  for (auto it = this->_blocks.begin(); it != this->_blocks.end(); ++it)
    {
      if (x == (*it).getPos().x && y == (*it).getPos().y)
	{
	  (*it).setNbLife((*it).getNbLife() - 1);
	  if ((*it).getNbLife() <= 0)
	    this->_blocks.erase(it);
	  return ;
	}
    }
}

int	arcade::Centipede::checkIsCentipedeEnemy(int x, int y)
{
  bool touch = false;

  for (size_t i = 0; i < this->_enemy.size(); i++)
    {
      std::vector<Pos> 	posList;

      posList = this->_enemy[i].getPosList();
      for (size_t b = 0 ; b < posList.size() ; ++b)
	{
	  if (posList[b].x == x && posList[b].y == y)
	    {
	      touch = true;
	      break;
	    }
	}

      if (touch)
	{
	  std::vector<Pos> 	nList;
	  CentipedeEnemy	nEnemy;

	  posList = this->_enemy[i].getPosList();
	  nEnemy.setDir(Pos(this->_enemy[i].getDir().x * (-1), this->_enemy[i].getDir().y));
	  for (size_t a = 0 ; a < posList.size() ; a++)
	    {
	      if (posList[a].x == x && posList[a].y == y)
		{
		  posList.erase(posList.begin() + i);
		  break;
		}
	      nList.push_back(Pos(posList[a].x, posList[a].y));
	      posList.erase(posList.begin() + i);
	    }
	 nEnemy.setPosList(nList);
	 if (!nList.empty())
	    this->_enemy.push_back(nEnemy);
	  this->_enemy[i].setPosList(posList);
	  if (posList.size() <= 0)
	    this->_enemy.erase(this->_enemy.begin() + i);
	  this->_soundPlay = 3;
	  return (1);
	}
    }
  return (0);
}

void arcade::Centipede::displayCentipedeEnemy(IGraphicLib *graphicLib) const
{
  for (auto it = this->_enemy.begin(); this->_enemy.size() > 0 && it != this->_enemy.end(); ++it)
    {
      std::vector<Pos> posList;
      posList = (*it).getPosList();
      for (auto iu = posList.begin(); iu != posList.end(); ++iu)
	{
	  graphicLib->p_cell(Pos((*iu).x + 5, (*iu).y + 5), "em_centipede_enemy.png", 0);
	}
    }
}


void arcade::Centipede::moveCentipedeEnemy()
{
  for (auto it = this->_enemy.begin(); it != this->_enemy.end(); ++it)
    {
      std::vector<Pos> 	posList;

      posList = (*it).getPosList();

      Pos		n_pos(posList.back().x + (*it).getDir().x, posList.back().y);
      if (n_pos.x <= 0 || n_pos.x >= 40 || checkIsBlock(n_pos.x, n_pos.y) == 1)
	{
	  n_pos.x = posList.back().x;
	  n_pos.y += (*it).getDir().y;
	  (*it).setDir(Pos((*it).getDir().x * -1, (*it).getDir().y));
	}
      if (n_pos.y >= 40 || n_pos.y <= 0)
	{
	  n_pos.y -= (*it).getDir().y;
	  (*it).setDir(Pos((*it).getDir().x, (*it).getDir().y * -1));
	  this->_soundPlay = 2;
	}
      if (n_pos.y >= 39)
	this->setScore(std::to_string(0));
      posList.push_back(n_pos);
      posList.erase(posList.begin());
      (*it).setPosList(posList);
    }
}

void arcade::Centipede::reset()
{
  this->_player.x = 20;
  this->_player.y = 39;

  this->_dir = AProtocol::MoveDirection::DEFAULT;

  this->_blocks.clear();
  this->addBlock();
  this->_nbKill = 0;

  this->_speed = 5;

  this->_isFire = false;

  CentipedeEnemy 	enemy;
  std::vector<Pos>	posList(5);

  posList[0] = Pos(1, 1);
  posList[1] = Pos(2, 1);
  posList[2] = Pos(3, 1);
  posList[3] = Pos(4, 1);
  posList[4] = Pos(5, 1);


  enemy.setDir(Pos(1, 1));
  enemy.setPosList(posList);
  this->_enemy.clear();
  this->_enemy.push_back(enemy);
}

/*
 * Protocol
 */

struct arcade::GetMap	*arcade::Centipede::getMap()
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
  return map;
}

struct arcade::WhereAmI 	*arcade::Centipede::getPlayer()
{
  struct arcade::WhereAmI	*player;

  if ((player = new arcade::WhereAmI[sizeof(arcade::WhereAmI) + (1 * sizeof(arcade::Position))]) == NULL)
    return NULL;
  player->type = arcade::CommandType::WHERE_AM_I;
  player->lenght = 1;
  player->position[0].x = this->_player.x;
  player->position[0].y = this->_player.y;
  return player;
}

void arcade::Centipede::setDirectionPlayer(arcade::AProtocol::MoveDirection move)
{
  this->_dir = move;
}

void 	arcade::Centipede::shoot()
{
  if (!this->_isFire)
    {
      this->_isFire = true;
      this->_shoot = this->_player;
      this->_soundPlay = 1;
    }
}

void 	arcade::Centipede::playProtocol()
{
  if (this->_enemy.empty())
    {
      CentipedeEnemy 	enemy;
      std::vector<Pos>	posList(5);

      posList[0] = Pos(1, 1);
      posList[1] = Pos(2, 1);
      posList[2] = Pos(3, 1);
      posList[3] = Pos(4, 1);
      posList[4] = Pos(5, 1);


      enemy.setDir(Pos(1, 1));
      enemy.setPosList(posList);
      this->_enemy.push_back(enemy);

      this->_nbKill += 1;
    }
  this->movePlayer(this->_dir, 1);
  this->moveCentipedeEnemy();
  this->checkFire();
  if (this->_nbKill == 10)
    this->reset();
}


// Protocol Play
extern "C" void Play(void)
{
  arcade::CommandType n;

  arcade::Centipede *game = new arcade::Centipede();
  while (std::cin.read(reinterpret_cast<char *>(&n), sizeof(n)))
    game->execAction(n);
  delete game;
};
