#pragma once
#ifndef TPS_USERCONTROLKEYBOARDINTFC
#define TPS_USERCONTROLKEYBOARDINTFC

#include "../renderableentity/renderableentitycontrol_intfc.hpp"

namespace TouhouProjectShadow {
   typedef class UserControlkeyboard : public MRI {
   public:
      virtual ~UserControlkeyboard(void) = default;

      typedef enum Direction {
         Up, Down, Left, Right
      };
   };
}
#endif // !TPS_USERCONTROLKEYBOARDINTFC
