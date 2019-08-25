#pragma once
#ifndef TPS_PHYSICALEFFECTINTFC
#define TPS_PHYSICALEFFECTINTFC

#include "../generalpurposetype/generalpurposetype.hpp"
#include "../renderableentity/renderableentitymanager_intfc.hpp"
#include "../texture/textureanimation_intfc.hpp"

namespace TouhouProjectShadow {
   typedef class PhysicalEffect_intfc : public MRI {
   public:
      virtual ~PhysicalEffect_intfc(void) = default;
      typedef struct InitializationParameterList {
         std::vector<float_t> parameterlist;
      } IPL;
      virtual MRI_Message Initialization(IPL const& ipl) = 0;
      virtual MRI_Message Register(REMI::RECIHL const& recihl) = 0;
      virtual MRI_Messagequeue Update(float const& timeinterval) = 0;
   } PEI;
}
#endif // !TPS_PHYSICALEFFECTINTFC
