#pragma once
#ifndef TPS_RENDERABLEENTITYCONTROLINTFC
#define TPS_RENDERABLEENTITYCONTROLINTFC

#include "../generalpurposetype/generalpurposetype.hpp"

namespace TouhouProjectShadow {
   /*
   ���¼��REI
   */
   typedef class RenderableEntityControl_intfc {
   protected:
      virtual ~RenderableEntityControl_intfc(void) = default;
   public:
      typedef RenderableEntityControl_intfc* RECIHandle;
      struct Attributes {
         // ����Ⱦʵ�� �����������е�λ��
         Vec2f position;
         // ����Ⱦʵ�� ���ٶ��ڶ�ά�ռ��еķ���
         //  @RenderableEntityFree 
         //   ���� @position ����ÿ��Update��ʱ�����ı仯
         //   @position(after Update) = @position(before Update) + @timeinterval * @speed(before Update)
         Vec2f speed;
         // ����Ч�������� �е� ��ײЧ�� �ж���ͬ Camp ֮���Ƿ������ײʹ��Բ�ΰ�Χ�н����ж�
         // @collisionrange ��ʾ��Բ����ײ�ж��еİ뾶
         float collisionrange;
         // ����Ⱦʵ�� ��ʼ��ʱ�Ļ�����ͼ�ı����͸���ͼ�����ŵȼ���
         //  �� ����Ⱦʵ������� ע��� ����Ⱦʵ�� ʱ�����Զ��޸Ļ�����ͼ�Ĳ���
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
      virtual void Config(Attributes const&) = 0;
      /*
      * Feature��
          ���@REI�ڵ�ǰ֡���������꣬������Ҳ�� Բ���ж��� ��Բ�Ρ�
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

      * This method is equivalent to��

      * Precautions��
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
