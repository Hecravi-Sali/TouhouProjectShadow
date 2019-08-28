#pragma once
#ifndef TPS_RENDERABLEENTITYGENERATEINTFC
#define TPS_RENDERABLEENTITYGENERATEINTFC

#include "../generalpurposetype/generalpurposetype.hpp"
#include "renderableentitymanager_intfc.hpp"

namespace TouhouProjectShadow {
   typedef class RenderableEntityGenerat_intfc : public MRI {
   public:
      virtual ~RenderableEntityGenerat_intfc(void) = default;
      typedef std::shared_ptr<RenderableEntityGenerat_intfc> Handle;

      typedef struct GenerateEvent {
         MAKE_ENUMCLASS(GenerateMode, GM,
            Insitu, Vector, Round, Liner, Tracking);
         GM generatemode;
         MAKE_ENUMCLASS(GenerateOrder, GO,
            positive, negative, Fixed);
         GO generateorder;

         uint16_t numberofgenerated;
         struct MarkPoint {
            MAKE_ENUMCLASS(MarkPointMode, MPM, entity, fixed);
            MPM markpointmode;
            Vec2f position;
            REMI::REGMP::REC camp;
         };
         std::vector<MarkPoint> markpointgroup;

         REMI::REGMP::REC generate_renderableentitycamp;
         // 属性列表的大小小于生成实体的个数时，多出的生成实体的属性总是与属性列表的最后相同。
         std::vector<RECI::Attributes> attributeslist;

         float speed;
         // 完成GenerateEvent所需要的时间
         // duration = 0 的情况下所有需要生成的 可渲染实体 都是同时生成的
         // duration ！= 0 的情况下生成所有的 可渲染实体 一共需要 duration 长的时间，
         //  第一个 可渲染实体 的生成的时刻为 GenerateEvent 触发经过
         //  duration/numberofgenerated 长的时间后。
         float duration;
      } GE;

      virtual MRI_Message PreloadGenerateEvent(
         std::string const& GEalias, GE const&) = 0;
      virtual MRI_Message ExecuteGenerateEvent(
         std::string const& GEalias) = 0;
      virtual bool const GenerateEventFinished(
         std::string const& GEalias) const = 0;
      virtual MRI_Messagequeue Update(float const& timeinterval) = 0;
   } REGI;
}
#endif // !TPS_RENDERABLEENTITYGENERATEINTFC
