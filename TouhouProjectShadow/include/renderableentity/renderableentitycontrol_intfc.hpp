#pragma once
#ifndef TPS_RENDERABLEENTITYCONTROLINTFC
#define TPS_RENDERABLEENTITYCONTROLINTFC

#include "../generalpurposetype/generalpurposetype.hpp"

namespace TouhouProjectShadow {
   /*
   以下简称REI
   */
   typedef class RenderableEntityControl_intfc {
   protected:
      virtual ~RenderableEntityControl_intfc(void) = default;
   public:
      typedef RenderableEntityControl_intfc* RECIHandle;
      struct Attributes {
         // 可渲染实体 在世界坐标中的位置
         Vec2f position;
         // 可渲染实体 的速度在二维空间中的分量
         //  @RenderableEntityFree 
         //   决定 @position 随着每次Update的时间间隔的变化
         //   @position(after Update) = @position(before Update) + @timeinterval * @speed(before Update)
         Vec2f speed;
         // 物理效果管理器 中的 碰撞效果 判定不同 Camp 之间是否存在碰撞使用圆形包围盒进行判定
         // @collisionrange 表示该圆形碰撞判定盒的半径
         float collisionrange;
         // 可渲染实体 初始化时的基础贴图的别名和该贴图的缩放等级，
         //  在 可渲染实体管理器 注册该 可渲染实体 时将会自动修改基础贴图的参数
         std::string TCalias;
         Vec2f texturesizezoom;
         Attributes(void) {
            position = 0.0;
            speed = 0.0;
            collisionrange = 0.0;
            TCalias = "";
         }
      };
      /*
      * Feature：
          提供通过@Attributes结构体一次性对@REI进行配置的方法。
      * This method is equivalent to：
          Attributes attributes;
          attributes.position = Vec2f(?, ?);
          attributes.speed = Vec2f(?, ?);
          attributes.collisionrange = ?;
          attributes.TCalias = "?";
          attributes.texturesizezoom = ?;
          @RECI->Config(attributes);
       * Precautions：
          配置操作 行为是立即生效的。
          输入不允许空指针
      */
      virtual void Config(Attributes const&) = 0;
      /*
      * Feature：
          获得@REI在当前帧的世界坐标，该坐标也是 圆形判定盒 的圆形。
      * This method is equivalent to：
          auto position = @RECI->GetPosition();
          ...
      * Precautions：
      */
      virtual Vec2f GetPosition(void) const = 0;
      /*
      * Feature：
          直接设置@RECI的世界坐标（以下简称设置操作）
      * This method is equivalent to：
          @RECI->SetPosition(Vec2f(?, ?));
      * Precautions：
          设置操作 在当前帧结束的时候生效。
          在当前帧内的所有设置操作只会生效最后一次。
          设置操作会覆盖掉当前帧中进行的所有 增量更新位置 操作。
      */
      virtual void SetPosition(Vec2f const&) = 0;
      /*
      * Feature：
          增量更新@RECI的世界坐标。
      * This method is equivalent to：
          Vec2f iccp0(?, ?), iccp1(?, ?), iccp2(?, ?);
          @RECI->IncrementChangePosition(iccp1);
          @RECI->IncrementChangePosition(iccp0);
          @RECI->IncrementChangePosition(iccp2);
          // Equivalent to
          // @RECI::position + iccp1 + iccp0 + iccp2;
      * Precautions：
          增量更新操作 在当前帧结束的时候生效
          增量更新操作 会被 设置操作 覆盖掉，导致当前帧内进行的任何 增量更新操作 无效。
      */
      virtual void IncrementChangePosition(Vec2f const&) = 0;
      /*
      * Feature：

      * This method is equivalent to：

      * Precautions：
      */
      virtual Vec2f GetSpeed(void) const = 0;
      virtual void SetSpeed(Vec2f const&) = 0;
      virtual void IncrementChangeSpeed(Vec2f const&) = 0;
      virtual float GetCollisionRange(void) const = 0;
      virtual void SetCollisionRange(float const&) = 0;
      virtual std::string GetTCalias(void) const = 0;
      virtual UIC const GetUIC(void) const = 0;
   } RECI;
}
#endif // !TPS_RENDERABLEENTITYCONTROLINTFC
