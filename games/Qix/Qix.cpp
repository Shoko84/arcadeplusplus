/*
** Qix.cpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/games/Qix
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Wed Apr 05 11:11:46 2017 cauvin-m
** Last update Sun Apr 09 21:41:57 2017 cauvin-m
*/

#include "Qix.hpp"

arcade::Qix::Qix()
{
  std::srand(time(NULL));
  this->_gameSize = Pos(41, 41 + 3);
  this->_level = 1;
  this->_sparks.push_back(Player(Pos(20, 0), Pos(-1, 0), StatusType::ENEMY));
  this->_sparks.push_back(Player(Pos(20, 0), Pos(1, 0), StatusType::ENEMY));
  this->resetKeysPressed();
  this->resetGame();
}

arcade::Qix::~Qix()
{

}

int         arcade::Qix::initGame(IGraphicLib *graphicLib, Score const& highScore)
{
  this->_highScore = highScore;
  this->_graphicLib = graphicLib;
  this->_assetsList = {{0, "qix_background.png"},
                       {1, "qix_border.png"},
                       {2, "qix_sparks.png"},
                       {3, "qix_nonWalkable.png"},
                       {4, "qix_qix.png"},
                       {5, "qix_player.png"},
                       {6, "qix_trail.png"}};
  graphicLib->addSprite(this->_assetsList[0], 0x000000, " ");
  graphicLib->addSprite(this->_assetsList[1], 0xffffff, " ");
  graphicLib->addSprite(this->_assetsList[2], 0xff0000, " ");
  graphicLib->addSprite(this->_assetsList[3], 0x500000, " ");
  graphicLib->addSprite(this->_assetsList[4], 0xff0000, " ");
  graphicLib->addSprite(this->_assetsList[5], 0xf2e800, " ");
  graphicLib->addSprite(this->_assetsList[6], 0x1897c6, " ");
  return (0);
}

void        arcade::Qix::resetGame()
{
  this->_player = Player(Pos(20, 40), Pos(0, 0), StatusType::ALLY);
  this->_cellTravelled = 0;
  this->_map.clear();
  this->_cellsToFill = 39 * 39;
  this->_cellsFilled = 0;
  this->_turns = 0;
  for (int i = 0; i < 41; i++)
  {
    if (i == 0 || i == 40)
      this->_map.push_back({1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1});
    else
      this->_map.push_back({1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1});
  }
  this->_qix = Pos(std::rand() % 39 + 1, std::rand() % 39 + 1);
  this->_sparks[0] = Player(Pos(20, 0), Pos(-1, 0), StatusType::ENEMY);
  this->_sparks[1] = Player(Pos(20, 0), Pos(1, 0), StatusType::ENEMY);
}

void        arcade::Qix::resetKeysPressed()
{
  this->_keysPressed = {{EventKeyBoard::EK_LEFT, false},
                        {EventKeyBoard::EK_RIGHT, false},
                        {EventKeyBoard::EK_UP, false},
                        {EventKeyBoard::EK_DOWN, false}};
}

bool        arcade::Qix::playerCanMove(Pos const& nextPos) const
{
  return (nextPos.y >= 0 && nextPos.y < (int)this->_map.size() &&
          nextPos.x >= 0 && nextPos.x < (int)this->_map[nextPos.x].size() &&
          this->_map[nextPos.y][nextPos.x] != 3 &&
          ((this->_map[nextPos.y][nextPos.x] != 6 && this->_map[nextPos.y][nextPos.x] != 1) ||
           (this->_map[nextPos.y][nextPos.x] == 1) ||
           (!this->_cellTravelled)));
}

void                arcade::Qix::differentiateFormInMap(std::vector<std::vector<int>> & map, Pos const& pos, int const& id) const
{
  if (map[pos.y][pos.x] == 0)
  {
    map[pos.y][pos.x] = id;
    if (pos.x - 1 > 0)
      this->differentiateFormInMap(map, Pos(pos.x - 1, pos.y), id);
    if (pos.y - 1 > 0)
      this->differentiateFormInMap(map, Pos(pos.x, pos.y - 1), id);
    if (pos.x < (int)map[pos.y].size() - 1)
      this->differentiateFormInMap(map, Pos(pos.x + 1, pos.y), id);
    if (pos.y < (int)map.size() - 1)
      this->differentiateFormInMap(map, Pos(pos.x, pos.y + 1), id);
  }
}

int          arcade::Qix::fillInForm(std::vector<std::vector<int>> const& map, int const& id)
{
  int        nbCells = 0;

  for (int i = 0; i < (int)map.size(); i++)
  {
    for (int j = 0; j < (int)map[i].size(); j++)
    {
      if (map[i][j] == 6)
      {
        this->_map[i][j] = 1;
        this->_cellsFilled += 1;
        nbCells += 1;
      }
      else if (map[i][j] != id && map[i][j] != 1 && map[i][j] != 3)
      {
        this->_map[i][j] = 3;
        this->_cellsFilled += 1;
        nbCells += 1;
      }
    }
  }
  return (nbCells);
}

void                arcade::Qix::findForms()
{
  std::vector<std::vector<int>> map = this->_map;
  int               id = 10;

  for (int i = 0; i < (int)map.size(); i++)
  {
    for (int j = 0; j < (int)map[i].size(); j++)
    {
      if (map[i][j] == 0)
      {
        this->differentiateFormInMap(map, Pos(j, i), id);
        id += 1;
      }
    }
  }
  this->setScore(std::to_string(std::stol(this->getScore()) + 4 * this->fillInForm(map, map[this->_qix.y][this->_qix.x]) * this->_level));
}

arcade::Pos       arcade::Qix::movePlayer()
{
  Pos       dir;

  if (this->_keysPressed[EventKeyBoard::EK_UP] &&
      this->playerCanMove(Pos(this->_player.getPos().x, this->_player.getPos().y - 1)))
    {
      this->_player.setPos(Pos(this->_player.getPos().x, this->_player.getPos().y - 1));
      dir = Pos(0, -1);
    }
  else if (this->_keysPressed[EventKeyBoard::EK_DOWN] &&
      this->playerCanMove(Pos(this->_player.getPos().x, this->_player.getPos().y + 1)))
    {
      this->_player.setPos(Pos(this->_player.getPos().x, this->_player.getPos().y + 1));
      dir = Pos(0, 1);
    }
  else if (this->_keysPressed[EventKeyBoard::EK_LEFT] &&
           this->playerCanMove(Pos(this->_player.getPos().x - 1, this->_player.getPos().y)))
    {
      this->_player.setPos(Pos(this->_player.getPos().x - 1, this->_player.getPos().y));
      dir = Pos(-1, 0);
    }
  else if (this->_keysPressed[EventKeyBoard::EK_RIGHT] &&
           this->playerCanMove(Pos(this->_player.getPos().x + 1, this->_player.getPos().y)))
    {
      this->_player.setPos(Pos(this->_player.getPos().x + 1, this->_player.getPos().y));
      dir = Pos(1, 0);
    }
  return (dir);
}

void        arcade::Qix::moveSparks()
{
  for (int i = 0; i < (int)this->_sparks.size(); i++)
  {
    if (this->_sparks[i].getPos().x + this->_sparks[i].getDir().x < 0 ||
        this->_sparks[i].getPos().y + this->_sparks[i].getDir().y < 0 ||
        this->_sparks[i].getPos().x + this->_sparks[i].getDir().x >= (int)this->_map[this->_sparks[i].getPos().y].size() ||
        this->_sparks[i].getPos().y + this->_sparks[i].getDir().y >= (int)this->_map.size() ||
        (this->_sparks[i].getPos().x > 0 && this->_sparks[i].getDir().x != -1 && (this->_map[this->_sparks[i].getPos().y][this->_sparks[i].getPos().x - 1] == 1 || this->_map[this->_sparks[i].getPos().y][this->_sparks[i].getPos().x - 1] == 6)) ||
        (this->_sparks[i].getPos().y > 0 && this->_sparks[i].getDir().y != -1 && (this->_map[this->_sparks[i].getPos().y - 1][this->_sparks[i].getPos().x] == 1 || this->_map[this->_sparks[i].getPos().y - 1][this->_sparks[i].getPos().x] == 6)) ||
        (this->_sparks[i].getPos().x < (int)this->_map[this->_sparks[i].getPos().y].size() - 1 && this->_sparks[i].getDir().x != 1 && (this->_map[this->_sparks[i].getPos().y][this->_sparks[i].getPos().x + 1] == 1 || this->_map[this->_sparks[i].getPos().y][this->_sparks[i].getPos().x + 1] == 6)) ||
        (this->_sparks[i].getPos().y < (int)this->_map.size() - 1 && this->_sparks[i].getDir().y != 1 && (this->_map[this->_sparks[i].getPos().y + 1][this->_sparks[i].getPos().x] == 1 || this->_map[this->_sparks[i].getPos().y + 1][this->_sparks[i].getPos().x] == 6)))
    {
      if (this->_sparks[i].getPos().y - 1 >= 0 &&
          this->_sparks[i].getDir().y != 1 &&
          (this->_map[this->_sparks[i].getPos().y - 1][this->_sparks[i].getPos().x] == 1 ||
           this->_map[this->_sparks[i].getPos().y - 1][this->_sparks[i].getPos().x] == 6))
        this->_sparks[i].setDir(Pos(0, -1));
      else if (this->_sparks[i].getPos().x + 1 < (int)this->_map[this->_sparks[i].getPos().y].size() &&
               this->_sparks[i].getDir().x != -1 &&
               (this->_map[this->_sparks[i].getPos().y][this->_sparks[i].getPos().x + 1] == 1 ||
                this->_map[this->_sparks[i].getPos().y][this->_sparks[i].getPos().x + 1] == 6))
        this->_sparks[i].setDir(Pos(1, 0));
      else if (this->_sparks[i].getPos().y + 1 < (int)this->_map.size() &&
               this->_sparks[i].getDir().y != -1 &&
               (this->_map[this->_sparks[i].getPos().y + 1][this->_sparks[i].getPos().x] == 1 ||
                this->_map[this->_sparks[i].getPos().y + 1][this->_sparks[i].getPos().x] == 6))
        this->_sparks[i].setDir(Pos(0, 1));
     else if (this->_sparks[i].getPos().x - 1 >= 0 &&
              this->_sparks[i].getDir().x != 1 &&
              (this->_map[this->_sparks[i].getPos().y][this->_sparks[i].getPos().x - 1] == 1 ||
               this->_map[this->_sparks[i].getPos().y][this->_sparks[i].getPos().x - 1] == 6))
        this->_sparks[i].setDir(Pos(-1, 0));
    }
    this->_sparks[i].setPos(Pos(this->_sparks[i].getPos().x + this->_sparks[i].getDir().x,
                                this->_sparks[i].getPos().y + this->_sparks[i].getDir().y));
  }
}

void        arcade::Qix::moveQix()
{
  int       coef;

  if (!(std::rand() % 2))
    coef = -1;
  else
    coef = 1;
  if (this->_map[this->_qix.y + 1 * coef][this->_qix.x + 1 * coef] != 1)
  {
    if (!(std::rand() % 2))
      this->_qix = Pos(this->_qix.x + 1 * coef, this->_qix.y);
    else
      this->_qix = Pos(this->_qix.x, this->_qix.y + 1 * coef);
  }
  else if (this->_qix.y - 1 >= 0 && !this->_map[this->_qix.y - 1][this->_qix.x])
    this->_qix = Pos(this->_qix.x, this->_qix.y - 1);
  else if (this->_qix.y + 1 < this->_map.size() && !this->_map[this->_qix.y + 1][this->_qix.x])
    this->_qix = Pos(this->_qix.x, this->_qix.y + 1);
  else if (this->_qix.x - 1 >= 0 && !this->_map[this->_qix.y][this->_qix.x - 1])
    this->_qix = Pos(this->_qix.x - 1, this->_qix.y);
  else if (this->_qix.x + 1 < this->_map[this->_qix.y].size() && !this->_map[this->_qix.y][this->_qix.x + 1])
    this->_qix = Pos(this->_qix.x + 1, this->_qix.y);
}

void        arcade::Qix::playerActions(Pos const& dir)
{
  if (!this->_map[this->_player.getPos().y][this->_player.getPos().x])
  {
    if (!this->_cellTravelled || this->_player.getDir().x != dir.x || this->_player.getDir().y != dir.y)
      this->_player.setDir(dir);
    this->_map[this->_player.getPos().y][this->_player.getPos().x] = 6;
    this->_cellTravelled += 1;
  }
  else if (this->_map[this->_player.getPos().y][this->_player.getPos().x] == 1)
  {
    if (this->_cellTravelled)
    {
      this->_graphicLib->p_sound("em_qix_filled.wav", arcade::SoundType::ST_SOUND);
      this->findForms();
    }
    this->_cellTravelled = 0;
  }
}

bool        arcade::Qix::hasCollidedWithTrail(Pos const& pos) const
{
  return (this->_map[pos.y][pos.x] == 6);
}

bool        arcade::Qix::hasCollidedWithPlayer(Player const& player, Pos const& pos) const
{
  return (pos.x == player.getPos().x && pos.y == player.getPos().y);
}

int         arcade::Qix::play()
{
  Pos       dir = this->movePlayer();

  if (this->hasCollidedWithTrail(this->_qix) ||
      this->hasCollidedWithPlayer(this->_player, this->_sparks[0].getPos()) ||
      this->hasCollidedWithPlayer(this->_player, this->_sparks[1].getPos()))
    this->setGameState(GameState::EXIT_ON_SUCCESS);
  if (!(this->_turns % 3))
  {
    this->moveQix();
    this->moveSparks();
  }
  if (this->hasCollidedWithTrail(this->_qix) ||
      this->hasCollidedWithPlayer(this->_player, this->_sparks[0].getPos()) ||
      this->hasCollidedWithPlayer(this->_player, this->_sparks[1].getPos()))
    this->setGameState(GameState::EXIT_ON_SUCCESS);
  this->resetKeysPressed();
  this->playerActions(dir);
  if (floor((float)this->_cellsFilled / (float)this->_cellsToFill * 100.0f) > 75)
    {
      this->_graphicLib->p_sound("em_qix_levelup.wav", arcade::SoundType::ST_SOUND);
      this->_level += 1;
      this->resetGame();
    }
  this->_turns += 1;
  return (0);
}

int         arcade::Qix::actionOfEvent(EventKeyBoard const& event)
{
  if (event == EventKeyBoard::EK_LEFT || event == EventKeyBoard::EK_RIGHT ||
      event == EventKeyBoard::EK_UP || event == EventKeyBoard::EK_DOWN)
    {
      this->resetKeysPressed();
      this->_keysPressed[event] = true;
    }
  return (0);
}

int         arcade::Qix::display(IGraphicLib *graphicLib)
{
  graphicLib->p_backGround("qix_background.png");
  graphicLib->p_text(Pos(1, 1), std::string("Score: " + this->getScore()), 0xf2e800, 12);
  graphicLib->p_text(Pos(12, 1), std::string("% filled: " + std::to_string((int)floor((float)this->_cellsFilled / (float)this->_cellsToFill * 100.0f))), 0xf2e800, 12);
  if (this->_highScore.name != "" && this->_highScore.score != "")
    graphicLib->p_text(Pos(24, 1), std::string("Highscore: " + this->_highScore.name + " " + this->_highScore.score), 0xf2e800, 12);
  else
    graphicLib->p_text(Pos(24, 1), "No highscores found.", 0xf2e800, 12);
  for (size_t i = 0; i < this->_map.size(); i++)
  {
    for (size_t j = 0; j < this->_map[i].size(); j++)
      graphicLib->p_cell(Pos(j, i + 3), this->_assetsList[this->_map[i][j]], 0);
  }
  for (int i = 0; i < (int)this->_sparks.size(); i++)
    graphicLib->p_cell(Pos(this->_sparks[i].getPos().x, this->_sparks[i].getPos().y + 3), this->_assetsList[2], 0);
  graphicLib->p_cell(Pos(this->_qix.x, this->_qix.y + 3), this->_assetsList[3], 0);
  graphicLib->p_cell(Pos(this->_player.getPos().x, this->_player.getPos().y + 3), this->_assetsList[5], 0);
  return (0);
}


extern "C" arcade::Qix   *CObject()
{
  std::cout << "Qix constructed" << std::endl;
  return (new arcade::Qix);
}

extern "C" void             DObject(arcade::Qix *obj)
{
    std::cout << "Qix destructed" << std::endl;
    delete obj;
}

/*
 * Protocol Funnctions
 */

// Protocol Play
extern "C" void Play(void)
{
  arcade::CommandType n;

  arcade::Qix *game = new arcade::Qix();
  while (std::cin.read(reinterpret_cast<char *>(&n), sizeof(n)))
    game->execAction(n);
  delete game;
};

struct arcade::GetMap	*arcade::Qix::getMap()
{
  struct arcade::GetMap	*map;

  if ((map = new arcade::GetMap[sizeof(arcade::GetMap) + (this->_map[0].size() * this->_map.size() * sizeof(arcade::TileType))]) == NULL)
    return NULL;
  map->type = arcade::CommandType::GET_MAP;
  map->height = this->_map.size();
  map->width = this->_map[0].size();
  for (int i = 0 ; i < map->height ; i++)
    {
      for (int j = 0 ; j < map->width ; j++)
	map->tile[(i * map->width) + j] = arcade::TileType::EMPTY;
    }
  return map;
}

struct arcade::WhereAmI 	*arcade::Qix::getPlayer()
{
  struct arcade::WhereAmI	*player;

  if ((player = new arcade::WhereAmI[sizeof(arcade::WhereAmI) + (1* sizeof(arcade::Position))]) == NULL)
    return NULL;
  player->type = arcade::CommandType::WHERE_AM_I;
  player->lenght = 1;
  player->position[0].x = this->_player.getPos().x;
  player->position[0].y = this->_player.getPos().y;
  return player;
}

void arcade::Qix::setDirectionPlayer(arcade::AProtocol::MoveDirection move)
{
  if (move == arcade::AProtocol::MoveDirection::LEFT)
    this->_player.setDir(Pos(-1, 0));
  else if (move == arcade::AProtocol::MoveDirection::RIGHT)
    this->_player.setDir(Pos(1, 0));
  else if (move == arcade::AProtocol::MoveDirection::UP)
    this->_player.setDir(Pos(0, -1));
  else if (move == arcade::AProtocol::MoveDirection::DOWN)
    this->_player.setDir(Pos(0, 1));
}

void arcade::Qix::shoot()
{
}

void 	arcade::Qix::playProtocol()
{
  this->play();
}
