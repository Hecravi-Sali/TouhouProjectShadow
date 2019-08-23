#pragma once
#ifndef TPS_UNIQUEIDENTIFICATIONCODEINTFC
#define TPS_UNIQUEIDENTIFICATIONCODEINTFC

namespace TouhouProjectShadow {
    typedef class UniqueIdentificationCode_intfc {
    public:
        virtual ~UniqueIdentificationCode_intfc(void) = default;
        virtual UICI& operator=(UICI const &) = 0;
        virtual bool operator==(UICI const &) const = 0;
        virtual bool operator<(UICI const &) const = 0;
    } UICI;
}
#endif // !TPS_UNIQUEIDENTIFICATIONCODE
