#pragma once
#ifndef TPS_RENDERABLEENTITYMANAGERINTFC
#define TPS_RENDERABLEENTITYMANAGERINTFC

#include "../generalpurposetype/generalpurposetype.hpp"
#include "renderableentitycontrol_intfc.hpp"

namespace TouhouProjectShadow {
   /*
    * 可渲染实体管理器（以下简称REMI）
    * REMI负责创建、更新、清除和管理<可渲染实体>
    *
    * 该类是可重入的，在方法内部实现了同步方法，外部调用者不需要做额外的同步操作。
    */
   typedef class RenderableEntityManager_intfc : public MRI {
   public:
      virtual ~RenderableEntityManager_intfc(void) = default;
      typedef std::shared_ptr<RenderableEntityManager_intfc> Handle;

      typedef struct RenderableEntityGroupMarkPair {
         //  The actual type difference of the entity (stable).
         MAKE_ENUMCLASS(RenderableEntityType, RET, Noinitial,
            Free, PathTracking);
         //  Used to distinguish between different entity logic types (User decision).
         MAKE_ENUMCLASS(RenderableEntityCamp, REC, Noinitial,
            camp0, camp1);
         RET ret = RET::Noinitial;
         REC rec = REC::Noinitial;
         inline std::string const toString(
            RenderableEntityGroupMarkPair const &egmp) const {
            return egmp.EnumtoString(ret) + ", " + egmp.EnumtoString(rec);
         }
      } REGMP;
      //  There are multiple REI maybe in the same group, Obtained REI by mark will return multiple.
      typedef std::vector<RECI::Handle> RECIHL;
      /*
       * Feature：
       *    创建一个<可渲染实体>并返回该实体的<控制句柄-RECI>用于执行RECI规定的相关操作
       * This method is equivalent to：
       *    RECI::RECIHandle createdRE;
       *    @REMI->Create(createdRE);
       *    // 初始化createdRE，或者进行其他操作。
       *    ...
       * Precautions：
       *    创建后的<可渲染实体>如果不使用Register注册进REMI，REMI是不会对该实体进行
       *       渲染、更新等操作，而且无法释放内存，直到REMI被析构。
       */
      virtual MRI_Message Create(RECI::Handle&) const = 0;
      /*
       * Feature：
       *    通过UIC清除一个<可渲染实体>，回收内存空间并在TMI中注销该实体相关的贴图映射。
       *    清除操作先根据<可渲染实体的类型>调用TAI中<动画执行槽Destory>动画，在动画
       *    播放结束后释放内存空间
       * This method is equivalent to：
       *
       * Precautions：
       */
      virtual MRI_Message Destroy(UIC const&) = 0;
      // 将 可渲染实体 注册后 可渲染实体管理器 将会自动调用注册在该实体类型中的
      // <动画执行槽Creat>下的动画 
      // 自动在 TextureManager 中注册该 可渲染实体 的 贴图实例
      virtual MRI_Message Register(REGMP const&, UIC const&) = 0;

      virtual RECIHL Get(REGMP::REC const&) const = 0;
      virtual MRI_Message Get(UIC const&, RECI::Handle&) const = 0;
      //  Render all entity & Update all entity position
      virtual MRI_Messagequeue Update(const float& timeinterval) = 0;
   } REMI;
}
#endif // !TPS_RENDERABLEENTITYMANAGERINTFC
