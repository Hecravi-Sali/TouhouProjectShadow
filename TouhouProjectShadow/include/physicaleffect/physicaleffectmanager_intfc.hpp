#pragma once
#ifndef TPS_PHYSICALEFFECTMANAGER
#define TPS_PHYSICALEFFECTMANAGER

#include "physicaleffect_intfc.hpp"

namespace TouhouProjectShadow {
   typedef class PhysicalEffectManager_intfc : public MRI {
   public:
      virtual ~PhysicalEffectManager_intfc(void) = default;

      typedef enum class PhysicalEffectType {
         Boundary, Collision, Gravity
      } PET;

      typedef struct TheRenderableEntityandPhysicalEffectTypeofPhysicalEffect {
         PET pet;
         REMI::EGMP egmp;
      } REPET;

      typedef struct PhysicalEffectRegistrationMessage {
         REPET repet;
         PEI::IPL ipl;
         std::vector<REMI::EGMP> dir;
      } PERM;

      virtual MRI_Message Register(PERM const& ipe) = 0;
      virtual PERM Get(REPET const& repet) = 0;
      virtual MRI_Message Deregister(REPET const& repet) = 0;
      virtual MRI_Messagequeue Update(float const& timeinterval) = 0;
   } PEMI;
}
#endif // !TPS_PHYSICALEFFECTMANAGER
