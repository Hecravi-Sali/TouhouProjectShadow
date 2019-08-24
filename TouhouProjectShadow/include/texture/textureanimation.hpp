#pragma once
#ifndef TPS_TEXTUREANIMATION
#define TPS_TEXTUREANIMATION

#include "textureanimation_intfc.hpp"

namespace TouhouProjectShadow {
    class TextureAnimation : public TAI {
    public:
        TextureAnimation(void) = delete;
        TextureAnimation(const TextureAnimation&) = delete;
        TextureAnimation operator=(const TextureAnimation &) = delete;

        TextureAnimation(TMI::TMIHandle &);
        ~TextureAnimation(void);
        MRI_Message Register(
           std::string const& FSalias, FS const& fs);
        MRI_Message Register(
           std::string const& TSalias, TS const& ts);
        MRI_Message Execute(std::string const&, std::string const&);
        bool IsFinished(std::string const &) const;
        MRI_Messagequeue Update(float const &);
    private:
        class Impl;
        Impl *pimpl = nullptr;
    };
}
#endif // !TPS_TEXTUREANIMATION
