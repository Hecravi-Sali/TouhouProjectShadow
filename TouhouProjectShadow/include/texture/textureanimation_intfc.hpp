#pragma once
#ifndef TPSTEXTUREANIMATIONINTFC
#define TPSTEXTUREANIMATIONINTFC

#include "../generalpurposetype/generalpurposetype.hpp"
#include "../renderableentity/renderableentitymanager_intfc.hpp"
#include "texturemanager_intfc.hpp"

namespace TouhouProjectShadow {
   /*
    * ��ͼ�����ӿڣ����¼��TAI��
    * TAI���� ����Ⱦʵ������ �ṩ����ִ�вۣ�ÿ��ִ�в����ɲ�ͬ�Ĺ��ܴ�������<����ִ��
    *    ��Creat>����<REMI>ע��<����Ⱦʵ��REI>ʱ�Զ����ã�<����ִ�в�Creat>��ִ��
    *    �����󽫻��Զ��ĵ���<����ִ�в�Running>���ظ�ִ�У���������ڣ���
    *    <����ִ�в�Destory>������<REMI>���÷����ݻ�<����Ⱦʵ��REI>ʱ�Զ����á�
    *    ����<����ִ�������>�������û�����Ĵ�����������ִ�С�
    *
    * �����ǿ�����ģ��ڷ����ڲ�ʵ����ͬ���������ⲿ�����߲���Ҫ�������ͬ��������
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
       * ��ͼ��������
       * ��ͼ������Ϊ���֣�һ����֡���ж�����ͨ���̶���ʱ�����滻UIC��ָ���<��ͼ��
       *    ��ӳ��>�е�<TIalias>��<coordmap>���滻��ͬ����ͼ��ʵ�ֶ�����Ч����
       *    ����ƽ�ƶ�����TAI�������<��������@ParameterSequence>�ṩ�Ĳ������ϸ�
       *    ��UIC��ָ���<��ͼ����ӳ��>�е�<coordmap>ʵ��ƽ�Ƶ�Ч����
       *    �������Ŷ�����TAI���ϸ���UIC��ָ���<��ͼ����ӳ��>�е�<texturesizezoo
       *    m>, REDI�ӿ��ṩ�Ļ�ͼ���ܽ��������ŵȼ���Ⱦ��
       */
      typedef struct AnimationSequence {
         MAKE_ENUMCLASS(AnimationSequenceType, AST,
            Frame, Translation, Zoom);
         AST animationsequencetype;
         /*
          * ����ִ��ʱ��
          * ��ָ��������ִ����Ҫ����ʱ�䣬��λ(s)��
          */
         float duration;
         /*
          * ͨ��<Ԥ������ͼ������Ϣ>�ı�����ȡ<TIalias>��<coordmap>���滻UIC��ָ
          *    ���<��ͼ����ӳ��>ʵ��֡���ж�����
          * �ò�������֡���ж���ģʽ����Ч�����@TCaliasSequence�Ĵ�С��֡���ж���
          *    ģʽ�µĴ�СΪ0������Ϊ������Ч�������������Ч����
          */
         std::vector<std::string> TCaliasSequence;
         /*
          * ��ƽ�ƶ���ģʽ�£�@ParameterSequence�еĲ�����Ϊ��������UICָ���<��ͼ
          *    ����ӳ��>�е�<coordmap>������������ָ�ķ���ƽ�ƣ��ƶ��켣��һ��ֱ�ߣ�
          *    ���������Ψһ����ô�����ƶ���һ�����ߣ���ͼ���˶��ٶ��ǹ̶��ġ�
          * �����Ŷ���ģʽ�£���һ����������Ϊ��ͼ����������ź��ֵ�������������ԡ�
          *
          * �����ƽ�ƶ���ģʽ�����Ŷ���ģʽ�²����б�Ĵ�СΪ0������Ϊ������Ч������
          * ��������Ч����
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
