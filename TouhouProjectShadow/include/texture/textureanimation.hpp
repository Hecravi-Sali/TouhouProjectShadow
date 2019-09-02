#pragma once
#ifndef TPS_TEXTUREANIMATION
#define TPS_TEXTUREANIMATION

#include "textureanimation_intfc.hpp"

namespace TouhouProjectShadow {
class TextureAnimation : public TAI {
public:
   TextureAnimation(TMI::Handle&);
   TextureAnimation(TextureAnimation const&) = delete;
   TextureAnimation operator=(TextureAnimation const&) = delete;
   TextureAnimation(TextureAnimation&&) noexcept;
   TextureAnimation& operator=(TextureAnimation&&) = delete;

   virtual MRI_Message PreloadExecutionSlot(
         REES const&, AS const&) override;
   AnimationSequence ReadExecutionSlot(REES const&) override;
   virtual MRI_Message ExecuteSlot(AEM const&) override;
   virtual bool ExecuteSlotIsFinished(AEM const&) const override;
   virtual MRI_Messagequeue Update(float const& timeinterval) override;
private:
   class Impl;
   std::unique_ptr<Impl> pImpl;
};
}
#endif // !TPS_TEXTUREANIMATION
