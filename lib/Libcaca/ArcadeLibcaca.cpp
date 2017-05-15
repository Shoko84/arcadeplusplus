/*
** ArcadeLibcaca.cpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/lib/ArcadeLibcaca
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Sun Mar 19 01:16:04 2017 cauvin-m
** Last update Sun Apr 09 14:05:58 2017 cauvin-m
*/

#include "ArcadeLibcaca.hpp"

arcade::ArcadeLibcaca::ArcadeLibcaca()
{

}

arcade::ArcadeLibcaca::~ArcadeLibcaca()
{

}

int                               arcade::ArcadeLibcaca::initWin()
{
  return (0);
}

int                               arcade::ArcadeLibcaca::openWin(Pos const& gameSize)
{
  this->_screenSize = gameSize;
  this->_canvas = caca_create_canvas(this->_screenSize.x * CELLSIZEX, this->_screenSize.y * CELLSIZEY);
  if (!(this->_window = caca_create_display(this->_canvas)))
  {
    std::cerr << "Could not load Caca window" << std::endl;
    return (-1);
  }
  caca_set_display_title(this->_window, "Arcade");
  return (0);
}

int                               arcade::ArcadeLibcaca::closeWin()
{
  if (this->_window)
    caca_free_display(this->_window);
  return (0);
}

arcade::EventKeyBoard             arcade::ArcadeLibcaca::getEvent()
{
  caca_event_t                    ev;
  int                             valKey;

  if (caca_get_event(this->_window, CACA_EVENT_KEY_PRESS | CACA_EVENT_QUIT, &ev, 0))
  {
    if (caca_get_event_type(&ev) == CACA_EVENT_QUIT)
      return (arcade::EventKeyBoard::EK_ESCAPE);
    else
    {
      if ((valKey = caca_get_event_key_ch(&ev)) == CACA_KEY_ESCAPE)
        return (arcade::EventKeyBoard::EK_ESCAPE);
      else if (valKey == CACA_KEY_UP)
        return (arcade::EventKeyBoard::EK_UP);
      else if (valKey == CACA_KEY_DOWN)
        return (arcade::EventKeyBoard::EK_DOWN);
      else if (valKey == CACA_KEY_LEFT)
        return (arcade::EventKeyBoard::EK_LEFT);
      else if (valKey == CACA_KEY_RIGHT)
        return (arcade::EventKeyBoard::EK_RIGHT);
      else if (valKey == CACA_KEY_RETURN)
        return (arcade::EventKeyBoard::EK_ENTER);
      else if (valKey == CACA_KEY_BACKSPACE)
        return (arcade::EventKeyBoard::EK_BACKSPACE);
      else if (valKey == 32)
        return (arcade::EventKeyBoard::EK_SPACE);
      else if (valKey == 50)
        return (arcade::EventKeyBoard::EK_NUMPAD2);
      else if (valKey == 51)
        return (arcade::EventKeyBoard::EK_NUMPAD3);
      else if (valKey == 52)
        return (arcade::EventKeyBoard::EK_NUMPAD4);
      else if (valKey == 53)
        return (arcade::EventKeyBoard::EK_NUMPAD5);
      else if (valKey == 56)
        return (arcade::EventKeyBoard::EK_NUMPAD8);
      else if (valKey == 57)
        return (arcade::EventKeyBoard::EK_NUMPAD9);
      else if (valKey == 9)
        return (arcade::EventKeyBoard::EK_SHIFT);
    }
  }
  return (arcade::EventKeyBoard::EK_DEFAULT);
}

int                               arcade::ArcadeLibcaca::clearWin()
{
  caca_clear_canvas(this->_canvas);
  return (0);
}

int                               arcade::ArcadeLibcaca::refreshWin()
{
  caca_refresh_display(this->_window);
  return (0);
}

int                               arcade::ArcadeLibcaca::p_backGround(std::string const& image)
{
  if (image != "" && this->_sprites.find(image) != this->_sprites.end())
  {
    caca_set_color_argb(this->_canvas, 0, this->convertU64ToU32(this->_sprites[image].color));
    for (size_t i = 0; i < this->_screenSize.y; i++)
    {
      for (size_t j = 0; j < this->_screenSize.x * CELLSIZEX; j++)
      caca_put_str(this->_canvas, j, i, this->_sprites[image].asciiImage.c_str());
    }
  }
  return (0);
}

int                               arcade::ArcadeLibcaca::p_cell(Pos const& pos, std::string const& image, int const way)
{
  (void)way;
  if (image != "" && this->_sprites.find(image) != this->_sprites.end())
  {
    caca_set_color_argb(this->_canvas, 0xFFF, this->convertU64ToU32(this->_sprites[image].color));
    for (int i = 0; i < CELLSIZEY; i++)
    {
      for (int j = 0; j < CELLSIZEX; j++)
        caca_put_str(this->_canvas, pos.x * CELLSIZEX + j, pos.y * CELLSIZEY + i, this->_sprites[image].asciiImage.substr((this->_sprites[image].asciiImage.length() > (size_t)(i * CELLSIZEX + j)) ? (i * CELLSIZEX + j) : (*(this->_sprites[image].asciiImage.end()))).c_str());
    }
  }
  return (0);
}

int                               arcade::ArcadeLibcaca::p_hLine(Pos const& pos, int const length, std::string const& image, int const way)
{
  Pos                             pos2(pos.x, pos.y);

  for (int i = 0; i < length; i++)
  {
    this->p_cell(pos2, image, way);
    pos2.x += 1;
  }
  return (0);
}

int                               arcade::ArcadeLibcaca::p_vLine(Pos const& pos, int const length, std::string const& image, int const way)
{
  Pos                             pos2(pos.x, pos.y);

  for (int i = 0; i < length; i++)
  {
    this->p_cell(pos2, image, way);
    pos2.y += 1;
  }
  return (0);
}

int                               arcade::ArcadeLibcaca::p_text(Pos const& pos, std::string const& str, size_t const color, int const size)
{
  (void)size;
  caca_set_color_argb(this->_canvas, this->convertU64ToU32(color), 0);
  caca_put_str(this->_canvas, pos.x * CELLSIZEX, pos.y * CELLSIZEY, str.c_str());
  return (0);
}

uint32_t                          arcade::ArcadeLibcaca::convertU64ToU32(size_t color)
{
  std::stringstream ss;
  uint32_t          newCol;
  std::string       strColor;

  ss << std::hex << color;
  for (size_t i = 0; i < 6 - ss.str().length(); i++)
    strColor += "0";
  strColor += ss.str();
  for (size_t i = 1; i < strColor.length(); i++)
    strColor.erase(i, 1);
  ss.str("");
  ss << std::hex << strColor;
  ss >> newCol;
  return (newCol);
}

int                               arcade::ArcadeLibcaca::p_sound(std::string const& soundName, SoundType const& soundType)
{
  (void)soundName;
  (void)soundType;
  return (0);
}

extern "C" arcade::ArcadeLibcaca *CObject()
{
  std::cout << "Libcaca constructed" << std::endl;
  return (new arcade::ArcadeLibcaca);
}

extern "C" void               DObject(arcade::ArcadeLibcaca *obj)
{
  std::cout << "Libcaca destructed" << std::endl;
  delete obj;
}
