#pragma once
#ifndef TPS_RENDERABLEENTITYMANAGERINTFC
#define TPS_RENDERABLEENTITYMANAGERINTFC

#include "../generalpurposetype/generalpurposetype.hpp"
#include "renderableentitycontrol_intfc.hpp"

namespace TouhouProjectShadow {
   /*
    * ����Ⱦʵ������������¼��REMI��
    * REMI���𴴽������¡�����͹���<����Ⱦʵ��>
    *
    * �����ǿ�����ģ��ڷ����ڲ�ʵ����ͬ���������ⲿ�����߲���Ҫ�������ͬ��������
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
       * Feature��
       *    ����һ��<����Ⱦʵ��>�����ظ�ʵ���<���ƾ��-RECI>����ִ��RECI�涨����ز���
       * This method is equivalent to��
       *    RECI::RECIHandle createdRE;
       *    @REMI->Create(createdRE);
       *    // ��ʼ��createdRE�����߽�������������
       *    ...
       * Precautions��
       *    �������<����Ⱦʵ��>�����ʹ��Registerע���REMI��REMI�ǲ���Ը�ʵ�����
       *       ��Ⱦ�����µȲ����������޷��ͷ��ڴ棬ֱ��REMI��������
       */
      virtual MRI_Message Create(RECI::Handle&) const = 0;
      /*
       * Feature��
       *    ͨ��UIC���һ��<����Ⱦʵ��>�������ڴ�ռ䲢��TMI��ע����ʵ����ص���ͼӳ�䡣
       *    ��������ȸ���<����Ⱦʵ�������>����TAI��<����ִ�в�Destory>�������ڶ���
       *    ���Ž������ͷ��ڴ�ռ�
       * This method is equivalent to��
       *
       * Precautions��
       */
      virtual MRI_Message Destroy(UIC const&) = 0;
      // �� ����Ⱦʵ�� ע��� ����Ⱦʵ������� �����Զ�����ע���ڸ�ʵ�������е�
      // <����ִ�в�Creat>�µĶ��� 
      // �Զ��� TextureManager ��ע��� ����Ⱦʵ�� �� ��ͼʵ��
      virtual MRI_Message Register(REGMP const&, UIC const&) = 0;

      virtual RECIHL Get(REGMP::REC const&) const = 0;
      virtual MRI_Message Get(UIC const&, RECI::Handle&) const = 0;
      //  Render all entity & Update all entity position
      virtual MRI_Messagequeue Update(const float& timeinterval) = 0;
   } REMI;
}
#endif // !TPS_RENDERABLEENTITYMANAGERINTFC
