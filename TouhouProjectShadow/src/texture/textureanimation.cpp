#include "../../include/texture/textureanimation.hpp"

namespace TouhouProjectShadow {
class TextureAnimation::Impl {
public:
   TMI::Handle TMIH;
   /*
    * Renderable Entity Animation Execute Slot Map
    */
   RWMUTEX _RAESM_lock;
   std::map<REES, AnimationSequence> _REAESM;
   typedef struct executerecord {
      UNIQUEMUTEX record_lock;
      float consumedtime;
      AS animationsequence;
      executerecord(float const& temp0, AS const& as) {
         consumedtime = temp0;
         animationsequence = as; 
      }
   } ER;
   RWMUTEX _UICER_lock;
   std::map<AEM, std::shared_ptr<executerecord>> _UICER;

   Impl(TMI::Handle& handle) {
      TMIH = handle;
   }
   ~Impl(void) {
      TMIH.reset();
   }
   MRI_Message PreloadExecutionSlot(
         REES const& rees, AS const& as) {
      MRI_CreatMessage(re);
      {
         SYNCBLOCK_RW_UNIQUELOCK(_RAESM_lock);
         _REAESM[rees] = as;
      }
#ifndef MRI_CLOSEMESSAGE
      bool findrees;
      {
         SYNCBLOCK_RW_SHAREDLOCK(_RAESM_lock);
         findrees = _REAESM.find(rees) != _REAESM.end();
      }
      if (findrees) {
         MRI_SetMessage(re, Info, None,
            "Successfun to modify Animation Execute Slot:" + 
            rees.to_string());
      }
      else {
         MRI_SetMessage(re, Info, None, 
            "Successfun to create Animation Execute Slot:" +
            rees.to_string());
      }
#endif // !MRI_CLOSEMESSAGE
      MRI_Retrun(re);
   }
   AnimationSequence ReadExecutionSlot(REES const& rees) {
      AnimationSequence re;
      {
         SYNCBLOCK_RW_SHAREDLOCK(_RAESM_lock);
         auto finditerator = _REAESM.find(rees);
         if (finditerator != _REAESM.end()) {
            re = (*finditerator).second;
         }
      }
      return re;
   }
   MRI_Message ExecuteSlot(AEM const& aem) {
      MRI_CreatMessage(re);
      bool findedAS = false;
      AS animationsequence;
      {
         SYNCBLOCK_RW_SHAREDLOCK(_RAESM_lock);
         auto iterator = _REAESM.find(aem.rees);
         if (iterator != _REAESM.end()) {
            findedAS = true;
            animationsequence = (*iterator).second;
         }
      }
      if (findedAS) {
         if (ExecuteSlotIsFinished(aem)) {
            {
               SYNCBLOCK_RW_UNIQUELOCK(_UICER_lock);
               _UICER[aem] = std::make_shared<ER>(static_cast<float>(0.0), animationsequence);
            }
         }
         else {
            MRI_SetMessage(re, Warring, ParametersUnReasonable,
               "The animation of " + aem.uic.to_string() +
               " is already in running. Execution animation sequence cancel");
         }
      }
      else {
         MRI_SetMessage(re, Debug, ParametersUnReasonable,
            "The animation execute slot:" + aem.rees.to_string() + 
            " is not presence");
      }
      MRI_Retrun(re);
   }
   bool ExecuteSlotIsFinished(AEM const& uic) {
      SYNCBLOCK_RW_SHAREDLOCK(_UICER_lock);
      auto finditerator = _UICER.find(uic);
      return finditerator == _UICER.end();
   }
   MRI_Messagequeue Update(float const& timeinterval) {
      MRI_CreatMessageQueue(re);
      std::map<AEM, std::shared_ptr<executerecord>>::iterator iterator;
      {
         SYNCBLOCK_RW_SHAREDLOCK(_UICER_lock);
         iterator = _UICER.begin();
      }
      auto IteratorFinished = [&](void) -> bool {
         SYNCBLOCK_RW_SHAREDLOCK(_UICER_lock);
         return iterator != _UICER.end();
      };
      while (IteratorFinished()) {
         auto ptr = (*iterator).second;
         {
            SYNCBLOCK_LOCK(ptr->record_lock);
            ptr->consumedtime += timeinterval;
            if (ptr->consumedtime > ptr->animationsequence.duration) {
               MRI_PushMessageInQueue_Creat(re, Info, None,
                  "Animation sequence of UIC:" + 
                  (*iterator).first.to_string() + "is finished");
               {
                  SYNCBLOCK_RW_UNIQUELOCK(_UICER_lock);
                  iterator = _UICER.erase(iterator);
               }
            }
            else {
               switch (ptr->animationsequence.animationsequencetype) {
                  case AS::AST::Frame: {
                     if (ptr->animationsequence.TCaliasSequence.size() != 0 &&
                        ptr->animationsequence.duration > 0) {
                        MRI_PushMessageInQueue_RV(re, TMIH->Set((*iterator).first.uic, TMIH->ReadTextureCoordmap((ptr->animationsequence.TCaliasSequence)[static_cast<uint16_t>(ptr->consumedtime / ptr->animationsequence.duration * ptr->animationsequence.TCaliasSequence.size())])))
                     }
                     else {
                        MRI_PushMessageInQueue_Creat(re, Debug, ParametersUnReasonable,
                           "Animation sequence of UIC:" +
                           (*iterator).first.to_string() + "TCalias is empty");
                     }
                     break;
                  }
                  case AS::AST::Translation: {
                     if (ptr->animationsequence.ParameterSequence.size() != 0) {
                        auto increment =
                           ptr->animationsequence.ParameterSequence[0] *
                           (ptr->consumedtime / ptr->animationsequence.duration);
                        auto getcoordmap = TMIH->Get((*iterator).first.uic);
                        for (auto& i : getcoordmap.coordmap) {
                           i += increment;
                        }
                        MRI_PushMessageInQueue_RV(re, TMIH->Set((*iterator).first.uic, getcoordmap));
                     }
                     else {
                        MRI_PushMessageInQueue_Creat(re, Debug, ParametersUnReasonable,
                           "Animation sequence of UIC:" +
                           (*iterator).first.to_string() + "Parameter is empty");
                     }
                     break;
                  }
                  case AS::AST::Zoom: {
                     if (ptr->animationsequence.ParameterSequence.size() != 0) {
                        auto increment =
                           ptr->animationsequence.ParameterSequence[0] *
                           (ptr->consumedtime / ptr->animationsequence.duration);
                        auto getcoordmap = TMIH->Get((*iterator).first.uic);
                        getcoordmap.texturesizezoom += increment;
                        MRI_PushMessageInQueue_RV(re, TMIH->Set((*iterator).first.uic, getcoordmap));
                     }
                     else {
                     MRI_PushMessageInQueue_Creat(re, Debug, ParametersUnReasonable,
                        "Animation sequence of UIC:" +
                        (*iterator).first.to_string() + "Parameter is empty");
                     }
                     break;
                  }
                  default:
                     MRI_PushMessageInQueue_Creat(re, Error, ParametersUnReasonable,
                        "Unknow animation sequence type");
                     break;
               }
               iterator++;
            }
         }
      }
      MRI_Retrun(re);
   }
};

TextureAnimation::TextureAnimation(TMI::Handle& handle) {
   pImpl = std::make_unique<Impl>(handle);
}
TextureAnimation::TextureAnimation(TextureAnimation&& r) noexcept {
   pImpl = std::move(r.pImpl);
}
EXPANSIONIMPL_2(TextureAnimation, MRI_Message, PreloadExecutionSlot, REES const&, AS const&);
EXPANSIONIMPL_1(TextureAnimation, TextureAnimation::AS, ReadExecutionSlot, REES const&);
EXPANSIONIMPL_1(TextureAnimation, MRI_Message, ExecuteSlot, AEM const&);
EXPANSIONIMPL_1_CONST(TextureAnimation, bool, ExecuteSlotIsFinished, AEM const&);
EXPANSIONIMPL_1(TextureAnimation, MRI_Messagequeue, Update, float const&);
}