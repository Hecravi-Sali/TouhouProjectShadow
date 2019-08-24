#pragma once
#ifndef TPS_RENDERABLEENTITYFREEENTITY
#define TPS_RENDERABLEENTITYFREEENTITY

#include "renderableentity_intfc.hpp"

namespace TouhouProjectShadow {
   class RenderableEntityFree : public REI {
   public:
      RenderableEntityFree(void) = delete;
      RenderableEntityFree(RenderableEntityFree const&) = delete;
      RenderableEntityFree operator=(const RenderableEntityFree&) = delete;
      RenderableEntityFree(TMI::TMIHandle, UIC const&);
      ~RenderableEntityFree(void);

      void Config(Attributes const&);
      Vec2f GetPosition(void) const;
      void SetPosition(Vec2f const&);
      void IncrementChangePosition(Vec2f const&);
      Vec2f GetSpeed(void) const;
      void SetSpeed(Vec2f const&);
      void IncrementChangeSpeed(Vec2f const&);
      float GetCollisionRange(void) const;
      void SetCollisionRange(float const&);
      std::string GetTCalias(void) const;
      void SetTCalias(std::string const&);
      Vec2f GetTexturesize(void) const;
      void SetTexturesize(Vec2f const&);
      UIC const GetUIC(void) const;

      MRI_Message Draw(void);
      void Update(float const& timeinterval);
   private:
      class Impl;
      Impl* pimpl = nullptr;
   };
}
#endif // !TPS_RENDERABLEENTITYFREEENTITY