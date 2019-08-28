#pragma once
#ifndef TPS_TEXTUREMANAGER2D
#define TPS_TEXTUREMANAGER2D

#include "texturemanager_intfc.hpp"

namespace TouhouProjectShadow {

   class TextureManager2D : public TMI {
   public:
      TextureManager2D(std::string const& texture_absolutepath);
      
      MRI_Message PreloadTextureImage(
         std::string const& TIalias, TIPM const&) override;
      MRI_Message PreloadTextureCoordmap(
         std::string const& TCalias, TCPM const&) override;
      MRI_Message ReadTextureCoordmap(
         std::string const& TCalias) const override;
      MRI_Message Create(UIC const&, std::string const& TCalias) override;
      MRI_Message Destroy(UIC const&) override;
      MRI_Message GetTextureCoordmap(UIC const&, TCHandle&) const override;
   private:
      class Impl;
      std::unique_ptr<Impl> pImpl;
   };
}
#endif // !TPS_TEXTUREMANAGER2D
