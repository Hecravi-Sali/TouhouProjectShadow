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
 * Ψһ��ʶ�루���¼��UIC����������ÿ�� ����Ⱦʵ�� �ṩһ�����ظ��ı�ǵ��ࡣ
 * �ṩ�˸��ơ��Ƚϵȷ��������Ե�������ʹ�ã�û�з�����Ҫ�������ͷŵ��ڴ�ռ䡣
 *
 * �������ṩ��һ����̬����GetUIC()���ڻ�ȡһ��UIC���÷����������롣
 *
 * UIC myuic(UIC::GetUIC());
 * ����޷���ȡ��ȷ��UIC����UIC�����˴���myuic.isNormal()������false
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
