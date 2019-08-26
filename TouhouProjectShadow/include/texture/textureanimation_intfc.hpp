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

      typedef struct RenderableEntityExecutionSlot {
         REMI::EGMP::REC renderableentitycamp;
         MAKE_ENUMCLASS(ExecuteSlotType, ELT,
            Creat, Running, Destory,
            Expansion0, Expansion1, Expansion2, Expansion3);
         ELT executionslottype;
      } REES;
      typedef struct AnimationSequence {
         MAKE_ENUMCLASS(AnimationSequenceType, AST,
            Frame, Translation, Zoom);
         AST animationsequencetype;
         float duration;
         std::vector<std::string> TCaliasSequence;
         std::vector<Vec2f> ParameterSequence;
      } AS;

      virtual MRI_Message PreloadExecutionSlot(
         REES const&, AS const&) = 0;
      virtual MRI_Message ExecuteSlot(REES const&, UIC const&) = 0;
      virtual bool ExecuteSlotIsFinished(
         REES const&, UIC const&) const = 0;
      virtual MRI_Messagequeue Update(float const& timeinterval) = 0;
   } TAI;
}
#endif // !TPSTEXTUREANIMATIONINTFC
