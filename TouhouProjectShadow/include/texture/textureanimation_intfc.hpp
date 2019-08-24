#pragma once
#ifndef TPSTEXTUREANIMATIONINTFC
#define TPSTEXTUREANIMATIONINTFC

#include "..//generalpurposetype/generalpurposetype.hpp"
#include "texturemanager_intfc.hpp"

namespace TouhouProjectShadow {
    typedef class TextureAnimation_intfc : public MRI {
    public:
        virtual ~TextureAnimation_intfc(void) = default;
        typedef TextureAnimation_intfc* TAIHandle;
        
        typedef struct FrameSequence {
            std::vector<std::string> textureimagealias;
            float usedtime;
        } FS;

        typedef struct TranslationSequence {
            Vec2f direction;
            float usedtime;
        } TS;

        virtual MRI_Message Register(
           std::string const& FSalias, FS const& fs) = 0;
        virtual MRI_Message Register(
           std::string const& TSalias, TS const& ts) = 0;
        virtual MRI_Message Execute(
           std::string const& TCalias, 
           std::string const& sequencealias) = 0;
        virtual bool IsFinished(std::string const& TCalias) const = 0;
        virtual MRI_Messagequeue Update(float const& timeinterval) = 0;
    } TAI;
}
#endif // !TPSTEXTUREANIMATIONINTFC
