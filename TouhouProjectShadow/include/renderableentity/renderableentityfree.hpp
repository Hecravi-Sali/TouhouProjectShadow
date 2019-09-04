#pragma once
#ifndef TPS_RENDERABLEENTITYFREE
#define TPS_RENDERABLEENTITYFREE

#include "../texture/texturemanager_intfc.hpp"
#include "renderableentity_intfc.hpp"

namespace TouhouProjectShadow {
class RenderableEntityFree : public REI {
public:
   RenderableEntityFree(UIC&, TMI::Handle&, std::shared_ptr<UNIQUEMUTEX>);
   RenderableEntityFree(RenderableEntityFree const&) = delete;
   RenderableEntityFree operator=(RenderableEntityFree const&) = delete;
   RenderableEntityFree(RenderableEntityFree&&) noexcept;
   RenderableEntityFree& operator=(RenderableEntityFree&&) = delete;

   virtual MRI_Message Config(Attributes const&) override;
   virtual Vec2f GetPosition(void) const override;
   virtual void SetPosition(Vec2f const&) override;
   virtual void IncrementChangePosition(Vec2f const&) override;
   virtual Vec2f GetSpeed(void) const override;
   virtual void SetSpeed(Vec2f const&) override;
   virtual void IncrementChangeSpeed(Vec2f const&) override;
   virtual float GetCollisionRange(void) const override;
   virtual void SetCollisionRange(float const&) override;
   virtual UIC GetUIC(void) const override;

   virtual MRI_Message Draw(void) const override;
   virtual void Update(float const& timeinterval) override;
private:
   class Impl;
   std::unique_ptr<Impl> pImpl;
};
}
#endif // !TPS_RENDERABLEENTITYFREE
