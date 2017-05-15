/*
** MapEditorSolarfox.cpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/games/MapEditorSolarfox
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Tue Apr 04 19:36:40 2017 cauvin-m
** Last update Sun Apr 09 15:27:42 2017 cauvin-m
*/

#include "MapEditorSolarfox.hpp"

arcade::MapEditorSolarfox::MapEditorSolarfox()
{
  this->_gameSize = Pos(40, 45);
  this->_assetsList.clear();
  this->_assetsList = {{0, "mapeditor_solarfoxEmpty.png"},
                       {1, "mapeditor_solarfoxPowerup.png"},
                       {2, "mapeditor_solarfoxUnreachable.png"},
                       {3, "mapeditor_solarfoxPlayer.png"}};
  this->_type = arcade::SelectType::MAPEDIT;
  this->_mapSize = Pos(5, 5);
  this->_level = 1;
  this->_cursorPos = Pos(0, 0);
  this->resetKeysPressed();
  this->_map.clear();
  for (int i = 0; i < this->_mapSize.y; i++)
  {
    std::vector<int>  map;
    for (int j = 0; j < this->_mapSize.x; j++)
      map.push_back(0);
    this->_map.push_back(map);
  }
}

arcade::MapEditorSolarfox::~MapEditorSolarfox()
{
  if (!this->mapIsEmpty())
  {
    std::ofstream     ofs;
    std::string       sep;

    while (this->fileExist("./Assets/Maps/Solarfox/solarfox_level_" + std::to_string(this->_level) + ".txt"))
      this->_level += 1;
    ofs.open("./Assets/Maps/Solarfox/solarfox_level_" + std::to_string(this->_level) + ".txt");
    for (int i = 0; i < (int)this->_map.size(); i++)
    {
      for (int j = 0; j < (int)this->_map[i].size(); j++)
        ofs << this->_map[i][j];
      ofs << std::endl;
    }
    ofs.close();
  }
}

bool          arcade::MapEditorSolarfox::mapIsEmpty() const
{
  for (int i = 0; i < (int)this->_map.size(); i++)
  {
    for (int j = 0; j < (int)this->_map[i].size(); j++)
    {
      if (this->_map[i][j] != 0)
        return (false);
    }
  }
  return (true);
}

bool         arcade::MapEditorSolarfox::fileExist(std::string const& filepath) const
{
  std::ifstream      ifs(filepath);
  bool               doesExist;

  doesExist = ifs.good();
  ifs.close();
  return (doesExist);
}

void        arcade::MapEditorSolarfox::createCell(IGraphicLib *graphicLib, Pos const& pos, Pos const& size, std::string const& asset) const
{
  for (int i = 0; i < size.y; i++)
  {
    for (int j = 0; j < size.x; j++)
      graphicLib->p_cell(Pos(pos.x + j, pos.y + i), asset, 0);
  }
}

int         arcade::MapEditorSolarfox::initGame(IGraphicLib *graphicLib, Score const& highScore)
{
  (void)highScore;
  graphicLib->addSprite("mapeditor_background.png", 0x000000, " ");
  graphicLib->addSprite("mapeditor_border.png", 0xffffff, " ");
  graphicLib->addSprite("mapeditor_selected.png", 0x00ff00, "-");
  graphicLib->addSprite(this->_assetsList[1], 0xffffff, " ");
  graphicLib->addSprite(this->_assetsList[2], 0xff0000, " ");
  graphicLib->addSprite(this->_assetsList[3], 0xf2e800, " ");
  return (0);
}

void        arcade::MapEditorSolarfox::resetKeysPressed()
{
  this->_keysPressed = {{EventKeyBoard::EK_LEFT, false},
                        {EventKeyBoard::EK_RIGHT, false},
                        {EventKeyBoard::EK_UP, false},
                        {EventKeyBoard::EK_DOWN, false},
                        {EventKeyBoard::EK_ENTER, false},
                        {EventKeyBoard::EK_BACKSPACE, false},
                        {EventKeyBoard::EK_SPACE, false}};
}

void        arcade::MapEditorSolarfox::mapEditEvents()
{
  if (this->_keysPressed[EventKeyBoard::EK_DOWN] && this->_cursorPos.y < this->_mapSize.y - 1)
    this->_cursorPos.y += 1;
  else if (this->_keysPressed[EventKeyBoard::EK_UP] && this->_cursorPos.y > 0)
    this->_cursorPos.y -= 1;
  else if (this->_keysPressed[EventKeyBoard::EK_RIGHT] && this->_cursorPos.x < this->_mapSize.x - 1)
    this->_cursorPos.x += 1;
  else if (this->_keysPressed[EventKeyBoard::EK_LEFT] && this->_cursorPos.x > 0)
    this->_cursorPos.x -= 1;
  else if (this->_keysPressed[EventKeyBoard::EK_ENTER])
    this->_map[this->_cursorPos.y][this->_cursorPos.x] += 1;
  else if (this->_keysPressed[EventKeyBoard::EK_BACKSPACE])
    this->_map[this->_cursorPos.y][this->_cursorPos.x] -= 1;
  else if (this->_keysPressed[EventKeyBoard::EK_SPACE])
    this->_type = SelectType::SIZEEDIT;

  if (this->_map[this->_cursorPos.y][this->_cursorPos.x] < 0)
    this->_map[this->_cursorPos.y][this->_cursorPos.x] = this->_assetsList.size() - 1;
  else if (this->_map[this->_cursorPos.y][this->_cursorPos.x] >= (int)this->_assetsList.size())
    this->_map[this->_cursorPos.y][this->_cursorPos.x] = 0;
}

void        arcade::MapEditorSolarfox::sizeEditEvents()
{
  if (this->_keysPressed[EventKeyBoard::EK_DOWN] && this->_mapSize.y > 5)
  {
    this->_mapSize.y -= 1;
    this->_map.pop_back();
  }
  else if (this->_keysPressed[EventKeyBoard::EK_UP] && this->_mapSize.y < 100)
  {
    this->_mapSize.y += 1;
    std::vector<int> map;
    for (int i = 0; i < this->_mapSize.x; i++)
      map.push_back(0);
    this->_map.push_back(map);
  }
  else if (this->_keysPressed[EventKeyBoard::EK_RIGHT] && this->_mapSize.x < 100)
  {
    this->_mapSize.x += 1;
    for (int i = 0; i < (int)this->_map.size(); i++)
      this->_map[i].push_back(0);
  }
  else if (this->_keysPressed[EventKeyBoard::EK_LEFT] && this->_mapSize.x > 5)
  {
    this->_mapSize.x -= 1;
    for (int i = 0; i < (int)this->_map.size(); i++)
      this->_map[i].pop_back();
  }
  else if (this->_keysPressed[EventKeyBoard::EK_ENTER])
    this->_type = SelectType::LEVELEDIT;
  else if (this->_keysPressed[EventKeyBoard::EK_SPACE])
    this->_type = SelectType::MAPEDIT;
}

void        arcade::MapEditorSolarfox::levelEditEvents()
{
  if (this->_keysPressed[EventKeyBoard::EK_UP] || this->_keysPressed[EventKeyBoard::EK_RIGHT])
    this->_level += 1;
  else if ((this->_keysPressed[EventKeyBoard::EK_DOWN] || this->_keysPressed[EventKeyBoard::EK_LEFT]) && this->_level > 1)
    this->_level -= 1;
  else if (this->_keysPressed[EventKeyBoard::EK_ENTER])
    this->_type = SelectType::SIZEEDIT;
  else if (this->_keysPressed[EventKeyBoard::EK_SPACE])
    this->_type = SelectType::MAPEDIT;
}

int         arcade::MapEditorSolarfox::play()
{
  if (this->_type == SelectType::MAPEDIT)
    this->mapEditEvents();
  else if (this->_type == SelectType::SIZEEDIT)
    this->sizeEditEvents();
  else if (this->_type == SelectType::LEVELEDIT)
    this->levelEditEvents();
  this->resetKeysPressed();
  return (0);
}

int         arcade::MapEditorSolarfox::actionOfEvent(EventKeyBoard const& event)
{
  if (event == EventKeyBoard::EK_LEFT || event == EventKeyBoard::EK_RIGHT ||
      event == EventKeyBoard::EK_UP || event == EventKeyBoard::EK_DOWN ||
      event == EventKeyBoard::EK_BACKSPACE || event == EventKeyBoard::EK_ENTER ||
      event == EventKeyBoard::EK_SPACE)
    {
      this->resetKeysPressed();
      this->_keysPressed[event] = true;
    }
  return (0);
}

int         arcade::MapEditorSolarfox::display(IGraphicLib *graphicLib)
{
  graphicLib->p_backGround("mapeditor_background.png");
  graphicLib->p_text(Pos(6, 42), std::string("Map size: " + std::to_string((int)this->_mapSize.x) + "x" + std::to_string((int)this->_mapSize.y)), 0xf2e800, 12);
  graphicLib->p_text(Pos(25, 42), std::string("Map level: " + std::to_string(this->_level)), 0xf2e800, 12);
  for (int i = 0; i < (int)this->_map.size(); i++)
  {
    for (int j = 0; j < (int)this->_map[i].size(); j++)
    {
      this->createCell(graphicLib, Pos(this->_gameSize.x / this->_mapSize.x * j,
                       (this->_gameSize.y - 5) / this->_mapSize.y * i),
                       Pos(this->_gameSize.x / this->_mapSize.x,
                           (this->_gameSize.y - 5) / this->_mapSize.y),
                       this->_assetsList[this->_map[i][j]]);
    }
  }
  if (this->_type == SelectType::MAPEDIT)
    graphicLib->p_hLine(Pos(this->_gameSize.x / this->_mapSize.x * this->_cursorPos.x,
                            (this->_gameSize.y - 5) / this->_mapSize.y * this->_cursorPos.y + ((this->_gameSize.y - 5) / this->_mapSize.y) - 1),
                        this->_gameSize.x / this->_mapSize.x,
                        ("mapeditor_selected.png"), 0);
  else if (this->_type == SelectType::SIZEEDIT)
    graphicLib->p_hLine(Pos(2.5, 43), 15, ("mapeditor_selected.png"), 0);
  else if (this->_type == SelectType::LEVELEDIT)
    graphicLib->p_hLine(Pos(21, 43), 15, ("mapeditor_selected.png"), 0);
  return (0);
}

extern "C" arcade::MapEditorSolarfox   *CObject()
{
  std::cout << "MapEditorSolarfox constructed" << std::endl;
  return (new arcade::MapEditorSolarfox);
}

extern "C" void             DObject(arcade::MapEditorSolarfox *obj)
{
    std::cout << "MapEditorSolarfox destructed" << std::endl;
    delete obj;
}
