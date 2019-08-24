#pragma once
#ifndef TPS_RENDERABLEENTITYDRAWINTFC
#define TPS_RENDERABLEENTITYDRAWINTFC

#include "../generalpurposetype/generalpurposetype.hpp"
#include "..//texture/texturemanager_intfc.hpp"

namespace TouhouProjectShadow {
   typedef class RenderableEntityDraw_intfc : public MRI {
   public :
      virtual ~RenderableEntityDraw_intfc(void) = default;
      typedef RenderableEntityDraw_intfc* REDIHandle;

      virtual MRI_Message Draw(void) = 0;
      virtual void Update(float const& timeinterval) = 0;
   } REDI;
}
#endif // !TPS_RENDERABLEENTITYDRAWINTFC
