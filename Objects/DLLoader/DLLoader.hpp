/*
** DLLoader.hpp for Rendu in /home/cauvin_m/Rendu/cpp_arcade/Objects/DLLoader
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Mon Mar 13 11:43:24 2017 cauvin-m
// Last update Sun Mar 19 22:20:30 2017 Maxime Cauvin
*/

#ifndef DLLOADER_HPP
#define  DLLOADER_HPP

# include <dlfcn.h>
# include "ArcadeError.hpp"

namespace arcade
{
  template <typename T>
  class DLLoader
  {
    T                 *(*_ctor)();
    void              (*_dtor)(T *);
    T                 *_obj;
    void              *_handler;

  public:
    DLLoader(std::string const& filepath)
    {
      if (!(this->_handler = dlopen(filepath.c_str(), RTLD_LAZY)))
        throw arcade::ArcadeError(dlerror());
      if (!(this->_ctor = (T* (*)())dlsym(this->_handler, "CObject")))
        throw arcade::ArcadeError(dlerror());
      if (!(this->_dtor = (void (*)(T*))dlsym(this->_handler, "DObject")))
        throw arcade::ArcadeError(dlerror());
    }

    ~DLLoader() noexcept(false)
    {
      this->_dtor(this->_obj);
      if (dlclose(this->_handler))
        throw arcade::ArcadeError(dlerror());
    }

    T* getInstance()
    {
      this->_obj = (T*)this->_ctor();
      return (this->_obj);
    }
  };
}

#endif /* DLLOADER_HPP */
