#pragma once
#ifndef TPS_MESSAGEREPORTINTFC
#define TPS_MESSAGEREPORTINTFC

#include <mutex>
#include <thread>
#include <string>
#include <queue>

namespace TouhouProjectShadow {
   /*
    * MAKE_ENUMCLASS 用于定义一个强枚举类，并且提供了EnumtoString方法将枚举类转换成
    *    std::string 用于记录等。
    * 
    * @ECN 为该枚举类的全名。
    * @ALIAS 为该枚举类的别名，用于减少代码长度。
    *
    * 使用：
    * MAKE_ENUMCLASS(EnumClassA, ECA, A, B, C, D);
    * 等同于生成如下片段：
    * typedef enum class EnumClassA {
    *    A, B, C, D
    * } ECA;
    * std::string EnumtoString(EnumClassA const &value) const { ... }
    */
#define MAKE_ENUMCLASS(ECN, ALIAS, ...) \
   typedef enum class ECN { __VA_ARGS__ } ALIAS; \
   std::string EnumtoString(ECN const &value) const { \
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
   /*
    * 消息传递接口（以下简称MRI）用于记录函数调用过程中任何值得注意的操作；调用者函数在
    *    调用含有MRI的函数时可以通过被调用函数执行结束后返回的MRI::Message /
    *    MRI::MessageQueue得知 被调用的函数 以及 被调用的函数调用的函数等返回的任何
    *    需要注意的信息，调用函数可以使用、抛弃、记录或者通过接口返回向上层函数处理。
    *     
    * MRI不需要实例化也不应该被实例化，MRI生成的消息队列可以由MessageLog类进行记录。
    * 可以通过定义MRI_CLOSEMESSAGE宏关闭MRI，以减少性能开销。
    *
    * 使用示例：
    * // Function_A创建了一个消息并返回，Function_A没有调用任何含有MRI接口的函数。
    * MRI_Message Function_A(...) {
    *    MRI_CreatMessage(re);
    *    ...
    *    MRI_SetMessage(Info, None);
    *    MRI_Retrun(re);
    * }
    * // Function_B只在最后返回时调用了含有MRI接口的函数Function_A并返回了消息。
    * MRI_Message Function_B(...) {
    *    MRI_CreatMessage(re);
    *    ...
    *    MRI_MessageCopy_RV(re, A(...));
    *    MRI_Retrun(re);
    *    // 等同于：
    *    // MRI_Retrun_RV(A(...));   
    * }
    * MRI_Messagequeue Function_C(...) {
    *    MRI_CreatMessageQueue(re);
    *    ...
    *    for(...) {
    *        MRI_PushMessageInQueue_RV(A(...));
    *    }
    *    MRI_Return(re);
    * }
    * ...
    */ 
   typedef class MessageReport_intfc {
   public:
      /*
       * 消息重要等级
       * @Error 指代会引起不可忽视的错误，会导致程序退出或者出现无法预料到的情况，需要
       *     终止程序的运行。一般是由于程序在执行过程中出现了空指针、执行了不应该执行的
       *     程序片段或者出现了应该终止的错误等情况造成的。
       * @Warring 指代程序执行过程中出现了失效操作，如文件IO错误、未正确初始化等情况。
       *     一般不会影响程序的正确执行，但可能会导致不期望的程序行为，需要警戒。
       * @Debug 一般用于打印调试信息，如性能计数器等；低于@Warring级别的失效操作也会
       *     列入@Debug级别；该级别的错误指代程序执行过程中出现了异常情况，但在可控范
       *     围内，不会引起无法预料的行为，仅需要注意。
       * @Info 用于记录程序执行过程的轨迹，如记录调用堆栈、报告一些无关紧要的数据用于
       *     分析等。
       */
      MAKE_ENUMCLASS(MessageReportGrade, MRG,
         Error, Warring, Debug, Info);
      /*
       * 消息代码
       * @None 指代该片段的程序执行没有错误、完全符合预期的行为。
       * @UnabletoLocate 无法定位错误地点。一般是由于程序片段创建了消息但没有进行赋
       *     值（程序片段的某些分支没有对消息进行赋值造成的），是程序设计的失误，需要
       *     警戒并修正。
       *     还有可能是@Error等级的错误出现但程序片段无法对错误原因进行定位。
       * @FileSystemI0Fail 文件IO错误，如无法打开文件、主目录设置错误或者文件不存
       *     在等情况。
       * @ParametersUnReasonable 参数不合法，指代被调用函数发现调用函数传递的参数
       *     不符合接口规定。
       * @ExecutionConditionsDestroyed 执行条件被摧毁，如某些资源无法获取或者没有
       *     加载，导致程序片段的执行条件不满足，提前退出。
       * @ImproperCallSequence 不正确的调用顺序。有些接口调用时需要遵循接口定义的调
       *     用顺序，不按顺序调用将会导致该接口无法正常的运行。
       */ 
      MAKE_ENUMCLASS(MessageReportCode, MRC,
         None, UnabletoLocate, FileSystemI0Fail, ParametersUnReasonable,
         ExecutionConditionsDestroyed, ImproperCallSequence);

   protected:
      /*
       * 消息的实例化结构
       * 不应该调用也不应该使用
       */
      struct _Message {
         MRG grade;
         MRC code;
         std::string info;
      };
      typedef std::queue<_Message> _Messagequeue;

   public:
#ifndef MRI_CLOSEMESSAGE
#define MRI_Message MessageReport_intfc::_Message
#else
#define MRI_Message void
#endif

#ifndef MRI_CLOSEMESSAGE
#define MRI_Messagequeue MessageReport_intfc::_Messagequeue
#else
#define MRI_Messagequeue void
#endif

#ifndef MRI_CLOSEMESSAGE
#define MRI_CreatMessage(message) \
        MessageReport_intfc::_Message message = { \
            MessageReport_intfc::MRG::Error, \
            MessageReport_intfc::MRC::UnabletoLocate , \
            "" };
#else
#define MRI_CreatMessage(message) 
#endif

#ifndef MRI_CLOSEMESSAGE
#define MRI_CreatMessageQueue(message) \
        MessageReport_intfc::_Messagequeue message;
#else
#define MRI_CreatMessageQueue(message)
#endif

#ifndef MRI_CLOSEMESSAGE
#define MRI_MessageCopy_RV(dir, src) \
        dir = src;
#else
#define MRI_MessageCopy_RV(dir, src) src;
#endif

#ifndef MRI_CLOSEMESSAGE
#define MRI_SetMessage(message, grade, code, ...) message = { \
        MessageReport_intfc::MRG::grade, \
        MessageReport_intfc::MRC::code, \
        ## __VA_ARGS__};
#else
#define MRI_SetMessage(message, grade, code)
#endif

#ifndef MRI_CLOSEMESSAGE
#define MRI_PushMessageInQueue_RV(messagequeue, message) \
        messagequeue.push(message);
#else
#define MRI_PushMessageInQueue_RV(messagequeue, message) \
        message;
#endif

#ifndef MRI_CLOSEMESSAGE
#define MRI_PushMessageInQueue_Creat(stack, grade, code, str) \
        stack.push({ \
            ErrorReport_intfc::MRG::grade, \
            ErrorReport_intfc::MRC::code, \
            (str)});
#else
#define MRI_PushMessageInQueue_Creat(stack, grade, code, str)
#endif

#ifndef MRI_CLOSEMESSAGE
#define MRI_LinkQueue_RV(dir, src) \
        auto srcqueue = src;\
        while(!srcqueue.empty()) { \
            dir.push(srcqueue.front()); \
            srcqueue.pop(); }
#else
#define MRI_LinkQueue_RV(dir, src) \
        src;
#endif

#ifndef MRI_CLOSEMESSAGE
#define MRI_Retrun(message) \
        return message;
#else
#define MRI_Retrun(message) \
        return ;
#endif

#ifndef MRI_CLOSEMESSAGE
#define MRI_Retrun_RV(message) \
        return message;
#else
#define MRI_Retrun_RV(message) \
        message;
#endif
   } MRI;
}
#endif // !TPS_MESSAGEREPORTINTFC
