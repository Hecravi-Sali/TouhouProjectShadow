#pragma once
#ifndef TPS_GENERALPURPOSETYPE
#define TPS_GENERALPURPOSETYPE

#include <mutex>
#include <thread>
#include <vector>
#include <tuple>
#include <functional>
#include <limits>
#include <map>

#include <gl\glew.h>

#include "../messagereport/messagereport_intfc.hpp"
/*
功能：
用途：
输入输出：
 @input
 @output
注意事项：
对类成员函数而言: 函数调用期间对象是否需要保持引用参数, 是否会释放这些参数.
函数是否分配了必须由调用者释放的空间.
参数是否可以为空指针.
是否存在函数使用上的性能隐患.
如果函数是可重入的, 其同步前提是什么?
*/

/*
* Feature：

* This method is equivalent to：

* Precautions：
*/

namespace TouhouProjectShadow {
#define MAKE_ENUMCLASS(ECN, ALIAS, ...) \
   typedef enum class ECN { __VA_ARGS__ } ALIAS; \
   inline std::string EnumtoString(ECN const &value) const { \
      static std::mutex _lockground;\
      static std::map<ECN, std::string> map; \
      static bool isi = false; \
      std::lock_guard<std::mutex> lock(_lockground);\
      if(!isi){ \
         isi = true; \
         std::string temp, ecstring = #__VA_ARGS__; \
         ECN count = static_cast<ECN>(0); \
         for(uint16_t i = 0; i < ecstring.size(); i++){ \
             if(ecstring[i] != ' ') { \
                temp.push_back(ecstring[i]); \
             } \
             if(ecstring[i] == ',' || i == ecstring.size() - 1) { \
                 if(temp.back() == ',') {\
                    temp.pop_back(); } \
                 map[count] = temp;\
                 count = static_cast<ECN>(static_cast<int>(count) + 1); \
                 temp.clear(); \
             } \
         } \
      } \
      return map[value]; \
   }

   struct Vec2f {
      union { float x, s, vx; };
      union { float y, t, vy; };
      inline Vec2f(void) {
         x = y = 0.0;
      }
      inline Vec2f(float const& a, float const& b) {
         x = a, y = b;
      }
      inline Vec2f(double const& a, double const& b) {
         x = static_cast<float>(a), y = static_cast<float>(b);
      }
      inline void operator=(double const& val) {
         x = y = static_cast<float>(val);
      }
      inline void operator+=(Vec2f const& src) {
         x += src.x, y += src.y;
      }
      inline Vec2f operator*(float const& Magnification) const {
         return Vec2f(x * Magnification, y * Magnification);
      }
      inline void operator*=(float const& Magnification) {
         x *= Magnification;
         y *= Magnification;
      }
      inline Vec2f operator-(Vec2f const& src) const {
         return Vec2f(x - src.x, y - src.y);
      }
   };

   typedef class UniqueIdentificationCode {
   protected:
      UniqueIdentificationCode(uint32_t const& id)
         : _id(id) {
         ;
      }
   public:
      ~UniqueIdentificationCode(void) = default;
      UniqueIdentificationCode(UniqueIdentificationCode const& uic)
         : _id(uic._id) {
         ;
      }
      UniqueIdentificationCode && operator=(
         UniqueIdentificationCode const& uic) const {
         return UniqueIdentificationCode(uic._id);
      }
      bool operator==(UniqueIdentificationCode const& uic) const {
         return _id == uic._id;
      }
      bool operator<(UniqueIdentificationCode const& uic) const {
         return _id < uic._id;
      }
      static bool GetUIC(UIC& uic) {
         static std::mutex _lockground;
         static uint32_t _idcounter = 0;
         std::lock_guard<std::mutex> lock(_lockground);
         if (_idcounter < UINT32_MAX) {
            uic = UIC(_idcounter++);
            return true;
         }
         else {
            return false;
         }
      }
   private:
      const uint32_t _id;
   } UIC;
}
#endif // !TPS_GENERALPURPOSETYPE
