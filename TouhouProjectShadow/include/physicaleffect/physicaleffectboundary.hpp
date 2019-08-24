#pragma once
#ifndef TPS_PHYSICALEFFECT
#define TPS_PHYSICALEFFECT

#include "physicaleffect_intfc.hpp"

namespace TouhouProjectShadow {
    class PhysicalEffect : public PEI {
    public:
        PhysicalEffect(void) = delete;
        PhysicalEffect(PhysicalEffect const &) = delete;
        PhysicalEffect operator=(PhysicalEffect const &) = delete;

        PhysicalEffect(void);
        ~PhysicalEffect(void);
        MRI_Message Initialization(IPL const& ipl);
        MRI_Message Register(REMI::RECIHL const& recihl);
        MRI_Messagequeue Update(float const& timeinterval);
    private:
        class Impl;
        Impl *pimpl = nullptr;
    };
}
#endif // !TPS_PHYSICALEFFECT
