#pragma once
#ifndef TPS_MESSAGEREPORTINTFC
#define TPS_MESSAGEREPORTINTFC

#include "..//generalpurposetype/generalpurposetype.hpp"

namespace TouhouProjectShadow {
    typedef class MessageReport_intfc {
    public:
        enum class Grade {
            Error,
            Warring,
            Debug,
            Info
        };
        enum class Code {
            None,
            UnabletoLocate,
            FileSystemI0Fail,
            ParametersUnReasonable,
            ExecutionConditionsDestroyed
        };
        struct _Message {
            Grade grade;
            Code code;
            std::string info;
        };
        typedef std::queue<_Message> _Messagequeue;

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
            MessageReport_intfc::Grade::Error, \
            MessageReport_intfc::Code::UnabletoLocate , \
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
        MessageReport_intfc::Grade::grade, \
        MessageReport_intfc::Code::code, \
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
            ErrorReport_intfc::Grade::grade, \
            ErrorReport_intfc::Code::code, \
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
