#pragma once
#ifndef TPS_UNIQUEIDENTIFICATIONCODEMANAGER
#define TPS_UNIQUEIDENTIFICATIONCODEMANAGER

#include "..//messagereport//messagereport_intfc.hpp"
#include "uniqueidentificationcode_intfc.hpp"

namespace TouhouProjectShadow {
    typedef class UniqueIdentificationCodeManager_intfc : public MRI {
        virtual ~UniqueIdentificationCodeManager_intfc(void) = default;
        typedef UniqueIdentificationCodeManager_intfc* UICMIHanele;

        virtual MRI_Message Get(UICI &) = 0;
    } UICMI;
}
#endif // !TPS_UNIQUEIDENTIFICATIONCODE
