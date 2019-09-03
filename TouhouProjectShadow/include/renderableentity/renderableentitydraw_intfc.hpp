#pragma once
#ifndef TPS_RENDERABLEENTITYDRAWINTFC
#define TPS_RENDERABLEENTITYDRAWINTFC

#include "../generalpurposetype/generalpurposetype.hpp"
#include "..//texture/texturemanager_intfc.hpp"

namespace TouhouProjectShadow {
   /*
    * <可渲染实体>的渲染接口（以下简称REDI）
    * REDI提供了关于该<可渲染实体>的绘制相关的封装。
    *
    * 在REDI进行绘图或者更新操作时应该通过内部锁阻塞<可渲染实体>的控制接口的所有操作。
    * REDI不需要重入也不应该重入，因为<可渲染实体>只会由唯一的<REMI>进行管理。
    */
   typedef class RenderableEntityDraw_intfc : virtual public MRI {
   public:
      virtual ~RenderableEntityDraw_intfc(void) = default;
      typedef std::shared_ptr<RenderableEntityDraw_intfc> REDIHandle;

      virtual MRI_Message Draw(void) = 0;
      virtual void Update(float const& timeinterval) = 0;
   } REDI;
}
#endif // !TPS_RENDERABLEENTITYDRAWINTFC
