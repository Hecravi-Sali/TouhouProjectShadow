#pragma once
#ifndef TPS_RENDERABLEENTITYCONTROLINTFC
#define TPS_RENDERABLEENTITYCONTROLINTFC

#include "../generalpurposetype/generalpurposetype.hpp"

namespace TouhouProjectShadow {
   typedef class RenderableEntityControl_intfc {
   protected:
      virtual ~RenderableEntityControl_intfc(void) = default;
   public:
      typedef RenderableEntityControl_intfc* RECIHandle;
      struct Attributes {
         //  The position of the center of the renderable entity in world coordinates.
         Vec2f position;
         //  Iteratively update the position of the entity.
         Vec2f speed;
         //  Used to judge collisions or implement advanced physical effects by physical effect.
         float collisionrange;
         //  The TextureCoordinate alias used in the entity rendering process.
         std::string TCalias;
         //  Used to calculate the texture coordinate in wordcoordinates.
         Vec2f texturesize;
         //  Default constructor, providing initialization.
         Attributes(void) {
            position = 0.0;
            speed = 0.0;
            collisionrange = 0.0;
            TCalias = "";
            texturesize = { 1.0,1.0 };
         }
      };
      virtual void Config(Attributes const&) = 0;
      virtual Vec2f GetPosition(void) const = 0;
      virtual void SetPosition(Vec2f const&) = 0;
      virtual void IncrementChangePosition(Vec2f const&) = 0;
      virtual Vec2f GetSpeed(void) const = 0;
      virtual void SetSpeed(Vec2f const&) = 0;
      virtual void IncrementChangeSpeed(Vec2f const&) = 0;
      virtual float GetCollisionRange(void) const = 0;
      virtual void SetCollisionRange(float const&) = 0;
      virtual std::string GetTCalias(void) const = 0;
      virtual void SetTCalias(std::string const&) = 0;
      virtual Vec2f GetTexturesize(void) const = 0;
      virtual void SetTexturesize(Vec2f const&) = 0;
      virtual UIC const GetUIC(void) const = 0;
   } RECI;
}
#endif // !TPS_RENDERABLEENTITYCONTROLINTFC
