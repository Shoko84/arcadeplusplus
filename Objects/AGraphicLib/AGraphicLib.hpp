/*
** AGraphicLib.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/Objects/AGraphicLib
**
** Made by Maxime Cauvin
** Login   <cauvin_m@epitech.net>
**
** Started on  Wed Mar 08 15:15:26 2017 cauvin-m
** Last update Sun Apr 09 14:06:32 2017 cauvin-m
*/

#ifndef AGRAPHICLIB_HPP_
# define AGRAPHICLIB_HPP_

#include "IGraphicLib.hpp"

namespace arcade
{

  class AGraphicLib : public IGraphicLib
  {
  public:
    AGraphicLib(void) : _screenSize(Pos(35, 35)){}
    virtual ~AGraphicLib(void){}

  public:
    virtual int                               initWin(void) = 0;
    virtual int                               openWin(Pos const& gameSize) = 0;
    virtual int                               closeWin(void) = 0;

  public:
    virtual EventKeyBoard                     getEvent(void) = 0;   // Retourne un evenement du clavier
    virtual int                               clearWin(void) = 0;   // Netoie la fenêtre ( à mettre en debut de boucle de jeu )
    virtual int                               refreshWin(void) = 0; // Actualise la fenêtre ( à mettre en fin de boucle de jeu )

  public:
    virtual void                              addSprite(std::string const& imageName, size_t const& color, std::string const& asciiImage){
      Sprite        sprite;

      sprite.color = color;
      sprite.asciiImage = asciiImage;
      this->_sprites[imageName] = sprite;
    };

  public:
    virtual int                               p_backGround(std::string const& image) = 0; // Dessine une image de fond a notre jeu
    virtual int                               p_cell(Pos const& pos, std::string const& image, const int way) = 0; // Dessine une cellule au point donné avec une image donnée dans le way 0, 1, 2 ou 3; ou une couleur de fond et le caractère la composant
    virtual int                               p_hLine(Pos const& pos, const int length, std::string const& image, const int way) = 0; // Dessine une ligne horizontale de cellules à partir d'un point jusqu'a sa taille
    virtual int                               p_vLine(Pos const& pos, const int length, std::string const& image, const int way) = 0; // Dessine une ligne verticale de cellules à partir d'un point jusqu'a sa taille
    virtual int                               p_text(Pos const& pos, const std::string& str, const size_t color, const int size) = 0; // Ecrit du texte au point donné
    virtual int                               p_sound(std::string const& soundName, SoundType const& soundType) = 0; // Joue un son

  protected:
    std::unordered_map<std::string, Sprite>   _sprites;
    Pos                                       _screenSize;
  };

}

#endif
