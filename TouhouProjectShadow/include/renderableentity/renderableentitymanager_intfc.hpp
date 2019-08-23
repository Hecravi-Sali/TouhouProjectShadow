#pragma once
#ifndef TPS_RENDERABLEENTITYMANAGERINTFC
#define TPS_RENDERABLEENTITYMANAGERINTFC

#include "..//messagereport//messagereport_intfc.hpp"
#include "..//uniqueidentificationcode/uniqueidentificationcodemanager_intfc.hpp"
#include "renderableentitydraw_intfc.hpp"
#include "renderableentitycontrol_intfc.hpp"

namespace TouhouProjectShadow {
    typedef class RenderableEntityManager_intfc : public MRI {
    public:
        virtual ~RenderableEntityManager_intfc(void) = default;
        typedef RenderableEntityManager_intfc* EMIHandle;
        //  Used to distinguish between different entity logic types (User decision).
        MAKE_ENUMCLASS(Camp, camp0, camp1);
        //  The actual type difference of the entity (stable).
        MAKE_ENUMCLASS(EntityType, FE, PTE);
        typedef struct EntityGroupMarkPair {
            Camp camp;
            EntityType entitytype;
            inline std::string const toString(EMIHandle itemmanager) const {
                return itemmanager->EnumtoString(camp) + ", " + 
                       itemmanager->EnumtoString(entitytype);
            }
        } EGMP;
        //  There are multiple REI maybe in the same group, Obtained REI by mark will return multiple.
        typedef std::vector<RECI::RECIHandle> RECIHL;

        virtual MRI_Message Create(RECI::RECIHandle &) const = 0;
        virtual MRI_Message Register(EGMP const &, RECI::RECIHandle const&) = 0;
        virtual RECIHL Get(EGMP const &) const = 0;
        virtual MRI_Message Get(UICI const &, RECI::RECIHandle &) const = 0;
        //  Render all entity & Update all entity position
        virtual MRI_Messagequeue Update(const float &timeinterval) = 0;
    } REMI;
}
#endif // !TPS_RENDERABLEENTITYMANAGERINTFC
