#pragma once
#ifndef TPS_TEXTUREMANAGER_2D
#define TPS_TEXTUREMANAGER_2D

#include "texturemanager_intfc.hpp"

namespace TouhouProjectShadow {
   class TextureManager_2D : public TMI {
   public:
      TextureManager_2D(void) = delete;
      TextureManager_2D(const TextureManager_2D&) = delete;
      TextureManager_2D operator=(const TextureManager_2D&) = delete;

      TextureManager_2D(const std::string&);
      ~TextureManager_2D(void);
      MRI_Message Register(std::string const&, TIRM const&);
      MRI_Message Register(std::string const&, TCRM const&);
      TCRM Get(std::string const&) const;
      MRI_Message Deregister(std::string const&);
   private:
      class Impl;
      Impl* pimpl = nullptr;
   };
}

#endif // !TPS_TEXTUREMANAGER_2D
