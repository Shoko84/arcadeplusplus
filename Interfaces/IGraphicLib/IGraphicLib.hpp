/*
** IGraphicLib.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/Interfaces/IGraphicLib
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Tue Apr 04 17:38:24 2017 cauvin-m
** Last update Tue Apr 04 17:38:35 2017 cauvin-m
*/

#ifndef IGRAPHICLIB_HPP_
# define IGRAPHICLIB_HPP_

#include <iostream>
#include <vector>
#include <unordered_map>

namespace arcade
{

  // Différents évenements du clavier
  enum class EventKeyBoard : int
  {
    EK_DEFAULT = -1,
    EK_ESCAPE = 0,
    EK_LEFT = 1,
    EK_RIGHT = 2,
    EK_UP,
    EK_DOWN,
    EK_SPACE,
    EK_P,
    EK_ENTER,
    EK_BACKSPACE,
    EK_NUMPAD2,
    EK_NUMPAD3,
    EK_NUMPAD4,
    EK_NUMPAD5,
    EK_NUMPAD8,
    EK_NUMPAD9,
    EK_SHIFT
  };

  enum class SoundType : int
  {
    ST_DEFAULT = -1,
    ST_SOUND = 0,
    ST_MUSIC = 1
  };

  struct Sprite
  {
    size_t          color;      // Couleur en hexa
    std::string     asciiImage; // Ascii de l'image ( possibilité de le remplire d'espace )
  };

  struct Pos
  {
    Pos(void){}
    Pos(double _x, double _y) : x(_x), y(_y){}

    double    x;
    double    y;
  };

  class IGraphicLib
  {
    // Initialise la window
  public:
    virtual int                               initWin(void) = 0;
    virtual int                               openWin(Pos const& gameSize) = 0;
    virtual int                               closeWin(void) = 0;

    // Fonctions à utiliser dans la mainLoop
  public:
    virtual EventKeyBoard                     getEvent(void) = 0;   // Retourne un evenement du clavier
    virtual int                               clearWin(void) = 0;   // Netoie la fenêtre ( à mettre en debut de boucle de jeu )
    virtual int                               refreshWin(void) = 0; // Actualise la fenêtre ( à mettre en fin de boucle de jeu )

    // Ajoute un nouveau sprite dans la lib graphique
  public:
    //  param -> nom de l'image, couleur de fond, asciiArt
    virtual void                              addSprite(std::string const& imageName, size_t const& color, std::string const& asciiImage) = 0;

    // Fonctions de dessin
  public:
    virtual int                               p_backGround(std::string const& image) = 0; // Dessine une image de fond a notre jeu
    virtual int                               p_cell(Pos const& pos, std::string const& image, const int way) = 0; // Dessine une cellule au point donné avec une image donnée dans le way 0, 1, 2 ou 3; ou une couleur de fond et le caractère la composant
    virtual int                               p_hLine(Pos const& pos, const int length, std::string const& image, const int way) = 0; // Dessine une ligne horizontale de cellules à partir d'un point jusqu'a sa taille
    virtual int                               p_vLine(Pos const& pos, const int length, std::string const& image, const int way) = 0; // Dessine une ligne verticale de cellules à partir d'un point jusqu'a sa taille
    virtual int                               p_text(Pos const& pos, const std::string& str, const size_t color, const int size) = 0; // Ecrit du texte au point donné
    virtual int                               p_sound(std::string const& soundName, SoundType const& soundType) = 0; // Joue un son
  };

}

#endif
