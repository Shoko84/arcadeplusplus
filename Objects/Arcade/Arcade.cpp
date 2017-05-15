/*
** Arcade.cpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Mon Mar 13 10:29:06 2017 cauvin-m
** Last update Sun Apr 09 22:27:07 2017 cauvin-m
*/

#include "Arcade.hpp"

arcade::Arcade::Arcade(std::string const& pathGraphLib)
{
  this->_programState = arcade::ProgramState::DEFAULT;
  this->_dlGraphicLib = nullptr;
  this->_graphicLib = nullptr;
  this->_menuState = arcade::MenuState::MENU_NAME;
  this->_dlGame = nullptr;
  this->_game = nullptr;
  this->_name = "AAA";
  this->_currentGraphicLibIdx = -1;
  this->refreshGameList();
  this->refreshGraphicLibList();
  this->refreshScoreList();
  for (int i = 0; i < (int)this->_graphicLibList.size(); i++)
  {
    if (pathGraphLib.find(this->_graphicLibList[i]) != std::string::npos)
      this->_currentGraphicLibIdx = i;
  }
  if (this->_currentGraphicLibIdx == -1)
  {
    if (this->fileExist(pathGraphLib))
      throw arcade::ArcadeError(std::string("The library '" + pathGraphLib + "' is not a graphic library.."));
    else
      throw arcade::ArcadeError(std::string("The library '" + pathGraphLib + "' was not found.."));
  }
}

arcade::Arcade::~Arcade()
{
  if (this->_dlGraphicLib)
  {
    this->_graphicLib->closeWin();
    delete this->_dlGraphicLib;
  }
  if (this->_dlGame)
    delete this->_dlGame;
}

arcade::Score arcade::Arcade::getHighscoreForGame(std::string const& gamename)
{
  this->refreshScoreList();
  for (auto it = this->_scoresList.begin(); it != this->_scoresList.end(); ++it)
  {
    if (std::string("arcade_score_" + gamename + ".txt") == (*it).first)
      return (Score((*(*it).second.rbegin()).second, std::to_string((*(*it).second.rbegin()).first)));
  }
  return (Score("", ""));
}

void                arcade::Arcade::pickNextGraphicLib(int const& nb)
{
  this->_currentGraphicLibIdx += nb;
  if (this->_currentGraphicLibIdx >= (int)this->_graphicLibList.size())
    this->_currentGraphicLibIdx = 0;
  else if (this->_currentGraphicLibIdx <= -1)
    this->_currentGraphicLibIdx = this->_graphicLibList.size() - 1;
  if (this->_dlGraphicLib)
  {
    this->_graphicLib->closeWin();
    delete this->_dlGraphicLib;
  }
  this->_dlGraphicLib = new arcade::DLLoader<IGraphicLib>("./lib/" + this->_graphicLibList[this->_currentGraphicLibIdx]);
  this->_graphicLib = this->_dlGraphicLib->getInstance();
}

void                arcade::Arcade::pickNextGame(int const& nb)
{
  this->_currentGameIdx += nb;
  if (this->_currentGameIdx <= -1)
    this->_currentGameIdx = this->_gamesList.size() - 1;
  else if (this->_currentGameIdx >= (int)this->_gamesList.size())
    this->_currentGameIdx = 0;
  if (this->_dlGame)
    delete this->_dlGame;
  this->_dlGame = new arcade::DLLoader<IGame>("./games/" + this->_gamesList[this->_currentGameIdx]);
  this->_game = this->_dlGame->getInstance();
}

void                arcade::Arcade::refreshGameList()
{
  DIR                   *dir;
  struct dirent         *dirp;

  this->_gamesList.clear();
  if ((dir = opendir("./games/")))
  {
    while ((dirp = readdir(dir)))
    {
      std::string name = dirp->d_name;
      if (dirp->d_type == DT_REG && name.find("lib_arcade_") != std::string::npos && name.find(".so") != std::string::npos &&
          name.find("lib_arcade_") == 0 && name.substr(name.find(".so")) == ".so")
        this->_gamesList.push_back(name);
    }
    closedir(dir);
  }
  else
    throw arcade::ArcadeError("Could not open './games' folder");
}

void                arcade::Arcade::refreshGraphicLibList()
{
  DIR                   *dir;
  struct dirent         *dirp;

  this->_graphicLibList.clear();
  if ((dir = opendir("./lib/")))
  {
    while ((dirp = readdir(dir)))
    {
      std::string name = dirp->d_name;
      if (dirp->d_type == DT_REG && name.find("lib_arcade_") != std::string::npos && name.find(".so") != std::string::npos &&
          name.find("lib_arcade_") == 0 && name.substr(name.find(".so")) == ".so")
        this->_graphicLibList.push_back(name);
    }
    closedir(dir);
  }
  else
    throw arcade::ArcadeError("Could not open './lib' folder");
}

void                arcade::Arcade::refreshScoreList()
{
  DIR             *dir;
  struct dirent   *dirp;

  this->_scoresList.clear();
  if ((dir = opendir("./scoring/")))
  {
    while ((dirp = readdir(dir)))
    {
      std::string                             name = dirp->d_name;
      std::pair<std::string, std::map<size_t, std::string>> scores;

      if (dirp->d_type == DT_REG && name.find("arcade_score_") != std::string::npos && name.find(".txt") != std::string::npos &&
          name.find("arcade_score_") == 0 && name.substr(name.find(".txt")) == ".txt")
        {
          std::ifstream ifs("./scoring/" + name);
          std::string   score;
          std::string   playerName;
          bool          goodFile = true;
          if (ifs)
          {
            while (ifs >> playerName && goodFile)
            {
              if (ifs >> score)
              {
                scores.first = name;
                if (!this->hasOnlyDigits(score) || !this->hasOnlyLetters(playerName) || std::stol(score) <= 0)
                  goodFile = false;
                else
                  scores.second[std::stol(score)] = playerName;
              }
              else
                goodFile = false;
            }
            if (goodFile)
              this->_scoresList.push_back(scores);
            ifs.close();
          }
          else
            throw arcade::ArcadeError("Error while opening '" + name + "' scoring file");
        }
    }
    closedir(dir);
  }
  else
    std::cerr << "Could not open './scoring' folder" << std::endl;
}

bool                arcade::Arcade::fileExist(std::string const& filepath) const
{
  std::ifstream      ifs(filepath);
  bool               doesExist;

  doesExist = ifs.good();
  ifs.close();
  return (doesExist);
}

bool                arcade::Arcade::hasOnlyDigits(std::string const& str) const
{
  return (str.find_first_not_of("0123456789") == std::string::npos);
}

bool                arcade::Arcade::hasOnlyLetters(std::string const& str) const
{
  return (str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos);
}

void                arcade::Arcade::printScoreInFile(std::string const& score) const
{
  if (score != "0")
  {
    std::ofstream     ofs;
    std::string       gameName = this->_gamesList[this->_currentGameIdx];
    std::string       truncGameName = gameName.substr(std::string("lib_arcade_").length(),
                                                      gameName.find(".so") - std::string("lib_arcade_").length());
    std::string       sep;

    if (this->fileExist("./scoring/arcade_score_" + truncGameName + ".txt"))
      sep = "\n";
    ofs.open("./scoring/arcade_score_" + truncGameName + ".txt", std::ios::app);
    ofs << sep << this->_name << "\t" << score;
    ofs.close();
  }
}

void  arcade::Arcade::displayMenuName(char const& charSelected, bool const& fade) const
{
  this->_graphicLib->p_hLine(Pos(0, 0), 44, "borderMenuColor", 0);
  this->_graphicLib->p_hLine(Pos(0, 33), 45, "borderMenuColor", 0);
  this->_graphicLib->p_vLine(Pos(0, 0), 33, "borderMenuColor", 0);
  this->_graphicLib->p_vLine(Pos(44, 0), 33, "borderMenuColor", 0);
  this->_graphicLib->p_text(Pos(19, 8), "Welcome", 0xf2e800, 24);
  this->_graphicLib->p_text(Pos(15, 11), "Please select your name", 0xf2e800, 14);
  if (!fade || charSelected != 0)
    this->_graphicLib->p_text(Pos(20.5, 17), this->_name.substr(0, 1), 0xf2e800, 30);
  if (!fade || charSelected != 1)
    this->_graphicLib->p_text(Pos(22.5, 17), this->_name.substr(1, 1), 0xf2e800, 30);
  if (!fade || charSelected != 2)
    this->_graphicLib->p_text(Pos(24.5, 17), this->_name.substr(2, 1), 0xf2e800, 30);
  this->_graphicLib->p_text(Pos(15.5, 29.5), "Press ENTER to confirm", 0xf2e800, 14);
}

void  arcade::Arcade::displayMenuGame(char const& gameSelected, bool const& fade) const
{
  int i = 0;

  this->_graphicLib->p_hLine(Pos(0, 0), 44, "borderMenuColor", 0);
  this->_graphicLib->p_hLine(Pos(0, 33), 45, "borderMenuColor", 0);
  this->_graphicLib->p_vLine(Pos(0, 0), 33, "borderMenuColor", 0);
  this->_graphicLib->p_vLine(Pos(44, 0), 33, "borderMenuColor", 0);
  this->_graphicLib->p_text(Pos(15, 4), "Please select a game:", 0xf2e800, 16);
  if (this->_gamesList.size() >= 1)
  {
    for (auto it = this->_gamesList.begin(); it != this->_gamesList.end(); ++it, i++)
    {
      if (!fade || gameSelected != i)
        this->_graphicLib->p_text(Pos(6, 8 + i), (*it).substr(11, (*it).find(".so") - 11), 0xf2e800, 12);
    }
    this->_graphicLib->p_text(Pos(28.5, 29.5), "Press ENTER to confirm", 0xf2e800, 11);
  }
  else
    this->_graphicLib->p_text(Pos(6, 8), "No games found", 0xf2e800, 12);
  this->_graphicLib->p_text(Pos(5, 29.5), "Press BACKSPACE to go back", 0xf2e800, 11);
}

void  arcade::Arcade::displayMenuLib(char const& libSelected, bool const& fade) const
{
  int i = 0;

  this->_graphicLib->p_hLine(Pos(0, 0), 44, "borderMenuColor", 0);
  this->_graphicLib->p_hLine(Pos(0, 33), 45, "borderMenuColor", 0);
  this->_graphicLib->p_vLine(Pos(0, 0), 33, "borderMenuColor", 0);
  this->_graphicLib->p_vLine(Pos(44, 0), 33, "borderMenuColor", 0);
  this->_graphicLib->p_text(Pos(10.5, 4), "Please select a graphic library:", 0xf2e800, 16);
  if (this->_graphicLibList.size() >= 1)
  {
    for (auto it = this->_graphicLibList.begin(); it != this->_graphicLibList.end(); ++it, i++)
    {
      if (!fade || libSelected != i)
        this->_graphicLib->p_text(Pos(6, 8 + i), (*it).substr(11, (*it).find(".so") - 11), 0xf2e800, 12);
    }
    this->_graphicLib->p_text(Pos(29, 28.25), "Press ENTER to start", 0xf2e800, 11);
  }
  else
    this->_graphicLib->p_text(Pos(6, 8), "No graphic libraries found", 0xf2e800, 12);
  this->_graphicLib->p_text(Pos(5, 28.25), "Press BACKSPACE to go back", 0xf2e800, 11);
  this->_graphicLib->p_text(Pos(13, 30.5), "Press SPACE to display leaderboards", 0xf2e800, 11);
}

void  arcade::Arcade::displayMenuLeaderboard(char const& gameSelected) const
{
  int i = 0;

  this->_graphicLib->p_hLine(Pos(0, 0), 44, "borderMenuColor", 0);
  this->_graphicLib->p_hLine(Pos(0, 33), 45, "borderMenuColor", 0);
  this->_graphicLib->p_vLine(Pos(0, 0), 33, "borderMenuColor", 0);
  this->_graphicLib->p_vLine(Pos(44, 0), 33, "borderMenuColor", 0);
  this->_graphicLib->p_text(Pos(19, 4), "Leaderboard:", 0xf2e800, 16);
  if (this->_scoresList.size() >= 1)
  {
    this->_graphicLib->p_text(Pos(20.5, 7.5), "< " + this->_scoresList[gameSelected].first.substr(std::string("arcade_score_").length(), this->_scoresList[gameSelected].first.find(".txt") - std::string("arcade_score_").length()) + " >", 0xf2e800, 14);
    for (auto it = this->_scoresList[gameSelected].second.rbegin(); it != this->_scoresList[gameSelected].second.rend(); ++it, i++)
    {
      this->_graphicLib->p_text(Pos(20, 11 + (i * 2)), (*it).second, 0xf2e800, 16);
      this->_graphicLib->p_text(Pos(24, 11 + (i * 2)), std::to_string((*it).first), 0xf2e800, 16);
    }
  }
  else
    this->_graphicLib->p_text(Pos(19, 10), "No scores found", 0xf2e800, 12);
  this->_graphicLib->p_text(Pos(14, 29.5), "Press BACKSPACE to go back", 0xf2e800, 14);
}

void  arcade::Arcade::menuNameEvents(std::clock_t & c_fade, char & charSelected, bool & fade)
{
  arcade::EventKeyBoard keyP = this->_graphicLib->getEvent();

  if (keyP != arcade::EventKeyBoard::EK_DEFAULT)
    this->_graphicLib->p_sound("em_selectmenu.ogg", arcade::SoundType::ST_SOUND);
  if (keyP == arcade::EventKeyBoard::EK_ESCAPE)
    this->_programState = arcade::ProgramState::EXIT_ON_SUCCESS;
  else if (keyP == arcade::EventKeyBoard::EK_NUMPAD2)
  {
    this->refreshGraphicLibList();
    if (this->_graphicLibList.size() > 1)
    {
      this->pickNextGraphicLib(-1);
      this->_graphicLib->initWin();
      this->_graphicLib->openWin(Pos(45, 34));
      this->_graphicLib->addSprite("borderMenuColor", 0xf2e800, " ");
    }
  }
  else if (keyP == arcade::EventKeyBoard::EK_NUMPAD3)
  {
    this->refreshGraphicLibList();
    if (this->_graphicLibList.size() > 1)
    {
      this->pickNextGraphicLib(1);
      this->_graphicLib->initWin();
      this->_graphicLib->openWin(Pos(45, 34));
      this->_graphicLib->addSprite("borderMenuColor", 0xf2e800, " ");
    }
  }
  else if (keyP == arcade::EventKeyBoard::EK_NUMPAD9)
    this->_menuState = arcade::MenuState::MENU_NAME;
  else if (keyP == arcade::EventKeyBoard::EK_RIGHT)
  {
    charSelected += 1;
    if (charSelected >= (char)this->_name.length())
      charSelected = 0;
    c_fade = std::clock();
    fade = false;
  }
  else if (keyP == arcade::EventKeyBoard::EK_LEFT)
  {
    charSelected -= 1;
    if (charSelected <= -1)
      charSelected = 2;
    c_fade = std::clock();
    fade = false;
  }
  else if (keyP == arcade::EventKeyBoard::EK_UP)
  {
    this->_name[charSelected] += 1;
    if (this->_name[charSelected] > 'Z')
      this->_name[charSelected] = 'A';
  }
  else if (keyP == arcade::EventKeyBoard::EK_DOWN)
  {
    this->_name[charSelected] -= 1;
    if (this->_name[charSelected] < 'A')
      this->_name[charSelected] = 'Z';
  }
  else if (keyP == arcade::EventKeyBoard::EK_ENTER)
  {
    charSelected = 0;
    c_fade = std::clock();
    fade = false;
    this->refreshGameList();
    this->_menuState = arcade::MenuState::GAME_SELECT;
  }
}

void  arcade::Arcade::menuGameEvents(std::clock_t & c_fade, char & gameSelected, bool & fade)
{
  arcade::EventKeyBoard keyP = this->_graphicLib->getEvent();

  if (keyP != arcade::EventKeyBoard::EK_DEFAULT)
    this->_graphicLib->p_sound("em_selectmenu.ogg", arcade::SoundType::ST_SOUND);
  if (keyP == arcade::EventKeyBoard::EK_ESCAPE)
    this->_programState = arcade::ProgramState::EXIT_ON_SUCCESS;
  else if (keyP == arcade::EventKeyBoard::EK_NUMPAD2)
  {
    this->refreshGraphicLibList();
    if (this->_graphicLibList.size() > 1)
    {
      this->pickNextGraphicLib(-1);
      this->_graphicLib->initWin();
      this->_graphicLib->openWin(Pos(45, 34));
      this->_graphicLib->addSprite("borderMenuColor", 0xf2e800, " ");
    }
  }
  else if (keyP == arcade::EventKeyBoard::EK_NUMPAD3)
  {
    this->refreshGraphicLibList();
    if (this->_graphicLibList.size() > 1)
    {
      this->pickNextGraphicLib(1);
      this->_graphicLib->initWin();
      this->_graphicLib->openWin(Pos(45, 34));
      this->_graphicLib->addSprite("borderMenuColor", 0xf2e800, " ");
    }
  }
  else if (keyP == arcade::EventKeyBoard::EK_NUMPAD9)
    this->_menuState = arcade::MenuState::MENU_NAME;
  else if (keyP == arcade::EventKeyBoard::EK_BACKSPACE)
  {
    this->_menuState = arcade::MenuState::MENU_NAME;
    gameSelected = 0;
    c_fade = std::clock();
    fade = false;
  }
  else if (keyP == arcade::EventKeyBoard::EK_UP)
  {
    gameSelected -= 1;
    if (gameSelected <= -1)
      gameSelected = this->_gamesList.size() - 1;
    c_fade = std::clock();
    fade = false;
  }
  else if (keyP == arcade::EventKeyBoard::EK_DOWN)
  {
    gameSelected += 1;
    if ((size_t)gameSelected >= this->_gamesList.size())
      gameSelected = 0;
    c_fade = std::clock();
    fade = false;
  }
  else if (this->_gamesList.size() > 0 && keyP == arcade::EventKeyBoard::EK_ENTER)
  {
    c_fade = std::clock();
    fade = false;
    this->_currentGameIdx = gameSelected;
    gameSelected = 0;
    this->refreshGraphicLibList();
    this->_menuState = arcade::MenuState::LIB_SELECT;
  }
}

void  arcade::Arcade::menuLibEvents(std::clock_t & c_fade, char & libSelected, bool & fade)
{
  arcade::EventKeyBoard keyP = this->_graphicLib->getEvent();

  if (keyP != arcade::EventKeyBoard::EK_DEFAULT)
    this->_graphicLib->p_sound("em_selectmenu.ogg", arcade::SoundType::ST_SOUND);
  if (keyP == arcade::EventKeyBoard::EK_ESCAPE)
    this->_programState = arcade::ProgramState::EXIT_ON_SUCCESS;
  else if (keyP == arcade::EventKeyBoard::EK_NUMPAD2)
  {
    this->refreshGraphicLibList();
    if (this->_graphicLibList.size() > 1)
    {
      this->pickNextGraphicLib(-1);
      this->_graphicLib->initWin();
      this->_graphicLib->openWin(Pos(45, 34));
      this->_graphicLib->addSprite("borderMenuColor", 0xf2e800, " ");
    }
  }
  else if (keyP == arcade::EventKeyBoard::EK_NUMPAD3)
  {
    this->refreshGraphicLibList();
    if (this->_graphicLibList.size() > 1)
    {
      this->pickNextGraphicLib(1);
      this->_graphicLib->initWin();
      this->_graphicLib->openWin(Pos(45, 34));
      this->_graphicLib->addSprite("borderMenuColor", 0xf2e800, " ");
    }
  }
  else if (keyP == arcade::EventKeyBoard::EK_NUMPAD9)
    this->_menuState = arcade::MenuState::MENU_NAME;
  else if (keyP == arcade::EventKeyBoard::EK_BACKSPACE)
  {
    this->_menuState = arcade::MenuState::GAME_SELECT;
    libSelected = 0;
    c_fade = std::clock();
    fade = false;
  }
  else if (keyP == arcade::EventKeyBoard::EK_UP)
  {
    libSelected -= 1;
    if (libSelected <= -1)
      libSelected = this->_graphicLibList.size() - 1;
    c_fade = std::clock();
    fade = false;
  }
  else if (keyP == arcade::EventKeyBoard::EK_DOWN)
  {
    libSelected += 1;
    if ((size_t)libSelected >= this->_graphicLibList.size())
      libSelected = 0;
    c_fade = std::clock();
    fade = false;
  }
  else if (keyP == arcade::EventKeyBoard::EK_SPACE)
  {
    this->refreshScoreList();
    libSelected = 0;
    this->_menuState = arcade::MenuState::LEADERBOARD;
  }
  else if (this->_graphicLibList.size() > 0 && keyP == arcade::EventKeyBoard::EK_ENTER)
  {
    c_fade = std::clock();
    fade = false;
    this->_currentGraphicLibIdx = libSelected;
    libSelected = 0;
    if (this->_dlGraphicLib)
    {
      this->_graphicLib->closeWin();
      delete this->_dlGraphicLib;
    }
    this->_dlGame = new arcade::DLLoader<IGame>("./games/" + this->_gamesList[this->_currentGameIdx]);
    this->_dlGraphicLib = new arcade::DLLoader<IGraphicLib>("./lib/" + this->_graphicLibList[this->_currentGraphicLibIdx]);
    this->_graphicLib = this->_dlGraphicLib->getInstance();
    this->_game = this->_dlGame->getInstance();
    this->_game->setGameState(arcade::GameState::RUN);
  }
}

void  arcade::Arcade::menuLeaderboardEvents(char & gameSelected)
{
  arcade::EventKeyBoard keyP = this->_graphicLib->getEvent();

  if (keyP != arcade::EventKeyBoard::EK_DEFAULT)
    this->_graphicLib->p_sound("em_selectmenu.ogg", arcade::SoundType::ST_SOUND);
  if (keyP == arcade::EventKeyBoard::EK_ESCAPE)
    this->_programState = arcade::ProgramState::EXIT_ON_SUCCESS;
  else if (keyP == arcade::EventKeyBoard::EK_BACKSPACE)
  {
    this->_menuState = arcade::MenuState::LIB_SELECT;
    gameSelected = 0;
  }
  else if (keyP == arcade::EventKeyBoard::EK_NUMPAD2)
  {
    this->refreshGraphicLibList();
    if (this->_graphicLibList.size() > 1)
    {
      this->pickNextGraphicLib(-1);
      this->_graphicLib->initWin();
      this->_graphicLib->openWin(Pos(45, 34));
      this->_graphicLib->addSprite("borderMenuColor", 0xf2e800, " ");
    }
  }
  else if (keyP == arcade::EventKeyBoard::EK_NUMPAD3)
  {
    this->refreshGraphicLibList();
    if (this->_graphicLibList.size() > 1)
    {
      this->pickNextGraphicLib(1);
      this->_graphicLib->initWin();
      this->_graphicLib->openWin(Pos(45, 34));
      this->_graphicLib->addSprite("borderMenuColor", 0xf2e800, " ");
    }
  }
  else if (keyP == arcade::EventKeyBoard::EK_NUMPAD9)
    this->_menuState = arcade::MenuState::MENU_NAME;
  else if (keyP == arcade::EventKeyBoard::EK_RIGHT)
  {
    gameSelected += 1;
    if (gameSelected >= (char)this->_scoresList.size())
      gameSelected = 0;
  }
  else if (keyP == arcade::EventKeyBoard::EK_LEFT)
  {
    gameSelected -= 1;
    if (gameSelected <= -1)
      gameSelected = this->_scoresList.size() - 1;
  }
}

void  arcade::Arcade::menuHandler()
{
  std::clock_t      c_start = std::clock();
  std::clock_t      c_fade = std::clock();
  char              selected = 0;
  bool              fade = false;

  if (this->_dlGraphicLib)
  {
    this->_graphicLib->closeWin();
    delete this->_dlGraphicLib;
  }
  this->_dlGraphicLib = new arcade::DLLoader<IGraphicLib>("./lib/" + this->_graphicLibList[this->_currentGraphicLibIdx]);
  this->_graphicLib = this->_dlGraphicLib->getInstance();
  this->_graphicLib->initWin();
  this->_graphicLib->openWin(Pos(45, 34));
  this->_graphicLib->addSprite("borderMenuColor", 0xf2e800, " ");
  while (!this->_game && this->_programState != arcade::ProgramState::EXIT_ON_SUCCESS &&
         this->_programState != arcade::ProgramState::EXIT_ON_ERROR)
    {
      if (this->_menuState == arcade::MenuState::MENU_NAME)
        this->menuNameEvents(c_fade, selected, fade);
      else if (this->_menuState == arcade::MenuState::GAME_SELECT)
        this->menuGameEvents(c_fade, selected, fade);
      else if (this->_menuState == arcade::MenuState::LIB_SELECT)
        this->menuLibEvents(c_fade, selected, fade);
      else if (this->_menuState == arcade::MenuState::LEADERBOARD)
        this->menuLeaderboardEvents(selected);
      if (this->_game)
        break;
      if (std::clock() - c_fade >= ONE_SEC / 2.5)
      {
        fade = !fade;
        c_fade = std::clock();
      }
      if (std::clock() - c_start >= ONE_SEC / 60)
        {
          this->_graphicLib->clearWin();
          if (this->_menuState == arcade::MenuState::MENU_NAME)
            this->displayMenuName(selected, fade);
          else if (this->_menuState == arcade::MenuState::GAME_SELECT)
            this->displayMenuGame(selected, fade);
          else if (this->_menuState == arcade::MenuState::LIB_SELECT)
            this->displayMenuLib(selected, fade);
          else if (this->_menuState == arcade::MenuState::LEADERBOARD)
            this->displayMenuLeaderboard(selected);
          this->_graphicLib->refreshWin();
          c_start = std::clock();
        }
    }
}

void                arcade::Arcade::gameHandler()
{
  std::clock_t      c_start = std::clock();
  int               nbFrames = 0;
  std::clock_t      previous = std::clock();
  std::clock_t      lag = 0.0;

  this->_game->initGame(this->_graphicLib, getHighscoreForGame(this->_gamesList[this->_currentGameIdx].substr(11, this->_gamesList[this->_currentGameIdx].find(".so") - 11)));
  this->_graphicLib->initWin();
  this->_graphicLib->openWin(this->_game->getGameSize());
  while (this->_game->getGameState() != GameState::EXIT_ON_SUCCESS &&
         this->_game->getGameState() != GameState::EXIT_ON_ERROR)
    {
      std::clock_t  current = std::clock();
      std::clock_t  elapsed = current - previous;
      arcade::EventKeyBoard keyP = this->_graphicLib->getEvent();
      previous = current;
      lag += elapsed;

      if (keyP == arcade::EventKeyBoard::EK_ESCAPE)
      {
        this->_game->setGameState(arcade::GameState::EXIT_ON_SUCCESS);
        this->_programState = arcade::ProgramState::EXIT_ON_SUCCESS;
        break;
      }
      else if (keyP == arcade::EventKeyBoard::EK_NUMPAD2)
      {
        this->refreshGraphicLibList();
        if (this->_graphicLibList.size() > 1)
        {
          this->pickNextGraphicLib(-1);
          this->_game->initGame(this->_graphicLib, getHighscoreForGame(this->_gamesList[this->_currentGameIdx].substr(11, this->_gamesList[this->_currentGameIdx].find(".so") - 11)));
          this->_graphicLib->initWin();
          this->_graphicLib->openWin(this->_game->getGameSize());
        }
      }
      else if (keyP == arcade::EventKeyBoard::EK_NUMPAD3)
      {
        this->refreshGraphicLibList();
        if (this->_graphicLibList.size() > 1)
        {
          this->pickNextGraphicLib(1);
          this->_game->initGame(this->_graphicLib, getHighscoreForGame(this->_gamesList[this->_currentGameIdx].substr(11, this->_gamesList[this->_currentGameIdx].find(".so") - 11)));
          this->_graphicLib->initWin();
          this->_graphicLib->openWin(this->_game->getGameSize());
        }
      }
      else if (keyP == arcade::EventKeyBoard::EK_NUMPAD4)
      {
        this->refreshGameList();
        if (this->_dlGraphicLib)
        {
          this->_graphicLib->closeWin();
          delete this->_dlGraphicLib;
        }
        this->_dlGraphicLib = new arcade::DLLoader<IGraphicLib>("./lib/" + this->_graphicLibList[this->_currentGraphicLibIdx]);
        this->_graphicLib = this->_dlGraphicLib->getInstance();
        if (this->_gamesList.size() > 1)
        {
          this->pickNextGame(-1);
          this->_game->initGame(this->_graphicLib, getHighscoreForGame(this->_gamesList[this->_currentGameIdx].substr(11, this->_gamesList[this->_currentGameIdx].find(".so") - 11)));
          this->_graphicLib->initWin();
          this->_graphicLib->openWin(this->_game->getGameSize());
        }
      }
      else if (keyP == arcade::EventKeyBoard::EK_NUMPAD5)
      {
        this->refreshGameList();
        if (this->_dlGraphicLib)
        {
          this->_graphicLib->closeWin();
          delete this->_dlGraphicLib;
        }
        this->_dlGraphicLib = new arcade::DLLoader<IGraphicLib>("./lib/" + this->_graphicLibList[this->_currentGraphicLibIdx]);
        this->_graphicLib = this->_dlGraphicLib->getInstance();
        if (this->_gamesList.size() > 1)
        {
          this->pickNextGame(1);
          this->_game->initGame(this->_graphicLib, getHighscoreForGame(this->_gamesList[this->_currentGameIdx].substr(11, this->_gamesList[this->_currentGameIdx].find(".so") - 11)));
          this->_graphicLib->initWin();
          this->_graphicLib->openWin(this->_game->getGameSize());
        }
      }
      else if (keyP == arcade::EventKeyBoard::EK_NUMPAD8)
      {
        this->refreshGameList();
        if (this->_gamesList.size() > 1)
        {
          if (this->_dlGame)
            delete this->_dlGame;
          this->_dlGame = new arcade::DLLoader<IGame>("./games/" + this->_gamesList[this->_currentGameIdx]);
          this->_game = this->_dlGame->getInstance();
          this->_game->initGame(this->_graphicLib, getHighscoreForGame(this->_gamesList[this->_currentGameIdx].substr(11, this->_gamesList[this->_currentGameIdx].find(".so") - 11)));
        }
      }
      else if (keyP == arcade::EventKeyBoard::EK_NUMPAD9)
      {
        this->_game->setGameState(arcade::GameState::EXIT_ON_SUCCESS);
        this->_menuState = arcade::MenuState::GAME_SELECT;
        break;
      }
      this->_game->actionOfEvent(keyP);
      while (lag >= MS_PER_UPDATE)
        {
          this->_game->play();
          lag -= MS_PER_UPDATE;
        }
      if ((std::clock() - c_start) >= (unsigned int)(ONE_SEC / this->_game->getFps()))
        {
          this->_graphicLib->clearWin();
          this->_game->display(this->_graphicLib);
          this->_graphicLib->refreshWin();
          nbFrames++;
          c_start = std::clock();
        }
    }
  std::cout << "Score: " << this->_game->getScore() << std::endl;
  this->printScoreInFile(this->_game->getScore());
  if (this->_dlGame)
    delete this->_dlGame;
  this->_dlGame = nullptr;
  this->_game = nullptr;
  this->_menuState = arcade::MenuState::GAME_SELECT;
}

int                 arcade::Arcade::mainLoop()
{
  this->_programState = arcade::ProgramState::RUNNING;
  while (this->_programState == arcade::ProgramState::RUNNING)
    {
      if (this->_game)
        this->gameHandler();
      else
        this->menuHandler();
    }
  return (0);
}
