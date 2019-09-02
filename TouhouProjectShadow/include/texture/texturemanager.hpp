#pragma once
#ifndef TPS_TEXTUREMANAGER2D
#define TPS_TEXTUREMANAGER2D

#include "texturemanager_intfc.hpp"

namespace TouhouProjectShadow {
class TextureManager2D : public TMI {
public:
   TextureManager2D(std::string const&, std::shared_ptr<UNIQUEMUTEX>&);
   TextureManager2D(TextureManager2D const&) = delete;
   TextureManager2D operator=(TextureManager2D const&) = delete;
   TextureManager2D(TextureManager2D&&) noexcept;
   TextureManager2D& operator=(TextureManager2D&&) = delete;

   virtual MRI_Message PreloadTextureImage(
         std::string const& TIalias, TIPM const&) override;
   virtual MRI_Message PreloadTextureCoordmap(
         std::string const& TCalias, TCPM const&) override;
   virtual TCPM ReadTextureCoordmap(
         std::string const& TCalias) const override;
   virtual MRI_Message Create(
         UIC const&, std::string const& TCalias) override;
   virtual MRI_Message Destroy(UIC const&) override;
   virtual TCPM Get(UIC const&) const override;
   virtual MRI_Message Set(UIC const&, TCPM const&) override;
   std::weak_ptr<GLuint> Get(
std::string const& TIalias) const override;
private:
   class Impl;
   std::unique_ptr<Impl> pImpl;
};
}
#endif // !TPS_TEXTUREMANAGER2D
