#pragma once
#ifndef TPS_EVENTTRIGGERINTFC
#define TPS_EVENTTRIGGERINTFC

#include "../messagereport/messagereport_intfc.hpp"
#include "../physicaleffect/physicaleffectmanager_intfc.hpp"
#include "../renderableentity/renderableentitymanager_intfc.hpp"
#include "../texture/texturemanager_intfc.hpp"

namespace TouhouProjectShadow {
   typedef class EventTrigger_intfc : public MRI {
   public:
      virtual ~EventTrigger_intfc(void) = default;

      
   } ETI;
}
#endif // !TPS_EVENTTRIGGERINTFC
