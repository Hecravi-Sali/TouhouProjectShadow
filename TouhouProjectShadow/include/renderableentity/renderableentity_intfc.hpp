#pragma once
#ifndef TPS_RENDERABLEENTITYINTFC
#define TPS_RENDERABLEENTITYINTFC

#include "renderableentitycontrol_intfc.hpp"
#include "renderableentitydraw_intfc.hpp"

namespace TouhouProjectShadow {
   /*
    * <����Ⱦʵ��>�Ľӿڣ��������͵�<����Ⱦʵ��>���̳��Ըýӿڲ���ʵ�����˸ýӿڹ涨��
    *    ������
    * �ⲿ������Ӧ��ֱ��ʹ�øýӿڡ�
    */
   typedef class RenderableEntity_intfc : public RECI, public REDI {
   public:
      virtual ~RenderableEntity_intfc(void) = default;
      typedef std::shared_ptr<RenderableEntity_intfc> Handle;
   } REI;
}
#endif // !TPS_RENDERABLEENTITYINTFC
