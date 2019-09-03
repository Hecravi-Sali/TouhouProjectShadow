#pragma once
#ifndef TPS_RENDERABLEENTITYCONTROLINTFC
#define TPS_RENDERABLEENTITYCONTROLINTFC

#include "../messagereport/messagereport_intfc.hpp"
#include "../generalpurposetype/generalpurposetype.hpp"

namespace TouhouProjectShadow {
   /*
    * <可渲染实体>的控制接口
    * 提供了外部类对于<可渲染实体>的物理参数进行操作的方法。
    *
    * 该类是可重入的，在方法内部实现了同步方法，外部调用者不需要做额外的同步操作。
    */
   typedef class RenderableEntityControl_intfc : virtual public MRI {
   protected:
      virtual ~RenderableEntityControl_intfc(void) = default;
   public:
      typedef std::shared_ptr<RenderableEntityControl_intfc> Handle;
      /*
       * 属性列表用于一次性通过RECI初始化<可渲染实体>的物理参数
       * @position 可渲染实体 在世界坐标中的位置
       * @speed 可渲染实体 的速度在二维空间中的分量
       *    @RenderableEntityFree 决定 @position 随着每次Update的时间间隔的变化
       *    @position(after Update) = @position(before Update) + @timeinterval * @speed(before Update)
       * @collisionrange 表示该圆形碰撞判定盒的半径
       * @TCalias 在REMI注册该<可渲染实体>时将会自动修改基础贴图的参数
       * @texturesizezoom <可渲染实体>初始化时的基础贴图的别名和该贴图的缩放等级，
       */
      struct Attributes {
         Vec2f position;
         Vec2f speed;
         float collisionrange = static_cast<float>(0.0);
         std::string TCalias = "";
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
      virtual MRI_Message Config(Attributes const&) = 0;
      /*
      * Feature：
          获得@REI在当前帧的世界坐标，该坐标也是圆形判定盒的圆心。 
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
       *
       * This method is equivalent to：
       *
       * Precautions：
       */
      virtual Vec2f GetSpeed(void) const = 0;
      virtual void SetSpeed(Vec2f const&) = 0;
      virtual void IncrementChangeSpeed(Vec2f const&) = 0;
      virtual float GetCollisionRange(void) const = 0;
      virtual void SetCollisionRange(float const&) = 0;
      virtual UIC const GetUIC(void) const = 0;
   } RECI;
}
#endif // !TPS_RENDERABLEENTITYCONTROLINTFC
