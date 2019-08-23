#pragma once
#ifndef TPS_TEXTUREMANAGERINTFC
#define TPS_TEXTUREMANAGERINTFC

#include "..//messagereport//messagereport_intfc.hpp"

namespace TouhouProjectShadow {
   typedef class TextureManager_intfc : public MRI {
   public:
      virtual ~TextureManager_intfc(void) = default;
      typedef TextureManager_intfc* TMIHandle;

      typedef struct TextureImageRegistrationMessage {
         std::string relativePath;
         std::vector<std::pair<GLint, GLint>> parameteri;
         std::vector<std::pair<GLint, GLfloat>> parameterf;
      } TIRM;

      typedef struct TextureCoordinateRegistrationMessage {
         std::vector<Vec2f> coord;
         std::string textureimagealias;
      } TCRM;

      virtual MRI_Message Register(std::string const& TIalias, TIRM const& tirm) = 0;
      virtual MRI_Message Register(std::string const& TCalias, TCRM const& tcrm) = 0;
      virtual TCRM Get(std::string const& TCalias) const = 0;
      virtual MRI_Message Deregister(std::string const& TCalias) = 0;
   } TMI;
}
#endif // !TPS_TEXTUREMANAGERINTFC
