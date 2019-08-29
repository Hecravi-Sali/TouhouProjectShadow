#pragma once
#ifndef TPS_GENERALPURPOSETYPE
#define TPS_GENERALPURPOSETYPE

#include <vector>
#include <map>
#include <tuple>

#include <limits>
#include <functional>

#include <mutex>
#include <shared_mutex>
#include <thread>

#include <gl\glew.h>

#include "../messagereport/messagereport_intfc.hpp"

namespace TouhouProjectShadow {
typedef class TwoDimensionalVectorofFloatingPointType {
public:
   union { float x, s, vx; };
   union { float y, t, vy; };

   explicit TwoDimensionalVectorofFloatingPointType(void) {
      x = y = 0.0;
   }
   explicit TwoDimensionalVectorofFloatingPointType(
      float const& a, float const& b) {
      x = a, y = b;
   }
   explicit TwoDimensionalVectorofFloatingPointType(
      double const& a, double const& b) {
      x = static_cast<float>(a), y = static_cast<float>(b);
   }
   void operator=(double const& val) {
      x = y = static_cast<float>(val);
   }
   void operator+=(
      TwoDimensionalVectorofFloatingPointType const& src) {
      x += src.x, y += src.y;
   }
   TwoDimensionalVectorofFloatingPointType operator*(
      float const& Magnification) const {
      return TwoDimensionalVectorofFloatingPointType(
         x * Magnification, y * Magnification);
   }
   void operator*=(float const& Magnification) {
      x *= Magnification;
      y *= Magnification;
   }
   TwoDimensionalVectorofFloatingPointType operator-(
      TwoDimensionalVectorofFloatingPointType const& src) const {
      return TwoDimensionalVectorofFloatingPointType(x - src.x, y - src.y);
   }
} Vec2f;
/*
 * 唯一标识码（以下简称UIC）是用来给每个 可渲染实体 提供一个不重复的标记的类。
 * 提供了复制、比较等方法，可以当作变量使用，没有分配需要调用者释放的内存空间。
 *
 * 该类下提供了一个静态方法GetUIC()用于获取一个UIC，该方法可以重入。
 *
 * UIC myuic(UIC::GetUIC());
 * 如果无法获取正确的UIC或者UIC出现了错误，myuic.isNormal()将返回false
 */
typedef class UniqueIdentificationCode {
protected:
   UniqueIdentificationCode(uint32_t const& id, bool const& error)
      : _id(id), _error(error) {
      ;
   }
public:
   UniqueIdentificationCode(
      UniqueIdentificationCode const& uic)
      : _id(uic._id), _error(uic._error) {
      ;
   }
   ~UniqueIdentificationCode(void) = default;
   bool operator==(UniqueIdentificationCode const& uic) const {
      return _id == uic._id && !(_error || uic._error);
   }
   bool operator<(UniqueIdentificationCode const& uic) const {
      return _id < uic._id && !(_error || uic._error);
   }
   bool isNormal(void) const {
      return !_error;
   }
   std::string to_string(void) const {
      return std::to_string(_id);
   }
   static UniqueIdentificationCode GetUIC(void) {
      static std::mutex _lockground;
      static uint32_t _idcounter = 0;
      std::lock_guard<std::mutex> lock(_lockground);
      if (_idcounter < UINT32_MAX) {
         return UIC(_idcounter++, false);
      }
      else {
         return UIC(0, true);
      }
   }
private:
   const bool _error;
   const uint32_t _id;
} UIC;

#define RWMUTEX std::shared_mutex
#define SYNCBLOCK_RW_SHAREDLOCK(mutexname) \
   std::shared_lock<std::shared_mutex> _rw_shardlock(mutexname);
#define SYNCBLOCK_RW_UNIQUELOCK(mutexname) \
   std::unique_lock<std::shared_mutex> _rw_uniquelock(mutexname);
#define UNIQUEMUTEX std::mutex
#define SYNCBLOCK_LOCK(mutexname) \
   std::lock_guard<std::mutex> _uniquelock(mutexname);

}
#endif // !TPS_GENERALPURPOSETYPE
