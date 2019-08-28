#pragma once
#ifndef TPS_USERCONTROLKEYBOARDINTFC
#define TPS_USERCONTROLKEYBOARDINTFC

#include "../renderableentity/renderableentitymanager_intfc.hpp"

namespace TouhouProjectShadow {
   typedef class UserControlkeyboard : public MRI {
   public:
      virtual ~UserControlkeyboard(void) = default;
      typedef std::shared_ptr<UserControlkeyboard> Handle;

      MAKE_ENUMCLASS(OperationType, OT,
         Up, Down, Left, Right, 
         Fire0, Fire1, Fire2, Fire3);
      virtual MRI_Message Initial(REMI::REGMP::REC const&) = 0;
      virtual MRI_Message operate(OT const&) = 0;
      virtual MRI_Messagequeue Update(float const& timeinterval) = 0;
   };
}
#endif // !TPS_USERCONTROLKEYBOARDINTFC
