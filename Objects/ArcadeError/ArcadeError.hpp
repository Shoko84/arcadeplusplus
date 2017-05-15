/*
** ComponentError.hpp for Rendu in /home/cauvin_m/Rendu/cpp_nanotekspice/Objects/ComponentError
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Sun Mar 05 11:57:17 2017 cauvin-m
** Last update Sun Apr 09 01:28:18 2017 cauvin-m
*/

#ifndef ARCADE_ERROR_HPP
#define  ARCADE_ERROR_HPP

# include <iostream>

namespace arcade
{
  class ArcadeError : public std::exception
  {
    std::string _message;

  public:
    ArcadeError(std::string const &message) : _message(message) {};
    ~ArcadeError() throw() {};

    virtual const char* what() const throw() {return (this->_message.c_str());};
  };
}

#endif /* ARCADE_ERROR_HPP */
