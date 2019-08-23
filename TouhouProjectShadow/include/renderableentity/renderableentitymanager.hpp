#pragma once
#ifndef TPS_RENDERABLEENTITYMANAGER
#define TPS_RENDERABLEENTITYMANAGER

#include "renderableentitymanager_intfc.hpp"

namespace TouhouProjectShadow {
   class RenderableEntityManager : public REMI {
   public:
      RenderableEntityManager(const RenderableEntityManager&) = delete;
      RenderableEntityManager operator= (const RenderableEntityManager&) = delete;

      RenderableEntityManager(TMI::TMIHandle &);
      ~RenderableEntityManager(void);

      MRI_Message Create(RECI::RECIHandle&) const;
      MRI_Message Register(EGMP const&, RECI::RECIHandle const&);
      RECIHL Get(EGMP const&) const;
      MRI_Message Get(UICI const&, RECI::RECIHandle&) const;
      MRI_Messagequeue Update(const float& timeinterval);
   private:
      class Impl;
      Impl* pimpl = nullptr;
   };
}
#endif // !TPS_RENDERABLEENTITYMANAGER
