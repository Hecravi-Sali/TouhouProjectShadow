#pragma once
#ifndef TPS_RENDERABLEENTITYGENERATEINTFC
#define TPS_RENDERABLEENTITYGENERATEINTFC

#include "../generalpurposetype/generalpurposetype.hpp"
#include "renderableentitymanager_intfc.hpp"

namespace TouhouProjectShadow {
    typedef class RenderableEntityGenerat_intfc : public MRI {
    public:
        virtual ~RenderableEntityGenerat_intfc(void) = default;
        typedef RenderableEntityGenerat_intfc* REGIHandle;

        typedef struct GenerateEvent {
            REMI::EGMP egmp;
            enum class GenerateMode {
                Insitu, vector, round, liner
            } generate_mode;
            uint16_t number;
            struct MarkPoint {
                enum class PointMode{
                    item, fixed
                } mode;
                Vec2f position;
                REMI::EGMP egmp;
            } origin, target, auxiliary;
            enum class Order {
                positive, fixed, negative
            } order;
            std::vector<RECI::Attributes> attributeslist;
            float speed;
            uint16_t timeinterval;
        } GE;

        virtual MRI_Message Register(const GE &, std::string const &GEalias) = 0;
        virtual MRI_Message Execute(std::string const &GEalias) = 0;
        virtual bool const IsFinished(std::string const &GEalias) const = 0;
        virtual MRI_Messagequeue Update(float const &timeinterval) = 0;
    } REGI;
}
#endif // !TPS_RENDERABLEENTITYGENERATEINTFC
