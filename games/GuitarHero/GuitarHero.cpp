/*
** GuitarHero.cpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/games/GuitarHero
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Mon Apr 03 13:46:31 2017 cauvin-m
** Last update Sun Apr 09 23:04:20 2017 cauvin-m
*/

#include "GuitarHero.hpp"

arcade::GuitarHero::GuitarHero()
{
  this->_assetsUnpressed[0] = "guitarhero_firstkey_unpressed.png";
  this->_assetsUnpressed[1] = "guitarhero_secondkey_unpressed.png";
  this->_assetsUnpressed[2] = "guitarhero_thirdkey_unpressed.png";
  this->_assetsUnpressed[3] = "guitarhero_fourthkey_unpressed.png";
  this->_assetsPressed[0] = "guitarhero_firstkey_pressed.png";
  this->_assetsPressed[1] = "guitarhero_secondkey_pressed.png";
  this->_assetsPressed[2] = "guitarhero_thirdkey_pressed.png";
  this->_assetsPressed[3] = "guitarhero_fourthkey_pressed.png";
  for (int i = 0; i < 4; i++)
    this->_keys[i] = 0;
  this->_turns = 0;
  this->_combo = 0;
  this->_gameSize = Pos(20, 45);
  this->loadGuitarHeroMaps();
  this->_stateType = SelectType::MAPSELECT;
  this->_clkFade = std::clock();
  this->_fade = false;
  this->_mapIdxSelected = 0;
}

arcade::GuitarHero::~GuitarHero()
{

}

void        arcade::GuitarHero::createNote(IGraphicLib *graphicLib, Pos const& pos, Pos const& size, std::string const& asset) const
{
  for (int i = 0; i < size.y; i++)
  {
    for (int j = 0; j < size.x; j++)
      graphicLib->p_cell(Pos(pos.x + j, pos.y + i), asset, 0);
  }
}

int         arcade::GuitarHero::initGame(IGraphicLib *graphicLib, Score const& highScore)
{
  this->_graphicLib = graphicLib;
  this->_highScore = highScore;
  graphicLib->addSprite("guitarhero_background.png", 0x000000, " ");
  graphicLib->addSprite(this->_assetsUnpressed[0], 0x0d4d13, "-");
  graphicLib->addSprite(this->_assetsPressed[0], 0x2db036, "_");
  graphicLib->addSprite(this->_assetsUnpressed[1], 0x21656a, "-");
  graphicLib->addSprite(this->_assetsPressed[1], 0x3adff6, "_");
  graphicLib->addSprite(this->_assetsUnpressed[2], 0x731d1d, "-");
  graphicLib->addSprite(this->_assetsPressed[2], 0xde2a2a, "_");
  graphicLib->addSprite(this->_assetsUnpressed[3], 0x601c85, "-");
  graphicLib->addSprite(this->_assetsPressed[3], 0xc026df, "_");
  graphicLib->addSprite("guitarhero_note.png", 0xffffff, "o");
  return (0);
}

void        arcade::GuitarHero::loadGuitarHeroMaps()
{
  DIR                       *dir;
  struct dirent             *dirp;

  if ((dir = opendir("./Assets/Maps/GuitarHero/")))
  {
    while ((dirp = readdir(dir)))
    {
      std::string name = dirp->d_name;
      if (dirp->d_type == DT_REG && name.find("guitarhero_music_") != std::string::npos && name.find(".txt") != std::string::npos &&
          name.find("guitarhero_music_") == 0 && name.substr(name.find(".txt")) == ".txt")
        {
          std::ifstream     ifs("./Assets/Maps/GuitarHero/" + name);
          std::string       tick;
          std::string       note;
          bool              isMalformed = false;
          std::vector<Pos>  fallingNotes;

          if (ifs)
          {
            while (ifs >> tick)
            {
              if (!this->hasOnlyDigits(tick))
              {
                isMalformed = true;
                break;
              }
              if (ifs >> note)
              {
                if (note.length() != 4)
                {
                  isMalformed = true;
                  break;
                }
                for (size_t i = 0; i < note.length(); i++)
                {
                  if (note[i] == '1')
                    fallingNotes.push_back(Pos(this->_gameSize.x / 4 * i,
                                               this->_gameSize.y - 4.0f - std::stoi(tick)));
                }
              }
              else
              {
                isMalformed = true;
                break;
              }
            }
            ifs.close();
          }
          else
            throw arcade::ArcadeError("There was an error while loading ./Assets/Maps/GuitarHero/" + name);
          if (!isMalformed)
            this->_fallingNotes[name.substr(std::string("guitarhero_music_").length())] = fallingNotes;
          else
            std::cerr << "File './Assets/Maps/GuitarHero/" << name << "' malformed." << std::endl;
        }
      }
    closedir(dir);
  }
}

bool        arcade::GuitarHero::hitNotes(int const& keyIdx, int const& noteIdx)
{
  int score;

  if (this->_keys[keyIdx] > 0 &&
      this->_fallingNotes[this->_currentMap][noteIdx].y >= this->_gameSize.y - 5.5f &&
      this->_fallingNotes[this->_currentMap][noteIdx].y <= this->_gameSize.y - 2.5f &&
      this->_fallingNotes[this->_currentMap][noteIdx].x == this->_gameSize.x / 4 * keyIdx)
    {
      this->_combo += 1;
      if (this->_fallingNotes[this->_currentMap][noteIdx].y >= this->_gameSize.y - 4.5f &&
          this->_fallingNotes[this->_currentMap][noteIdx].y <= this->_gameSize.y - 3.5f)
        score = 300;
      else if (this->_fallingNotes[this->_currentMap][noteIdx].y >= this->_gameSize.y - 5.5f &&
               this->_fallingNotes[this->_currentMap][noteIdx].y <= this->_gameSize.y - 2.5f)
        score = 100;
      this->setScore(std::to_string(std::stoi(this->getScore()) + score * this->_combo));
      this->_fallingNotes[this->_currentMap].erase(this->_fallingNotes[this->_currentMap].begin() + noteIdx);
      return (true);
    }
  else if (this->_fallingNotes[this->_currentMap][noteIdx].y >= this->_gameSize.y - 2.0f)
    {
      this->_fallingNotes[this->_currentMap].erase(this->_fallingNotes[this->_currentMap].begin() + noteIdx);
      this->_combo = 0;
      return (true);
    }
  return (false);
}

int         arcade::GuitarHero::play()
{
  if (this->_stateType == SelectType::MAPSELECT)
  {
    if (std::clock() - this->_clkFade >= 1000000 / 2.5)
    {
      this->_fade = !this->_fade;
      this->_clkFade = std::clock();
    }
  }
  else if (this->_stateType == SelectType::MAPPLAY)
  {
    if (this->_fallingNotes[this->_currentMap].empty())
      this->setGameState(GameState::EXIT_ON_SUCCESS);
    else
    {
      for (size_t i = 0; i < this->_fallingNotes[this->_currentMap].size(); i++)
        this->_fallingNotes[this->_currentMap][i].y += 0.75;
      for (int i = 0; i < 4; i++)
      {
        for (int j = 0; j < (int)this->_fallingNotes[this->_currentMap].size(); j++)
        {
          if (this->hitNotes(i, j))
            j -= 1;
        }
        if (this->_keys[i] > 0)
          this->_keys[i] -= 1;
      }
      this->_turns += 1;
    }
  }
  return (0);
}

int         arcade::GuitarHero::actionOfEvent(EventKeyBoard const& event)
{
  if (this->_stateType == SelectType::MAPSELECT)
  {
    if (this->_fallingNotes.size() > 0)
    {
      if (event == arcade::EventKeyBoard::EK_DOWN || event == arcade::EventKeyBoard::EK_UP)
      {
        this->_graphicLib->p_sound("em_selectmenu.ogg", arcade::SoundType::ST_SOUND);
        this->_fade = false;
        this->_clkFade = std::clock();
      }
      if (event == arcade::EventKeyBoard::EK_DOWN)
        this->_mapIdxSelected += 1;
      else if (event == arcade::EventKeyBoard::EK_UP)
        this->_mapIdxSelected -= 1;
      else if (event == arcade::EventKeyBoard::EK_ENTER)
        {
          int i = 0;

          for (auto it = this->_fallingNotes.begin(); it != this->_fallingNotes.end(); ++it, i++)
          {
            if (i == this->_mapIdxSelected)
            {
              this->_currentMap = (*it).first;
              break;
            }
          }
          this->_stateType = SelectType::MAPPLAY;
        }
      if (this->_mapIdxSelected < 0)
        this->_mapIdxSelected = this->_fallingNotes.size() - 1;
      else if (this->_mapIdxSelected > (int)this->_fallingNotes.size() - 1)
        this->_mapIdxSelected = 0;
    }
  }
  else if (this->_stateType == SelectType::MAPPLAY)
  {
    if (event == arcade::EventKeyBoard::EK_LEFT)
      this->_keys[0] = 4;
    else if (event == arcade::EventKeyBoard::EK_DOWN)
      this->_keys[1] = 4;
    else if (event == arcade::EventKeyBoard::EK_UP)
      this->_keys[2] = 4;
    else if (event == arcade::EventKeyBoard::EK_RIGHT)
      this->_keys[3] = 4;
  }
  return (0);
}

int         arcade::GuitarHero::display(IGraphicLib *graphicLib)
{
  graphicLib->p_backGround("guitarhero_background.png");
  if (this->_stateType == SelectType::MAPSELECT)
  {
    int i = 0;

    graphicLib->p_text(Pos(7, 3), "Music list:", 0xf2e800, 14);
    if (this->_fallingNotes.size() > 0)
    {
      for (auto it = this->_fallingNotes.begin(); it != this->_fallingNotes.end(); ++it, i++)
      {
        if (!this->_fade || this->_mapIdxSelected != i)
          graphicLib->p_text(Pos(2, 6 + i), (*it).first, 0xf2e800, 10);
      }
      graphicLib->p_text(Pos(3, this->_gameSize.y - 3), "Press ENTER to start tapping !", 0xf2e800, 10);
    }
    else
      graphicLib->p_text(Pos(3, 7), "No map found.", 0xf2e800, 12);
  }
  else if (this->_stateType == SelectType::MAPPLAY)
  {
    graphicLib->p_text(Pos(1, 1), std::string("Combo: " + std::to_string(this->_combo)), 0xf2e800, 7);
    graphicLib->p_text(Pos(6, 1), std::string("Score: " + this->getScore()), 0xf2e800, 7);
    if (this->_highScore.name != "" && this->_highScore.score != "")
      graphicLib->p_text(Pos(this->_gameSize.x - 9, 1), std::string("Highscore: " + this->_highScore.name + " " + this->_highScore.score), 0xf2e800, 7);
    else
      graphicLib->p_text(Pos(this->_gameSize.x - 9, 1), "No highscores found.", 0xf2e800, 7);
    for (int i = 0; i < 4; i++)
    {
      if (!this->_keys[i])
        this->createNote(graphicLib, Pos(this->_gameSize.x / 4 * i, this->_gameSize.y - 4.0f), Pos(this->_gameSize.x / 4, 2), this->_assetsUnpressed[i]);
      else
        this->createNote(graphicLib, Pos(this->_gameSize.x / 4 * i, this->_gameSize.y - 4.0f), Pos(this->_gameSize.x / 4, 2), this->_assetsPressed[i]);
    }
    for (size_t i = 0; i < this->_fallingNotes[this->_currentMap].size(); i++)
    {
      if (this->_fallingNotes[this->_currentMap][i].y >= 3.0f && this->_fallingNotes[this->_currentMap][i].y < this->_gameSize.y + 3.0f)
        this->createNote(graphicLib, this->_fallingNotes[this->_currentMap][i], Pos(this->_gameSize.x / 4, 2), "guitarhero_note.png");
    }
  }
  return (0);
}

bool                arcade::GuitarHero::hasOnlyDigits(std::string const& str) const
{
  return (str.find_first_not_of("0123456789") == std::string::npos);
}

extern "C" arcade::GuitarHero   *CObject()
{
  std::cout << "GuitarHero constructed" << std::endl;
  return (new arcade::GuitarHero);
}

extern "C" void             DObject(arcade::GuitarHero *obj)
{
  std::cout << "GuitarHero destructed" << std::endl;
  delete obj;
}
