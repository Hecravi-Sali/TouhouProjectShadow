#pragma once
#ifndef TPS_PHYSICALEFFECTMANAGER
#define TPS_PHYSICALEFFECTMANAGER

#include "physicaleffect_intfc.hpp"

namespace TouhouProjectShadow {
   typedef class PhysicalEffectManager_intfc : public MRI {
   public:
      virtual ~PhysicalEffectManager_intfc(void) = default;

      typedef struct RenderableEntityExecutionSlot {
         REMI::EGMP::REC basecamp;
         MAKE_ENUMCLASS(ExecuteSlotType, ELT,
            Boundary, Collision, Gravity, ZoomCollisionRange
         );
         ELT executionslottype;
      } REES;
      typedef struct PhysicalEffectRegistrationMessage {
         REES repet;
         PEI::IPL initializationparameterlist;
         std::vector<REMI::EGMP::REC> objectivecamp;
      } PERM;

      virtual MRI_Message Register(PERM const& ipe) = 0;
      virtual MRI_Message Deregister(REES const& repet) = 0;
      virtual MRI_Messagequeue Update(float const& timeinterval) = 0;
   } PEMI;
}
#endif // !TPS_PHYSICALEFFECTMANAGER
