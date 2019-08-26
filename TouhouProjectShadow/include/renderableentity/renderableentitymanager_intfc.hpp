#pragma once
#ifndef TPS_RENDERABLEENTITYMANAGERINTFC
#define TPS_RENDERABLEENTITYMANAGERINTFC

#include "../generalpurposetype/generalpurposetype.hpp"
#include "renderableentitycontrol_intfc.hpp"

namespace TouhouProjectShadow {
   typedef class RenderableEntityManager_intfc : public MRI {
   public:
      virtual ~RenderableEntityManager_intfc(void) = default;
      typedef RenderableEntityManager_intfc* EMIHandle;

      typedef struct EntityGroupMarkPair {
         //  The actual type difference of the entity (stable).
         MAKE_ENUMCLASS(RenderableEntityType, RET, Free, PathTracking, unknow);
         //  Used to distinguish between different entity logic types (User decision).
         MAKE_ENUMCLASS(RenderableEntityCamp, REC, camp0, camp1, unknow);
         EntityGroupMarkPair(void) {
            ret = RET::unknow;
            rec = REC::unknow;
         }
         RET ret;
         REC rec;
         inline std::string const toString(EntityGroupMarkPair const &egmp) const {
            return egmp.EnumtoString(ret) + ", " + egmp.EnumtoString(rec);
         }
      } EGMP;
      //  There are multiple REI maybe in the same group, Obtained REI by mark will return multiple.
      typedef std::vector<RECI::RECIHandle> RECIHL;

      // 创建一个 可渲染实体 并返回该实体的 控制句柄 用于执行 控制句柄 规定的相关操作
      virtual MRI_Message Create(RECI::RECIHandle&) const = 0;
      virtual MRI_Message Decreate(RECI::RECIHandle&) = 0;
      // 将 可渲染实体 注册后 可渲染实体管理器 将会自动调用注册在该实体类型中的 动画执行槽Creat 下的动画 
      // 自动在 TextureManager 中注册该 可渲染实体 的 贴图实例
      virtual MRI_Message Register(EGMP const&, RECI::RECIHandle const&) = 0;
      // 根据 唯一标识码 清除 可渲染实体，将会自动调用注册在该实体类型中的 动画执行槽Destory 下的动画
      virtual MRI_Message Deregistre(UIC const&) = 0;

      virtual RECIHL Get(EGMP::REC const&) const = 0;
      virtual MRI_Message Get(UIC const&, RECI::RECIHandle&) const = 0;
      //  Render all entity & Update all entity position
      virtual MRI_Messagequeue Update(const float& timeinterval) = 0;
   } REMI;
}
#endif // !TPS_RENDERABLEENTITYMANAGERINTFC
