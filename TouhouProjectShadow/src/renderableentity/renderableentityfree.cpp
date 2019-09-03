#include "../../include/renderableentity/renderableentityfree.hpp"

namespace TouhouProjectShadow {
class RenderableEntityFree::Impl {
private:
   UIC _uic;
   TMI::Handle _TMH;
   std::shared_ptr<UNIQUEMUTEX> _OpenGLContextLock;

   RWMUTEX _position_lock;
   Vec2f _position;
   UNIQUEMUTEX _set_position_lock;
   bool _set_positon_effective = false;
   Vec2f _set_position;
   UNIQUEMUTEX _imcrement_position_lock;
   std::vector<Vec2f> _imcrement_position_list;

   RWMUTEX _speed_lock;
   Vec2f _speed;
   UNIQUEMUTEX _set_speed_lock;
   bool _set_speed_effective = false;
   Vec2f _set_speed;
   UNIQUEMUTEX _imcrement_speed_lock;
   std::vector<Vec2f> _imcrement_speed_list;

   RWMUTEX _collisionrange_lock;
   float collisionrange = static_cast<float>(0.0);
   UNIQUEMUTEX _set_range_lock;
   Vec2f _set_range;
public:

   MRI_Message Config(Attributes const& attributes) {
      MRI_CreatMessage(re);
      _position = attributes.position;
      _speed = attributes.speed;
      collisionrange = attributes.collisionrange;
      auto tcpm = _TMH->ReadTextureCoordmap(attributes.TCalias);
      if (tcpm.coordmap.size() != 0) {
         if (_TMH->Get(_uic).coordmap.size() == 0) {
            MRI_MessageCopy_RV(re, 
               _TMH->Create(_uic, attributes.TCalias));
         }
         else {
            MRI_MessageCopy_RV(re, _TMH->Set(_uic, tcpm));
         }
      }
      else {
         MRI_SetMessage(re, Warring, ParametersUnReasonable,
            "TCalias: " + attributes.TCalias + 
            "is not presence, Config entity of UIC: " +
            _uic.to_string() + " not successful");
      }
      MRI_Retrun(re);
   }
   Vec2f GetPosition(void) {
      SYNCBLOCK_RW_SHAREDLOCK(_position_lock);
      return _position;
   }
   void SetPosition(Vec2f const& setposition) {
      SYNCBLOCK_LOCK(_set_position_lock);
      _set_positon_effective = true;
      _set_position = setposition;
   }
   void IncrementChangePosition(Vec2f const& increment) {
      SYNCBLOCK_LOCK(_imcrement_position_lock);
      _imcrement_position_list.push_back(increment);
   }
   Vec2f GetSpeed(void) {
      SYNCBLOCK_RW_SHAREDLOCK(_speed_lock);
      return _speed;
   }
   void SetSpeed(Vec2f const& setspeed) {
      SYNCBLOCK_LOCK(_set_speed_lock);
      _set_speed_effective = true;
      _set_speed = setspeed;
   }
   void IncrementChangeSpeed(Vec2f const& increment) {
      SYNCBLOCK_LOCK(_imcrement_speed_lock);
      _imcrement_speed_list.push_back(increment);
   }
   float GetCollisionRange(void) {
      SYNCBLOCK_RW_SHAREDLOCK(_collisionrange_lock);
      return collisionrange;
   }
   void SetCollisionRange(float const& range) {
      SYNCBLOCK_LOCK(_set_range_lock);
      _set_range = range;
   }
   UIC const GetUIC(void) {
      return _uic;
   }
   MRI_Message Draw(void) {

   }
   void Update(float const& timeinterval) {

   }
};
}