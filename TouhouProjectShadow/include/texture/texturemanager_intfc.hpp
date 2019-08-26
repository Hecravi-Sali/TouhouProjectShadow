#pragma once
#ifndef TPS_TEXTUREMANAGERINTFC
#define TPS_TEXTUREMANAGERINTFC

#include "../generalpurposetype/generalpurposetype.hpp"

namespace TouhouProjectShadow {
   typedef class TextureManager_intfc : public MRI {
   public:
      virtual ~TextureManager_intfc(void) = default;
      typedef TextureManager_intfc* TMIHandle;

      typedef struct TextureImagePreloadMessage {
         std::string relativePath;
         //  glTexParameteri(GL_TEXTURE_XD, parameteri.frist, parameteri.secoud);
         std::vector<std::pair<GLint, GLint>> parameteri;
         //  glTexParameterf(GL_TEXTURE_XD, parameteri.frist, parameteri.secoud);
         std::vector<std::pair<GLint, GLfloat>> parameterf;
      } TIPM;

      typedef struct TextureCoordmapPreloadMessage {
         Vec2f texturesizezoom;
         std::vector<Vec2f> coordmap;
         std::string textureimagealias;
      } TCPM, TextureCoordmap;

      virtual MRI_Message PreloadTextureImage(
         std::string const& TIalias, TIPM const&) = 0;
      virtual MRI_Message PreloadTextoreCoordmap(
         std::string const& TCalias, TCPM const&) = 0;
      virtual MRI_Message RegisterTextureCoordmap(
         UIC const&, std::string const& TCalias) = 0;
      virtual MRI_Message GetTextureCoordmap(
         UIC const&, TextureCoordmap*) = 0;
      virtual std::vector<Vec2f> GetTextureCoord(UIC const&) const = 0;
      virtual Vec2f GetTextureSizeZoom(UIC const&) const = 0;
   } TMI;
}
#endif // !TPS_TEXTUREMANAGERINTFC
