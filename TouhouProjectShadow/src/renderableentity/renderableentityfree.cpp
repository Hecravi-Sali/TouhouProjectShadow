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
   bool _set_range_effective = false;
   float _set_range;
public:
   Impl(
         UIC uic, TMI::Handle handle, 
         std::shared_ptr<UNIQUEMUTEX> lock) : _uic(uic) {
      _TMH = handle;
      _OpenGLContextLock = lock;
   }
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
      _set_range_effective = true;
      _set_range = range;
   }
   UIC GetUIC(void) {
      return _uic;
   }
   MRI_Message Draw(void) {
      MRI_CreatMessage(re);
      auto texturecoordmap = _TMH->Get(_uic);
      if (texturecoordmap.coordmap.size() >= 2) {
         auto textureid = _TMH->Get(texturecoordmap.TIalias).lock();
         if (textureid != nullptr) {
            Vec2f renderposition;
            {
               SYNCBLOCK_RW_SHAREDLOCK(_position_lock);
               renderposition = _position;
            }
            Vec2f texturesize = texturecoordmap.coordmap[1] * texturecoordmap.texturesizezoom;
            {
               SYNCBLOCK_LOCK(*_OpenGLContextLock);
               glActiveTexture(GL_TEXTURE0);
               glEnable(GL_TEXTURE_2D);
               glBindTexture(GL_TEXTURE_2D, (*textureid));
               glEnable(GL_BLEND);
               glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
               glBegin(GL_QUADS);
               // Counterclockwise from the lower left corner
               glMultiTexCoord2f(
                  GL_TEXTURE0,
                  texturecoordmap.coordmap[0].s,
                  texturecoordmap.coordmap[0].t);
               glVertex2f(
                  _position.x - texturesize.x,
                  _position.y - texturesize.y);
               glMultiTexCoord2f(
                  GL_TEXTURE0,
                  texturecoordmap.coordmap[0].s + texturecoordmap.coordmap[1].x,
                  texturecoordmap.coordmap[0].t);
               glVertex2f(
                  _position.x + texturesize.x,
                  _position.y - texturesize.y);
               glMultiTexCoord2f(
                  GL_TEXTURE0,
                  texturecoordmap.coordmap[0].s + texturecoordmap.coordmap[1].x,
                  texturecoordmap.coordmap[0].t + texturecoordmap.coordmap[1].y);
               glVertex2f(
                  _position.x + texturesize.x,
                  _position.y + texturesize.y);
               glMultiTexCoord2f(
                  GL_TEXTURE0,
                  texturecoordmap.coordmap[0].s,
                  texturecoordmap.coordmap[0].t + texturecoordmap.coordmap[1].y);
               glVertex2f(
                  _position.x - texturesize.x,
                  _position.y + texturesize.y);
               glEnd();
            }
         }
         else {
            MRI_SetMessage(re, Warring, ExecutionConditionsDestroyed,
               "Can't get texture image id during the rendering process, maybe TMI has been destory or texture image do not exist");
         }
      }
      else {
         MRI_SetMessage(re, Debug, UnabletoLocate,
            "Can't get texture coord map, maybe renderable entity not config or entity has benn destory");
      }
      MRI_Retrun(re);
   }
   void Update(float const& timeinterval) {
      {
         SYNCBLOCK_RW_UNIQUELOCK(_collisionrange_lock);
         SYNCBLOCK_LOCK(_set_range_lock);
         if (_set_range_effective) {
            _set_range_effective = false;
            collisionrange = _set_range;
         }
      }
      {
         SYNCBLOCK_RW_UNIQUELOCK(_position_lock);
         _position += _speed * timeinterval;
      }
      {
         SYNCBLOCK_RW_UNIQUELOCK(_speed_lock);
         SYNCBLOCK_LOCK(_set_speed_lock, 0);
         if (_set_speed_effective) {
            _set_speed_effective = false;
            _speed = _set_speed;
         }
         else {
            SYNCBLOCK_LOCK(_imcrement_speed_lock, 1);
            for (auto const i : _imcrement_speed_list) {
               _speed += i;
            }
            _imcrement_speed_list.shrink_to_fit();
         }
      }
      {
         SYNCBLOCK_RW_UNIQUELOCK(_position_lock);
         SYNCBLOCK_LOCK(_set_position_lock, 0);
         if (_set_positon_effective) {
            _set_positon_effective = false;
            _position = _set_position;
         }
         else {
            SYNCBLOCK_LOCK(_imcrement_position_lock, 1);
            for (auto const i : _imcrement_position_list) {
               _position += i;
            }
            _imcrement_position_list.shrink_to_fit();
         }
      }
   }

};
RenderableEntityFree::RenderableEntityFree(
      UIC& uic, TMI::Handle& handle, std::shared_ptr<UNIQUEMUTEX> lock) {
   pImpl = std::make_unique<Impl>(uic, handle, lock);
}
RenderableEntityFree::RenderableEntityFree(
      RenderableEntityFree&& r) noexcept {
   pImpl = std::move(r.pImpl);
}
EXPANSIONIMPL_1(RenderableEntityFree, MRI_Message, Config, Attributes const&);
EXPANSIONIMPL_0_CONST(RenderableEntityFree, Vec2f, GetPosition);
EXPANSIONIMPL_1(RenderableEntityFree, void, SetPosition, Vec2f const&);
EXPANSIONIMPL_1(RenderableEntityFree, void, IncrementChangePosition, Vec2f const&);
EXPANSIONIMPL_0_CONST(RenderableEntityFree, Vec2f, GetSpeed);
EXPANSIONIMPL_1(RenderableEntityFree, void, SetSpeed, Vec2f const&);
EXPANSIONIMPL_1(RenderableEntityFree, void, IncrementChangeSpeed, Vec2f const&);
EXPANSIONIMPL_0_CONST(RenderableEntityFree, float, GetCollisionRange);
EXPANSIONIMPL_1(RenderableEntityFree, void, SetCollisionRange, float const&);
EXPANSIONIMPL_0_CONST(RenderableEntityFree, UIC, GetUIC);
EXPANSIONIMPL_0_CONST(RenderableEntityFree, MRI_Message, Draw);
EXPANSIONIMPL_1(RenderableEntityFree, void, Update, float const&);
}
