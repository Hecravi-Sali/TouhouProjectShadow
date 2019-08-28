#pragma once
#ifndef TPS_PHYSICALEFFECTMANAGER
#define TPS_PHYSICALEFFECTMANAGER

#include "physicaleffect_intfc.hpp"

namespace TouhouProjectShadow {
   typedef class PhysicalEffectManager_intfc : public MRI {
   public:
      virtual ~PhysicalEffectManager_intfc(void) = default;
      typedef std::shared_ptr<PhysicalEffectManager_intfc> Handle;

      typedef struct RenderableEntityExecutionSlot {
         REMI::REGMP::REC basecamp;
         MAKE_ENUMCLASS(ExecuteSlotType, ELT,
            Boundary, Collision, Gravity, ZoomCollisionRange
         );
         ELT executionslottype;
      } REES;

      typedef struct PhysicalEffectRegistrationMessage {
         REES repet;
         PEI::IPL initializationparameterlist;
         std::vector<REMI::REGMP::REC> objectivecamp;
      } PERM;

      virtual MRI_Message Register(PERM const& ipe) = 0;
      virtual MRI_Message Deregister(REES const& repet) = 0;
      virtual MRI_Messagequeue Update(float const& timeinterval) = 0;
   } PEMI;
}
#endif // !TPS_PHYSICALEFFECTMANAGER
