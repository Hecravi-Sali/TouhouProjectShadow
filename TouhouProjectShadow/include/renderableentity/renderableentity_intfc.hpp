#pragma once
#ifndef TPS_RENDERABLEENTITYINTFC
#define TPS_RENDERABLEENTITYINTFC

#include "renderableentitycontrol_intfc.hpp"
#include "renderableentitydraw_intfc.hpp"

namespace TouhouProjectShadow {
   /*
    * <可渲染实体>的接口，所有类型的<可渲染实体>均继承自该接口并且实现了了该接口规定的
    *    方法。
    * 外部方法不应该直接使用该接口。
    */
   typedef class RenderableEntity_intfc : public RECI, public REDI {
   public:
      virtual ~RenderableEntity_intfc(void) = default;
      typedef std::shared_ptr<RenderableEntity_intfc> Handle;
   } REI;
}
#endif // !TPS_RENDERABLEENTITYINTFC
