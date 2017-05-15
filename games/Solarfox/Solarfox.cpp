/*
** Solarfox.cpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/games/Solarfox
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Sun Apr 02 02:23:31 2017 cauvin-m
** Last update Sun Apr 09 22:49:15 2017 cauvin-m
*/

#include "Solarfox.hpp"

arcade::Solarfox::Solarfox()
{
  this->_map =
  {
    {1, {
      {0, {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {8, 2}, {9, 2}, {10, 2}, {11, 2}, {12, 2}, {13, 2}, {14, 2}, {15, 2}, {16, 2}, {17, 2}, {18, 2}}},
      {1, {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {8, 2}, {9, 2}, {10, 2}, {11, 2}, {12, 2}, {13, 2}, {14, 2}, {15, 2}, {16, 2}, {17, 2}, {18, 2}}},
      {2, {{0, 2}, {1, 2}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 2}, {18, 2}}},
      {3, {{0, 2}, {1, 2}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 2}, {18, 2}}},
      {4, {{0, 2}, {1, 2}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 2}, {18, 2}}},
      {5, {{0, 2}, {1, 2}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 2}, {18, 2}}},
      {6, {{0, 2}, {1, 2}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 2}, {18, 2}}},
      {7, {{0, 2}, {1, 2}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {11, 1}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 2}, {18, 2}}},
      {8, {{0, 2}, {1, 2}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 1}, {8, 0}, {9, 0}, {10, 0}, {11, 1}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 2}, {18, 2}}},
      {9, {{0, 2}, {1, 2}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 1}, {8, 0}, {9, 3}, {10, 0}, {11, 1}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 2}, {18, 2}}},
      {10, {{0, 2}, {1, 2}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 1}, {8, 0}, {9, 0}, {10, 0}, {11, 1}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 2}, {18, 2}}},
      {11, {{0, 2}, {1, 2}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {11, 1}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 2}, {18, 2}}},
      {12, {{0, 2}, {1, 2}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 2}, {18, 2}}},
      {13, {{0, 2}, {1, 2}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 2}, {18, 2}}},
      {14, {{0, 2}, {1, 2}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 2}, {18, 2}}},
      {15, {{0, 2}, {1, 2}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 2}, {18, 2}}},
      {16, {{0, 2}, {1, 2}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 2}, {18, 2}}},
      {17, {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {8, 2}, {9, 2}, {10, 2}, {11, 2}, {12, 2}, {13, 2}, {14, 2}, {15, 2}, {16, 2}, {17, 2}, {18, 2}}},
      {18, {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {8, 2}, {9, 2}, {10, 2}, {11, 2}, {12, 2}, {13, 2}, {14, 2}, {15, 2}, {16, 2}, {17, 2}, {18, 2}}}
    }}
  };
  this->_powerupsList[1] = 16;

  //Trouver la map la plus grande ?
  this->_gameSize = this->loadSolarfoxMaps();
  this->_gameSize.y += 3;
  this->_level = 1;
  this->_curMap = this->_map[this->_level];
  this->_nbPowerups = this->_powerupsList[this->_level];
  this->_player.setPos(this->getPlayerPosInMap(this->_curMap));
  this->_player.setDir(Pos(0, 0));
  this->_player.setType(arcade::StatusType::ALLY);
  this->createEnemies();
  this->_turns = 0;
  this->_isPaused = false;
  this->_boost = 1;
  this->_playerHasMoved = false;
  std::srand(std::time(0));
}

arcade::Solarfox::~Solarfox()
{

}

void      arcade::Solarfox::createEnemies()
{
  this->_enemies.clear();
  this->_enemies.push_back(Player(Pos(this->_curMap[0].size() / 2, 0), Pos(1, 0), arcade::StatusType::ENEMY));
  this->_enemies.push_back(Player(Pos(this->_curMap[0].size() - 1, this->_curMap.size() / 2), Pos(0, 1), arcade::StatusType::ENEMY));
  this->_enemies.push_back(Player(Pos(this->_curMap[0].size() / 2, this->_curMap.size() - 1), Pos(-1, 0), arcade::StatusType::ENEMY));
  this->_enemies.push_back(Player(Pos(0, this->_curMap.size() / 2), Pos(0, -1), arcade::StatusType::ENEMY));
}

arcade::Pos       arcade::Solarfox::loadSolarfoxMaps()
{
  DIR                       *dir;
  struct dirent             *dirp;
  Pos                       highestSize(-1, -1);

  if ((dir = opendir("./Assets/Maps/Solarfox")))
  {
    while ((dirp = readdir(dir)))
    {
      std::string name = dirp->d_name;
      if (dirp->d_type == DT_REG && name.find("solarfox_level_") != std::string::npos && name.find(".txt") != std::string::npos &&
          name.find("solarfox_level_") == 0 && name.substr(name.find(".txt")) == ".txt")
        {
          std::string     levelStr = name.substr(name.find("solarfox_level_") +
                                                 std::string("solarfox_level_").length(),
                                                 name.find(".txt") - name.find("solarfox_level_") -
                                                 std::string("solarfox_level_").length());
          if (this->hasOnlyDigits(levelStr))
          {
            std::ifstream ifs("./Assets/Maps/Solarfox/" + name);
            std::string   line;
            int           nbPowerups = 0;
            Pos           curSize(-1, 0);
            int           level = std::stoi(levelStr);

            if (ifs)
            {
              std::map<int, std::map<int, int>>   map;
              int                                 i = 0;
              bool                                isMalformed = false;

              while (std::getline(ifs, line))
              {
                std::map<int, int>                map2;
                int                               lLen = 0;

                for (int j = 0; j < (int)line.length(); j++)
                {
                  map2[j] = std::stoi(line.substr(j, 1));
                  lLen += 1;
                  if (map2[j] == 1)
                    nbPowerups += 1;
                }
                if (curSize.x == -1)
                  curSize.x = lLen;
                else if (curSize.x != lLen)
                {
                  std::cerr << "The map './Assets/Maps/Solarfox/" << name << "' has different line lengths.." << std::endl;
                  isMalformed = true;
                  break;
                }
                map[i] = map2;
                curSize.y += 1;
                i += 1;
              }
              if (curSize.x < 5 || curSize.y < 5)
                isMalformed = true;
              if (curSize.x < 5)
                std::cerr << "The map './Assets/Maps/Solarfox/" << name << "' needs a minimal width of 5 cells." << std::endl;
              if (curSize.y < 5)
                std::cerr << "The map './Assets/Maps/Solarfox/" << name << "' needs a minimal height of 5 cells." << std::endl;
              if (!isMalformed)
              {
                this->_map[level] = map;
                this->_powerupsList[level] = nbPowerups;
                if (highestSize.x < curSize.x)
                  highestSize.x = curSize.x;
                if (highestSize.y < curSize.y)
                  highestSize.y = curSize.y;
              }
              else if (level == 1 && (highestSize.x == -1 || highestSize.y == -1))
                highestSize = Pos(19, 19);
              ifs.close();
            }
            else
              throw arcade::ArcadeError("There was an error while loading ./Assets/Maps/Solarfox/" + name);
          }
          else
            std::cerr << "The map './Assets/Maps/Solarfox/" << name << "' has an incorrect level name." << std::endl;
        }
    }
    closedir(dir);
  }
  if (highestSize.x == -1 || highestSize.y == -1)
    highestSize = Pos(19, 19);
  return (highestSize);
}

bool      arcade::Solarfox::playerHasCollidedWithBullet(Player const& player, StatusType const& type) const
{
  for (size_t i = 0; i < this->_shoots.size(); i++)
  {
    if (this->_shoots[i].getType() == type &&
        this->_shoots[i].getPos().x == player.getPos().x &&
        this->_shoots[i].getPos().y == player.getPos().y)
      return (true);
  }
  return (false);
}

arcade::Pos       arcade::Solarfox::getPlayerPosInMap(std::map<int, std::map<int, int>> map) const
{
  Pos     pos(-1, -1);

  for (int i = 0; i < (int)map.size(); i++)
    {
      for (int j = 0; j < (int)map[i].size(); j++)
        {
          if (map[i][j] == 3)
            {
              map[i][j] = 0;
              pos = Pos(j, i);
            }
          else if (map[i][j] == 0 && (pos.x == -1 || pos.y == -1))
            pos = Pos(j, i);
        }
    }
  if (pos.x == -1 || pos.y == -1)
    pos = Pos(0, 0);
  return (pos);
}

void      arcade::Solarfox::movePlayer()
{
  this->_player.setPos(Pos(this->_player.getPos().x + this->_player.getDir().x,
                       this->_player.getPos().y + this->_player.getDir().y));
  this->_playerHasMoved = true;
}

void      arcade::Solarfox::moveEnemies()
{
  for (size_t i = 0; i < this->_enemies.size(); i++)
  {
    this->_enemies[i].setPos(Pos(this->_enemies[i].getPos().x + this->_enemies[i].getDir().x,
                                 this->_enemies[i].getPos().y + this->_enemies[i].getDir().y));
  }
}

void      arcade::Solarfox::createEnemyShoots()
{
  if (!(std::rand() % 20))
    this->_shoots.push_back(Shoot(Pos(this->_enemies[0].getPos().x, this->_enemies[0].getPos().y + 1),
                                  Pos(0, 1), arcade::StatusType::ENEMY, this->_curMap.size() - 1));
  if (!(std::rand() % 20))
    this->_shoots.push_back(Shoot(Pos(this->_enemies[1].getPos().x, this->_enemies[1].getPos().y + 1),
                                  Pos(-1, 0), arcade::StatusType::ENEMY, this->_curMap.size() - 1));
  if (!(std::rand() % 20))
    this->_shoots.push_back(Shoot(Pos(this->_enemies[2].getPos().x, this->_enemies[2].getPos().y + 1),
                                  Pos(0, -1), arcade::StatusType::ENEMY, this->_curMap.size() - 1));
  if (!(std::rand() % 20))
    this->_shoots.push_back(Shoot(Pos(this->_enemies[3].getPos().x, this->_enemies[3].getPos().y + 1),
                                  Pos(1, 0), arcade::StatusType::ENEMY, this->_curMap.size() - 1));
}

void      arcade::Solarfox::resetEnemiesDirections()
{
  if (this->_enemies[0].getPos().x <= 0 || this->_enemies[0].getPos().x >= this->_curMap[0].size() - 1)
    this->_enemies[0].setDir(Pos(this->_enemies[0].getDir().x * -1, 0));
  if (this->_enemies[1].getPos().y <= 0 || this->_enemies[1].getPos().y >= this->_curMap.size() - 1)
    this->_enemies[1].setDir(Pos(0, this->_enemies[1].getDir().y * -1));
  if (this->_enemies[2].getPos().x <= 0 || this->_enemies[2].getPos().x >= this->_curMap[this->_curMap.size() - 1].size() - 1)
    this->_enemies[2].setDir(Pos(this->_enemies[2].getDir().x * -1, 0));
  if (this->_enemies[3].getPos().y <= 0 || this->_enemies[3].getPos().y >= this->_curMap.size() - 1)
    this->_enemies[3].setDir(Pos(0, this->_enemies[3].getDir().y * -1));
}

bool      arcade::Solarfox::powerupsHandler(Shoot const& shoot)
{
  if (shoot.getType() == arcade::StatusType::ALLY)
    {
      if (this->_curMap[shoot.getPos().y][shoot.getPos().x] == 1)
        {
          this->_curMap[shoot.getPos().y][shoot.getPos().x] = 0;
          this->_nbPowerups -= 1;
          this->setScore(std::to_string(std::stol(this->getScore()) + 100 * this->_level));
          if (this->_nbPowerups == 0)
            {
              this->_graphicLib->p_sound("em_solarfox_levelup.wav", arcade::SoundType::ST_SOUND);
              this->_player.setDir(Pos(0, 0));
              this->_level += 1;
              if (this->_map.find(this->_level) == this->_map.end())
                this->_level = 1;
              this->_nbPowerups = this->_powerupsList[this->_level];
              this->_curMap = this->_map[this->_level];
              this->_player.setPos(this->getPlayerPosInMap(this->_curMap));
              this->_shoots.clear();
              this->createEnemies();
              this->_turns = 0;
              return (true);
            }
        }
    }
  return (false);
}

void      arcade::Solarfox::breakingShoots(Shoot const& shoot)
{
  for (size_t i = 0; i < this->_shoots.size(); i++)
  {
    if (this->_shoots[i].getType() == StatusType::ENEMY &&
        this->_shoots[i].getPos().x == shoot.getPos().x &&
        this->_shoots[i].getPos().y == shoot.getPos().y)
    {
      this->setScore(std::to_string(std::stol(this->getScore()) + 20 * this->_level));
      this->_shoots.erase(this->_shoots.begin() + i);
    }
  }
}

void      arcade::Solarfox::moveShoots()
{
  for (size_t i = 0; i < this->_shoots.size(); i++)
  {
    if (this->_shoots[i].getType() == arcade::StatusType::ALLY ||
        (this->_shoots[i].getType() == arcade::StatusType::ENEMY && !(this->_turns % 3)))
      this->_shoots[i].setPos(Pos(this->_shoots[i].getPos().x + this->_shoots[i].getDir().x,
                                  this->_shoots[i].getPos().y + this->_shoots[i].getDir().y));
    if (this->_shoots[i].getPos().x < 0 || this->_shoots[i].getPos().y < 0 ||
        this->_shoots[i].getPos().y > this->_curMap.size() - 1 ||
        this->_shoots[i].getPos().x > this->_curMap[this->_shoots[i].getPos().y].size() - 1)
      this->_shoots.erase(this->_shoots.begin() + i);
    else
      {
        if (this->powerupsHandler(this->_shoots[i]))
          break;
        else if (this->_shoots[i].getType() == StatusType::ALLY)
          this->breakingShoots(this->_shoots[i]);
        if (this->_shoots[i].getType() == arcade::StatusType::ALLY ||
            (this->_shoots[i].getType() == arcade::StatusType::ENEMY && !(this->_turns % 3)))
          {
            this->_shoots[i].setLife(this->_shoots[i].getLife() - 1);
            if (this->_shoots[i].getLife() <= 0)
              this->_shoots.erase(this->_shoots.begin() + i);
          }
      }
  }
}

int       arcade::Solarfox::initGame(IGraphicLib *graphicLib, Score const& highScore)
{
  this->_highScore = highScore;
  this->_graphicLib = graphicLib;
  graphicLib->addSprite("solarfox_background.png", 0x000000, " ");
  graphicLib->addSprite("solarfox_bulletally.png", 0x00ff00, "-");
  graphicLib->addSprite("solarfox_bulletenemy.png", 0xfc6200, "-");
  graphicLib->addSprite("solarfox_character.png", 0xf2e800, "C");
  graphicLib->addSprite("solarfox_powerup.png", 0xffffff, "o");
  graphicLib->addSprite("solarfox_enemy.png", 0xff0000, "X");
  graphicLib->addSprite("solarfox_nonwalkable.png", 0x500000, " ");
  return (0);
}

int       arcade::Solarfox::play()
{
  if (!this->_isPaused)
  {
    if (!(this->_turns % (4 / this->_boost)))
    {
      this->_boost = 1;
      this->movePlayer();
      if (this->_player.getPos().x < 0 || this->_player.getPos().y < 0 ||
          this->_player.getPos().y >= (int)this->_curMap.size() ||
          this->_player.getPos().x >= (int)this->_curMap[this->_player.getPos().y].size() ||
          this->playerHasCollidedWithBullet(this->_player, arcade::StatusType::ENEMY) ||
          this->_curMap[this->_player.getPos().y][this->_player.getPos().x] == 2)
        this->setGameState(arcade::GameState::EXIT_ON_SUCCESS);
      if (!(this->_turns % 4))
      {
        this->moveEnemies();
        this->createEnemyShoots();
        this->resetEnemiesDirections();
      }
    }
    this->moveShoots();
    if (this->playerHasCollidedWithBullet(this->_player, arcade::StatusType::ENEMY))
      this->setGameState(arcade::GameState::EXIT_ON_SUCCESS);
    this->_turns += 1;
  }
  return (0);
}

int       arcade::Solarfox::actionOfEvent(EventKeyBoard const& event)
{
  Pos                       dir(0, 0);

  if (event == arcade::EventKeyBoard::EK_P)
    this->_isPaused = !this->_isPaused;
  if (!this->_isPaused)
  {
    if (event == arcade::EventKeyBoard::EK_LEFT && !this->_player.getDir().x &&
        this->_playerHasMoved)
      dir.x = -1;
    else if (event == arcade::EventKeyBoard::EK_RIGHT && !this->_player.getDir().x &&
            this->_playerHasMoved)
      dir.x = 1;
    else if (event == arcade::EventKeyBoard::EK_UP && !this->_player.getDir().y &&
            this->_playerHasMoved)
      dir.y = -1;
    else if (event == arcade::EventKeyBoard::EK_DOWN && !this->_player.getDir().y &&
            this->_playerHasMoved)
      dir.y = 1;
    if (dir.x || dir.y)
    {
      this->_player.setDir(dir);
      this->_playerHasMoved = false;
    }
    if (event == arcade::EventKeyBoard::EK_SPACE)
    {
      this->_graphicLib->p_sound("em_solarfox_shoot.wav", arcade::SoundType::ST_SOUND);
      this->_shoots.push_back(Shoot(Pos(this->_player.getPos().x + this->_player.getDir().x, this->_player.getPos().y + this->_player.getDir().y),
                                    Pos(this->_player.getDir().x, this->_player.getDir().y), arcade::StatusType::ALLY, 2));
    }
    else if (event == arcade::EventKeyBoard::EK_ENTER)
      this->_boost = 2;
  }
  return (0);
}

int       arcade::Solarfox::display(IGraphicLib *graphicLib)
{
  graphicLib->p_backGround("solarfox_background.png");
  graphicLib->p_text(Pos(1, 1), std::string("Score: " + this->getScore()), 0xf2e800, 12);
  if (this->_highScore.name != "" && this->_highScore.score != "")
    graphicLib->p_text(Pos(this->_gameSize.x - 15, 1), std::string("Highscore: " + this->_highScore.name + " " + this->_highScore.score), 0xf2e800, 12);
  else
    graphicLib->p_text(Pos(this->_gameSize.x - 15, 1), "No highscores found.", 0xf2e800, 12);
  for (int i = 0; i < (int)this->_curMap.size(); i++)
  {
    for (int j = 0; j < (int)this->_curMap[i].size(); j++)
    {
      if (this->_curMap[i][j] == 1)
        graphicLib->p_cell(Pos(j, i + 3), "solarfox_powerup.png", 0);
      else if (this->_curMap[i][j] == 2)
        graphicLib->p_cell(Pos(j, i + 3), "solarfox_nonwalkable.png", 0);
    }
  }
  for (int i = 0; i < (int)this->_enemies.size(); i++)
    graphicLib->p_cell(Pos(this->_enemies[i].getPos().x, this->_enemies[i].getPos().y + 3), "solarfox_enemy.png", 0);
  for (int i = 0; i < (int)this->_shoots.size(); i++)
  {
    if (this->_shoots[i].getType() == StatusType::ALLY)
      graphicLib->p_cell(Pos(this->_shoots[i].getPos().x, this->_shoots[i].getPos().y + 3), "solarfox_bulletally.png", 0);
    else if (this->_shoots[i].getType() == StatusType::ENEMY)
      graphicLib->p_cell(Pos(this->_shoots[i].getPos().x, this->_shoots[i].getPos().y + 3), "solarfox_bulletenemy.png", 0);
  }
  graphicLib->p_cell(Pos(this->_player.getPos().x, this->_player.getPos().y + 3), "solarfox_character.png", 0);
  return (0);
}

bool                arcade::Solarfox::hasOnlyDigits(std::string const& str) const
{
  return (str.find_first_not_of("0123456789") == std::string::npos);
}

extern "C" arcade::Solarfox   *CObject()
{
  std::cout << "Solarfox constructed" << std::endl;
  return (new arcade::Solarfox);
}

extern "C" void             DObject(arcade::Solarfox *obj)
{
    std::cout << "Solarfox destructed" << std::endl;
    delete obj;
}

/*
 * Protocol Funnctions
 */

// Protocol Play
extern "C" void Play(void)
{
  arcade::CommandType n;

  arcade::Solarfox *game = new arcade::Solarfox();
  while (std::cin.read(reinterpret_cast<char *>(&n), sizeof(n)))
    game->execAction(n);
  delete game;
};

struct arcade::GetMap	*arcade::Solarfox::getMap()
{
  struct arcade::GetMap	*map;

  if ((map = new arcade::GetMap[sizeof(arcade::GetMap) + (this->_curMap[0].size() * this->_curMap.size() * sizeof(arcade::TileType))]) == NULL)
    return NULL;
  map->type = arcade::CommandType::GET_MAP;
  map->height = this->_curMap.size();
  map->width = this->_curMap[0].size();
  for (int i = 0 ; i < map->height ; i++)
    {
      for (int j = 0 ; j < map->width ; j++)
	map->tile[(i * map->width) + j] = arcade::TileType::EMPTY;
    }
  for (auto it = this->_shoots.begin() ; it != this->_shoots.end() ; ++it)
    {
      if ((*it).getType() == arcade::StatusType::ALLY)
	map->tile[(int)((*it).getPos().y * map->width) + (int)(*it).getPos().x] = arcade::TileType::MY_SHOOT;
    }
  return map;
}

struct arcade::WhereAmI 	*arcade::Solarfox::getPlayer()
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

void arcade::Solarfox::setDirectionPlayer(arcade::AProtocol::MoveDirection move)
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

void arcade::Solarfox::shoot()
{
  this->_shoots.push_back(Shoot(Pos(this->_player.getPos().x + this->_player.getDir().x, this->_player.getPos().y + this->_player.getDir().y),
				Pos(this->_player.getDir().x, this->_player.getDir().y), arcade::StatusType::ALLY, 2));
}

void 	arcade::Solarfox::playProtocol()
{
  this->play();
  this->play();
  this->play();
  this->play();
}
