/*
** ArcadeGLUT.cpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/lib/GLUT
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Fri Mar 24 10:06:15 2017 cauvin-m
// Last update Fri Mar 24 15:24:05 2017 cauvin-m
*/

#include "ArcadeGLUT.hpp"

arcade::ArcadeGLUT::ArcadeGLUT()
{

}

arcade::ArcadeGLUT::~ArcadeGLUT()
{

}

int                               arcade::ArcadeGLUT::initWin()
{
  return (0);
}

int                               arcade::ArcadeGLUT::openWin(Pos const& gameSize)
{
  int                             ac = 1;
  char                            **av = NULL;

  glutInit(&ac, av);
  this->_screenSize = gameSize;
  glutInitWindowSize(this->_screenSize.x * CELLSIZE, this->_screenSize.y * CELLSIZE);
  this->_window = glutCreateWindow("Arcade");
  return (0);
}

int                               arcade::ArcadeGLUT::closeWin()
{
  glutDestroyWindow(this->_window);
  return (0);
}

static unsigned char keyP = -1;
static int keySP = -1;

void                              keySpecialFunc(int key, int x, int y)
{
  (void)x;
  (void)y;
  keySP = key;
}

void                              keyPressedFunc(unsigned char key, int x, int y)
{
  (void)x;
  (void)y;
  keyP = key;
}

arcade::EventKeyBoard             arcade::ArcadeGLUT::getEvent()
{
  keyP = -1;
  keySP = -1;
  glutSpecialFunc(keySpecialFunc);
  glutKeyboardFunc(keyPressedFunc);
  glutMainLoopEvent();
  if (keyP == 27)
    return (arcade::EventKeyBoard::EK_ESCAPE);
  else if (keySP == GLUT_KEY_LEFT)
    return (arcade::EventKeyBoard::EK_LEFT);
  else if (keySP == GLUT_KEY_RIGHT)
    return (arcade::EventKeyBoard::EK_RIGHT);
  else if (keySP == GLUT_KEY_UP)
    return (arcade::EventKeyBoard::EK_UP);
  else if (keySP == GLUT_KEY_DOWN)
    return (arcade::EventKeyBoard::EK_DOWN);
  else if (keySP == 112 || keySP == 113)
    return (arcade::EventKeyBoard::EK_SHIFT);
  else if (keyP == 32)
    return (arcade::EventKeyBoard::EK_SPACE);
  else if (keyP == 'p' || keyP == 'P')
    return (arcade::EventKeyBoard::EK_P);
  else if (keyP == 13)
    return (arcade::EventKeyBoard::EK_ENTER);
  else if (keyP == 8)
    return (arcade::EventKeyBoard::EK_BACKSPACE);
  else if (keyP == '2')
    return (arcade::EventKeyBoard::EK_NUMPAD2);
  else if (keyP == '3')
    return (arcade::EventKeyBoard::EK_NUMPAD3);
  else if (keyP == '4')
    return (arcade::EventKeyBoard::EK_NUMPAD4);
  else if (keyP == '5')
    return (arcade::EventKeyBoard::EK_NUMPAD5);
  else if (keyP == '8')
    return (arcade::EventKeyBoard::EK_NUMPAD8);
  else if (keyP == '9')
    return (arcade::EventKeyBoard::EK_NUMPAD9);
  return (arcade::EventKeyBoard::EK_DEFAULT);
}

int                               arcade::ArcadeGLUT::clearWin()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  return (0);
}

int                               arcade::ArcadeGLUT::refreshWin()
{
  glFlush();
  return (0);
}

int                               arcade::ArcadeGLUT::p_backGround(std::string const& image)
{
  if (image != "" && this->_sprites.find(image) != this->_sprites.end())
  {
    glColor3f(0, 0, 0);
    glRectd(-1, 1, 1, -1);
  }
  return (0);
}

int                               arcade::ArcadeGLUT::p_cell(Pos const& pos, std::string const& image, int const way)
{
  (void)way;
  if (image != "" && this->_sprites.find(image) != this->_sprites.end())
  {
    Pos newPos = this->getTransformPosition(pos);
    Pos newPos2 = this->getTransformPosition(Pos(pos.x + 1, pos.y + 1));

    glColor3f(GET_RED(this->_sprites[image].color) / 255.0f, GET_GREEN(this->_sprites[image].color) / 255.0f, GET_BLUE(this->_sprites[image].color) / 255.0f);
    glRectd(newPos.x, newPos.y * -1, newPos2.x, newPos2.y * -1);
  }
  return (0);
}

int                               arcade::ArcadeGLUT::p_hLine(Pos const& pos, int const length, std::string const& image, int const way)
{
  Pos                             pos2(pos.x, pos.y);

  for (int i = 0; i < length; i++)
  {
    this->p_cell(pos2, image, way);
    pos2.x += 1;
  }
  return (0);
}

int                               arcade::ArcadeGLUT::p_vLine(Pos const& pos, int const length, std::string const& image, int const way)
{
  Pos                             pos2(pos.x, pos.y);

  for (int i = 0; i < length; i++)
  {
    this->p_cell(pos2, image, way);
    pos2.y += 1;
  }
  return (0);
}

int                               arcade::ArcadeGLUT::p_text(Pos const& pos, std::string const& str, size_t const color, int const size)
{
  (void)pos;
  (void)str;
  (void)color;
  (void)size;
  glColor3f(GET_RED(color) / 255.0f, GET_GREEN(color) / 255.0f, GET_BLUE(color) / 255.0f);
  glRasterPos2f(this->getTransformPosition(pos).x, this->getTransformPosition(pos).y * -1);
  for (size_t i = 0; i < str.length(); i++)
    {
      if (size < 14)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str.c_str()[i]);
      else
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str.c_str()[i]);
    }
  return (0);
}

arcade::Pos                       arcade::ArcadeGLUT::getTransformPosition(Pos const& pos)
{
  Pos                             newPos(pos.x, pos.y);

  newPos.x -= this->_screenSize.x / 2;
  newPos.x /= this->_screenSize.x / 2;
  newPos.y -= this->_screenSize.y / 2;
  newPos.y /= this->_screenSize.y / 2;
  return (newPos);
}

int                               arcade::ArcadeGLUT::p_sound(std::string const& soundName, SoundType const& soundType)
{
  (void)soundName;
  (void)soundType;
  return (0);
}

extern "C" arcade::ArcadeGLUT *CObject()
{
  std::cout << "GLUT constructed" << std::endl;
  return (new arcade::ArcadeGLUT);
}

extern "C" void               DObject(arcade::ArcadeGLUT *obj)
{
  std::cout << "GLUT destructed" << std::endl;
  delete obj;
}
