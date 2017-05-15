/*
** Arcade.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Mon Mar 13 10:29:45 2017 cauvin-m
** Last update Sun Apr 09 01:18:39 2017 cauvin-m
*/

#ifndef ARCADE_HPP
#define  ARCADE_HPP

# include <ctime>
# include <fstream>
# include <iostream>
# include <map>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include "AGame.hpp"
# include "AGraphicLib.hpp"
# include "DLLoader.hpp"
# include "ArcadeError.hpp"

# define MS_PER_UPDATE  (40000)
# define ONE_SEC        (1000000)

namespace arcade
{
  enum class ProgramState : int
  {
    EXIT_ON_ERROR = -1,
    DEFAULT = 0,
    EXIT_ON_SUCCESS = 1,
    RUNNING = 2
  };

  enum class MenuState : int
  {
    UNKNOWN = -1,
    MENU_NAME = 0,
    GAME_SELECT = 1,
    LIB_SELECT = 2,
    LEADERBOARD = 3
  };
  
  class Arcade
  {
  private:
    std::string                                                         _name;

    std::vector<std::string>                                            _gamesList;
    std::vector<std::string>                                            _graphicLibList;
    std::vector<std::pair<std::string, std::map<size_t, std::string>>>  _scoresList;

    IGame                                                               *_game;
    IGraphicLib                                                         *_graphicLib;
    DLLoader<IGame>                                                     *_dlGame;
    DLLoader<IGraphicLib>                                               *_dlGraphicLib;

    int                                                                 _currentGameIdx;
    int                                                                 _currentGraphicLibIdx;

    ProgramState                                                        _programState;
    MenuState                                                           _menuState;

  public:
    Arcade(std::string const& pathGraphLib);
    virtual ~Arcade();

    int           mainLoop();
    void          gameHandler();
    void          menuHandler();

    void          displayMenuName(char const& charSelected, bool const& fade) const;
    void          displayMenuGame(char const& gameSelected, bool const& fade) const;
    void          displayMenuLib(char const& libSelected, bool const& fade) const;
    void          displayMenuLeaderboard(char const& gameSelected) const;
    void          menuNameEvents(std::clock_t & c_fade, char & charSelected, bool & fade);
    void          menuGameEvents(std::clock_t & c_fade, char & gameSelected, bool & fade);
    void          menuLibEvents(std::clock_t & c_fade, char & libSelected, bool & fade);
    void          menuLeaderboardEvents(char & gameSelected);

    void          pickNextGraphicLib(int const& nb);
    void          pickNextGame(int const& nb);

    void          refreshGameList();
    void          refreshGraphicLibList();
    void          refreshScoreList();

    void          printScoreInFile(std::string const& score) const;

    bool          fileExist(std::string const& filepath) const;
    bool          hasOnlyDigits(std::string const& str) const;
    bool          hasOnlyLetters(std::string const& str) const;

    Score         getHighscoreForGame(std::string const& gamename);
  };
}

#endif /* ARCADE_HPP */
