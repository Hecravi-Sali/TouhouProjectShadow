#pragma once
#ifndef TPS_RENDERABLEENTITYINTFC
#define TPS_RENDERABLEENTITYINTFC

#include "renderableentitycontrol_intfc.hpp"
#include "renderableentitydraw_intfc.hpp"

namespace TouhouProjectShadow {
   typedef class RenderableEntity_intfc : public RECI, public REDI {
   public:
      virtual ~RenderableEntity_intfc(void) = default;
      typedef RenderableEntity_intfc* REIHandle;
   } REI;
}
#endif // !TPS_RENDERABLEENTITYINTFC


