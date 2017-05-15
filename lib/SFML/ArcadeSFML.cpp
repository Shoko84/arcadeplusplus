/*
** ArcadeSFML.cpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/lib/SFML
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Mon Mar 13 13:28:04 2017 cauvin-m
** Last update Sun Apr 09 17:16:08 2017 cauvin-m
*/

#include "ArcadeSFML.hpp"

arcade::ArcadeSFML::ArcadeSFML()
{

}

arcade::ArcadeSFML::~ArcadeSFML()
{

}

int                               arcade::ArcadeSFML::initWin()
{
  DIR                             *dir;
  struct dirent                   *dirp;

  if (!this->_font.loadFromFile("./Assets/Fonts/ArcadeItalic.ttf") && !this->_font.loadFromFile("/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc"))
    throw arcade::ArcadeError("Could not load './Assets/Fonts/ArcadeItalic.ttf' nor '/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc'");
  if ((dir = opendir("./Assets/Images/")))
  {
    while ((dirp = readdir(dir)))
    {
      std::string name = dirp->d_name;
      if (dirp->d_type == DT_REG)
        {
          sf::Texture tx;
          tx.loadFromFile("./Assets/Images/" + name);
          this->_txList[name] = tx;
        }
    }
    closedir(dir);
  }
  else
    std::cerr << "Could not open './Assets/Images' folder" << std::endl;
  return (0);
}

int                               arcade::ArcadeSFML::openWin(Pos const& gameSize)
{
  sf::ContextSettings             settings;

  this->_screenSize = gameSize;
  settings.antialiasingLevel = 4;
  this->_window.create(sf::VideoMode(this->_screenSize.x * CELLSIZE, this->_screenSize.y * CELLSIZE), "Arcade", sf::Style::Default, settings);
  return (0);
}

int                               arcade::ArcadeSFML::closeWin()
{
  if (this->_window.isOpen())
    this->_window.close();
  return (0);
}

arcade::EventKeyBoard             arcade::ArcadeSFML::getEvent()
{
  if (this->_window.isOpen())
  {
    sf::Event event;
    while (this->_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        this->_window.close();
        return (arcade::EventKeyBoard::EK_ESCAPE);
      }
      else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        return (arcade::EventKeyBoard::EK_ESCAPE);
      else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) ||
               sf::Joystick::isButtonPressed(0, 4))
        return (arcade::EventKeyBoard::EK_UP);
      else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) ||
               sf::Joystick::isButtonPressed(0, 6))
        return (arcade::EventKeyBoard::EK_DOWN);
      else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) ||
               sf::Joystick::isButtonPressed(0, 7))
        return (arcade::EventKeyBoard::EK_LEFT);
      else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) ||
               sf::Joystick::isButtonPressed(0, 5))
        return (arcade::EventKeyBoard::EK_RIGHT);
      else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) ||
               sf::Joystick::isButtonPressed(0, 14))
        return (arcade::EventKeyBoard::EK_ENTER);
      else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) ||
               sf::Joystick::isButtonPressed(0, 12))
        return (arcade::EventKeyBoard::EK_SPACE);
      else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace) ||
               sf::Joystick::isButtonPressed(0, 13))
        return (arcade::EventKeyBoard::EK_BACKSPACE);
      else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad2)
        return (arcade::EventKeyBoard::EK_NUMPAD2);
      else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad3)
        return (arcade::EventKeyBoard::EK_NUMPAD3);
      else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad4)
        return (arcade::EventKeyBoard::EK_NUMPAD4);
      else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad5)
        return (arcade::EventKeyBoard::EK_NUMPAD5);
      else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad8)
        return (arcade::EventKeyBoard::EK_NUMPAD8);
      else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad9) ||
               sf::Joystick::isButtonPressed(0, 0))
        return (arcade::EventKeyBoard::EK_NUMPAD9);
      else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) ||
               sf::Joystick::isButtonPressed(0, 3))
        return (arcade::EventKeyBoard::EK_P);
      else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::LShift ||
                                                       event.key.code == sf::Keyboard::RShift))
        return (arcade::EventKeyBoard::EK_SHIFT);
    }
  }
  return (arcade::EventKeyBoard::EK_DEFAULT);
}

int                               arcade::ArcadeSFML::clearWin()
{
  sf::RectangleShape              rect(sf::Vector2f(this->_window.getSize()));

  rect.setFillColor(sf::Color(0, 0, 0, 255));
  this->_window.draw(rect);
  return (0);
}

int                               arcade::ArcadeSFML::refreshWin()
{
  this->_window.display();
  return (0);
}

int                               arcade::ArcadeSFML::p_backGround(std::string const& image)
{
  sf::RectangleShape              rect(sf::Vector2f(this->_window.getSize()));
  if (image != "" && this->_sprites.find(image) != this->_sprites.end())
  {
    if (this->_sprites[image].asciiImage != "")
    {
      sf::Sprite sp(this->_txList[image]);
      this->_window.draw(sp);
    }
    else
    {
      rect.setFillColor(GET_COLOR(this->_sprites[image].color));
      this->_window.draw(rect);
    }
  }
  return (0);
}

int                               arcade::ArcadeSFML::p_cell(Pos const& pos, std::string const& image, int const way)
{
  sf::RectangleShape  rect(sf::Vector2f(CELLSIZE, CELLSIZE));
  if (image != "" && this->_sprites.find(std::string("./Assets/Images/" + image)) != this->_sprites.end())
  {
    if (this->_txList.find(std::string("./Assets/Images/" + image)) == this->_txList.end())
    {
      rect.setPosition(pos.x * CELLSIZE, pos.y * CELLSIZE);
      rect.setFillColor(GET_COLOR(this->_sprites[std::string("./Assets/Images/" + image)].color));
      this->_window.draw(rect);
    }
    else
    {
      sf::Sprite sp(this->_txList[std::string("./Assets/Images/" + image)]);
      sf::FloatRect spSize = sp.getLocalBounds();

      sp.setPosition(pos.x * CELLSIZE, pos.y * CELLSIZE);
      sp.setOrigin(sp.getTexture()->getSize().x / 2, sp.getTexture()->getSize().y / 2);
      sp.setPosition(pos.x * CELLSIZE + sp.getTexture()->getSize().x / 2, pos.y * CELLSIZE + sp.getTexture()->getSize().y / 2);
      sp.setScale(CELLSIZE / spSize.width, CELLSIZE / spSize.height);
      sp.rotate(way * 90);
      this->_window.draw(sp);
    }
  }
  return (0);
}

int                               arcade::ArcadeSFML::p_hLine(Pos const& pos, int const length, std::string const& image, int const way)
{
  Pos pos2(pos.x, pos.y);

  for (int j = 0; j < length; j++)
  {
    p_cell(pos2, image, way);
    pos2.x += 1;
  }
  return (0);
}

int                               arcade::ArcadeSFML::p_vLine(Pos const& pos, int const length, std::string const& image, int const way)
{
  Pos pos2(pos.x, pos.y);

  for (int i = 0; i < length; i++)
  {
    p_cell(pos2, image, way);
    pos2.y += 1;
  }
  return (0);
}

int                               arcade::ArcadeSFML::p_text(Pos const& pos, std::string const& str, size_t color, int const size)
{
  sf::Text text(str, this->_font);

  text.setCharacterSize(size);
  text.setPosition(pos.x * CELLSIZE, pos.y * CELLSIZE);
  text.setFillColor(GET_COLOR(color));

  this->_window.draw(text);
  return (0);
}

int                               arcade::ArcadeSFML::p_sound(std::string const& soundName, arcade::SoundType const& soundType)
{
  if (soundType == arcade::SoundType::ST_SOUND)
  {
    if (!this->_sbuffer.loadFromFile(std::string("./Assets/Sounds/" + soundName)))
      return (-1);
    this->_sound.setBuffer(this->_sbuffer);
    this->_sound.setVolume(30);
    this->_sound.setPitch(0.9);
    this->_sound.play();
  }
  else if (soundType == arcade::SoundType::ST_MUSIC)
  {
    if (!this->_music.openFromFile("./Assets/Musics/" + soundName))
      return (-1);
    this->_music.play();
  }
  return (0);
}

void                             arcade::ArcadeSFML::addSprite(std::string const& imageName, size_t const& color, std::string const& asciiImage)
{
  Sprite        sprite;

  sprite.color = color;
  sprite.asciiImage = asciiImage;
  this->_sprites[std::string("./Assets/Images/" + imageName)] = sprite;
};

extern "C" arcade::ArcadeSFML *CObject()
{
  std::cout << "SFML constructed" << std::endl;
  return (new arcade::ArcadeSFML);
}

extern "C" void               DObject(arcade::ArcadeSFML *obj)
{
  std::cout << "SFML destructed" << std::endl;
  delete obj;
}
