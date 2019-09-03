#pragma once
#ifndef TPS_RENDERABLEENTITYCONTROLINTFC
#define TPS_RENDERABLEENTITYCONTROLINTFC

#include "../messagereport/messagereport_intfc.hpp"
#include "../generalpurposetype/generalpurposetype.hpp"

namespace TouhouProjectShadow {
   /*
    * <����Ⱦʵ��>�Ŀ��ƽӿ�
    * �ṩ���ⲿ�����<����Ⱦʵ��>������������в����ķ�����
    *
    * �����ǿ�����ģ��ڷ����ڲ�ʵ����ͬ���������ⲿ�����߲���Ҫ�������ͬ��������
    */
   typedef class RenderableEntityControl_intfc : virtual public MRI {
   protected:
      virtual ~RenderableEntityControl_intfc(void) = default;
   public:
      typedef std::shared_ptr<RenderableEntityControl_intfc> Handle;
      /*
       * �����б�����һ����ͨ��RECI��ʼ��<����Ⱦʵ��>���������
       * @position ����Ⱦʵ�� �����������е�λ��
       * @speed ����Ⱦʵ�� ���ٶ��ڶ�ά�ռ��еķ���
       *    @RenderableEntityFree ���� @position ����ÿ��Update��ʱ�����ı仯
       *    @position(after Update) = @position(before Update) + @timeinterval * @speed(before Update)
       * @collisionrange ��ʾ��Բ����ײ�ж��еİ뾶
       * @TCalias ��REMIע���<����Ⱦʵ��>ʱ�����Զ��޸Ļ�����ͼ�Ĳ���
       * @texturesizezoom <����Ⱦʵ��>��ʼ��ʱ�Ļ�����ͼ�ı����͸���ͼ�����ŵȼ���
       */
      struct Attributes {
         Vec2f position;
         Vec2f speed;
         float collisionrange = static_cast<float>(0.0);
         std::string TCalias = "";
      };
      /*
      * Feature��
          �ṩͨ��@Attributes�ṹ��һ���Զ�@REI�������õķ�����
      * This method is equivalent to��
          Attributes attributes;
          attributes.position = Vec2f(?, ?);
          attributes.speed = Vec2f(?, ?);
          attributes.collisionrange = ?;
          attributes.TCalias = "?";
          attributes.texturesizezoom = ?;
          @RECI->Config(attributes);
       * Precautions��
          ���ò��� ��Ϊ��������Ч�ġ�
          ���벻�����ָ��
      */
      virtual MRI_Message Config(Attributes const&) = 0;
      /*
      * Feature��
          ���@REI�ڵ�ǰ֡���������꣬������Ҳ��Բ���ж��е�Բ�ġ� 
      * This method is equivalent to��
          auto position = @RECI->GetPosition();
          ...
      * Precautions��
      */
      virtual Vec2f GetPosition(void) const = 0;
      /*
      * Feature��
          ֱ������@RECI���������꣨���¼�����ò�����
      * This method is equivalent to��
          @RECI->SetPosition(Vec2f(?, ?));
      * Precautions��
          ���ò��� �ڵ�ǰ֡������ʱ����Ч��
          �ڵ�ǰ֡�ڵ��������ò���ֻ����Ч���һ�Ρ�
          ���ò����Ḳ�ǵ���ǰ֡�н��е����� ��������λ�� ������
      */
      virtual void SetPosition(Vec2f const&) = 0;
      /*
      * Feature��
          ��������@RECI���������ꡣ
      * This method is equivalent to��
          Vec2f iccp0(?, ?), iccp1(?, ?), iccp2(?, ?);
          @RECI->IncrementChangePosition(iccp1);
          @RECI->IncrementChangePosition(iccp0);
          @RECI->IncrementChangePosition(iccp2);
          // Equivalent to
          // @RECI::position + iccp1 + iccp0 + iccp2;
      * Precautions��
          �������²��� �ڵ�ǰ֡������ʱ����Ч
          �������²��� �ᱻ ���ò��� ���ǵ������µ�ǰ֡�ڽ��е��κ� �������²��� ��Ч��
      */
      virtual void IncrementChangePosition(Vec2f const&) = 0;
      /*
       * Feature��
       *
       * This method is equivalent to��
       *
       * Precautions��
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
