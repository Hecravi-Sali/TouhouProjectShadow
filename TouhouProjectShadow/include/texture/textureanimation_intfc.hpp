#pragma once
#ifndef TPSTEXTUREANIMATIONINTFC
#define TPSTEXTUREANIMATIONINTFC

#include "../generalpurposetype/generalpurposetype.hpp"
#include "../renderableentity/renderableentitymanager_intfc.hpp"
#include "texturemanager_intfc.hpp"

namespace TouhouProjectShadow {
   typedef class TextureAnimation_intfc : public MRI {
   public:
      virtual ~TextureAnimation_intfc(void) = default;
      typedef TextureAnimation_intfc* TAIHandle;

      template<typename T>
      struct AnimationSequence {
         float usedtime;
         std::vector<T> sequence;
      };
      typedef AnimationSequence<std::string> ASFrame;
      typedef AnimationSequence<Vec2f> ASTranslation;

      //  Texture Animation Execute Type
      MAKE_ENUMCLASS(TAET, Creat, Running, Destory, Expansion);
      typedef struct AnimationGroupMarkPair {
         REMI::EGMP egmp;
         TAET taet;
         AnimationSequence<int>* a;
      } AGMP;

      virtual MRI_Message Register(AGMP const&, ASFrame const&) = 0;
      virtual MRI_Message Register(AGMP const&, ASTranslation const&) = 0;
      virtual MRI_Message Execute(AGMP const&, UIC const&) = 0;
      virtual bool IsFinished(UIC const&) const = 0;
      virtual MRI_Messagequeue Update(float const& timeinterval) = 0;
   } TAI;
}
#endif // !TPSTEXTUREANIMATIONINTFC
