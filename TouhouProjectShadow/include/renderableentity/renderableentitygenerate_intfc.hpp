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
         // �����б�Ĵ�СС������ʵ��ĸ���ʱ�����������ʵ������������������б�������ͬ��
         std::vector<RECI::Attributes> attributeslist;

         float speed;
         // ���GenerateEvent����Ҫ��ʱ��
         // duration = 0 �������������Ҫ���ɵ� ����Ⱦʵ�� ����ͬʱ���ɵ�
         // duration ��= 0 ��������������е� ����Ⱦʵ�� һ����Ҫ duration ����ʱ�䣬
         //  ��һ�� ����Ⱦʵ�� �����ɵ�ʱ��Ϊ GenerateEvent ��������
         //  duration/numberofgenerated ����ʱ���
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
