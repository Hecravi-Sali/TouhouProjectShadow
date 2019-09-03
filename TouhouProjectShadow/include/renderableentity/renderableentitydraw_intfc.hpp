#pragma once
#ifndef TPS_RENDERABLEENTITYDRAWINTFC
#define TPS_RENDERABLEENTITYDRAWINTFC

#include "../generalpurposetype/generalpurposetype.hpp"
#include "..//texture/texturemanager_intfc.hpp"

namespace TouhouProjectShadow {
   /*
    * <����Ⱦʵ��>����Ⱦ�ӿڣ����¼��REDI��
    * REDI�ṩ�˹��ڸ�<����Ⱦʵ��>�Ļ�����صķ�װ��
    *
    * ��REDI���л�ͼ���߸��²���ʱӦ��ͨ���ڲ�������<����Ⱦʵ��>�Ŀ��ƽӿڵ����в�����
    * REDI����Ҫ����Ҳ��Ӧ�����룬��Ϊ<����Ⱦʵ��>ֻ����Ψһ��<REMI>���й���
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
