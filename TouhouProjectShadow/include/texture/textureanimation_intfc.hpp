#pragma once
#ifndef TPSTEXTUREANIMATIONINTFC
#define TPSTEXTUREANIMATIONINTFC

#include "../generalpurposetype/generalpurposetype.hpp"
#include "../renderableentity/renderableentitymanager_intfc.hpp"
#include "texturemanager_intfc.hpp"

namespace TouhouProjectShadow {
   /*
    * 贴图动画接口（以下简称TAI）
    * TAI根据 可渲染实体类型 提供动画执行槽，每个执行槽是由不同的功能触发，如<动画执行
    *    槽Creat>是在<REMI>注册<可渲染实体REI>时自动调用，<动画执行槽Creat>在执行
    *    结束后将会自动的调用<动画执行槽Running>并重复执行（如果它存在）；
    *    <动画执行槽Destory>则是在<REMI>调用方法摧毁<可渲染实体REI>时自动调用。
    *    其他<动画执行扩充槽>则是由用户定义的触发条件触发执行。
    *
    * 该类是可重入的，在方法内部实现了同步方法，外部调用者不需要做额外的同步操作。
    */
   typedef class TextureAnimation_intfc : public MRI {
   public:
      virtual ~TextureAnimation_intfc(void) = default;
      typedef std::shared_ptr<TextureAnimation_intfc> Handle;

      typedef struct RenderableEntityExecutionSlot {
         REMI::REGMP::REC renderableentitycamp;
         MAKE_ENUMCLASS(ExecuteSlotType, ELT,
            Creat, Running, Destory,
            Expansion0, Expansion1, Expansion2, Expansion3);
         ELT executionslottype;
      } REES;
      /*
       * 贴图动画序列
       * 贴图动画分为两种：一种是帧序列动画，通过固定的时间间隔替换UIC所指向的<贴图坐
       *    标映射>中的<TIalias>和<coordmap>，替换不同的贴图以实现动画的效果。
       *    二是平移动画，TAI将会根据<参数序列@ParameterSequence>提供的参数不断更
       *    新UIC所指向的<贴图坐标映射>中的<coordmap>实现平移的效果。
       *    三是缩放动画，TAI不断更新UIC所指向的<贴图坐标映射>中的<texturesizezoo
       *    m>, REDI接口提供的绘图功能将根据缩放等级渲染。
       */
      typedef struct AnimationSequence {
         MAKE_ENUMCLASS(AnimationSequenceType, AST,
            Frame, Translation, Zoom);
         AST animationsequencetype;
         /*
          * 动画执行时长
          * 是指整个动画执行需要多少时间，单位(s)，
          */
         float duration;
         /*
          * 通过<预加载贴图坐标信息>的别名获取<TIalias>和<coordmap>并替换UIC所指
          *    向的<贴图坐标映射>实现帧序列动画。
          * 该参数仅在帧序列动画模式下有效。如果@TCaliasSequence的大小在帧序列动画
          *    模式下的大小为0，则认为动画无效，不会产生动画效果。
          */
         std::vector<std::string> TCaliasSequence;
         /*
          * 在平移动画模式下，@ParameterSequence中的参数作为向量，将UIC指向的<贴图
          *    坐标映射>中的<coordmap>整体向向量所指的方向平移，移动轨迹是一条直线，
          *    如果参数不唯一，那么将会移动出一条折线，贴图的运动速度是固定的。
          * 在缩放动画模式下，第一个参数将作为贴图动画完成缩放后的值，其他参数忽略。
          *
          * 如果在平移动画模式和缩放动画模式下参数列表的大小为0，则认为动画无效，不会
          * 产生动画效果。
          */
         std::vector<Vec2f> ParameterSequence;
      } AS;

      virtual MRI_Message PreloadExecutionSlot(REES const&, AS const&) = 0;
      virtual MRI_Message ExecuteSlot(REES const&, UIC const&) = 0;
      virtual bool ExecuteSlotIsFinished(REES const&, UIC const&) const = 0;
      virtual MRI_Messagequeue Update(float const& timeinterval) = 0;
   } TAI;
}
#endif // !TPSTEXTUREANIMATIONINTFC
