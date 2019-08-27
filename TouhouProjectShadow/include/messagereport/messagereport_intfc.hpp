#pragma once
#ifndef TPS_MESSAGEREPORTINTFC
#define TPS_MESSAGEREPORTINTFC

#include <mutex>
#include <thread>
#include <string>
#include <queue>

namespace TouhouProjectShadow {
   /*
    * MAKE_ENUMCLASS ���ڶ���һ��ǿö���࣬�����ṩ��EnumtoString������ö����ת����
    *    std::string ���ڼ�¼�ȡ�
    * 
    * @ECN Ϊ��ö�����ȫ����
    * @ALIAS Ϊ��ö����ı��������ڼ��ٴ��볤�ȡ�
    *
    * ʹ�ã�
    * MAKE_ENUMCLASS(EnumClassA, ECA, A, B, C, D);
    * ��ͬ����������Ƭ�Σ�
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
    * ��Ϣ���ݽӿڣ����¼��MRI�����ڼ�¼�������ù������κ�ֵ��ע��Ĳ����������ߺ�����
    *    ���ú���MRI�ĺ���ʱ����ͨ�������ú���ִ�н����󷵻ص�MRI::Message /
    *    MRI::MessageQueue��֪ �����õĺ��� �Լ� �����õĺ������õĺ����ȷ��ص��κ�
    *    ��Ҫע�����Ϣ�����ú�������ʹ�á���������¼����ͨ���ӿڷ������ϲ㺯������
    *     
    * MRI����Ҫʵ����Ҳ��Ӧ�ñ�ʵ������MRI���ɵ���Ϣ���п�����MessageLog����м�¼��
    * ����ͨ������MRI_CLOSEMESSAGE��ر�MRI���Լ������ܿ�����
    *
    * ʹ��ʾ����
    * // Function_A������һ����Ϣ�����أ�Function_Aû�е����κκ���MRI�ӿڵĺ�����
    * MRI_Message Function_A(...) {
    *    MRI_CreatMessage(re);
    *    ...
    *    MRI_SetMessage(Info, None);
    *    MRI_Retrun(re);
    * }
    * // Function_Bֻ����󷵻�ʱ�����˺���MRI�ӿڵĺ���Function_A����������Ϣ��
    * MRI_Message Function_B(...) {
    *    MRI_CreatMessage(re);
    *    ...
    *    MRI_MessageCopy_RV(re, A(...));
    *    MRI_Retrun(re);
    *    // ��ͬ�ڣ�
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
       * ��Ϣ��Ҫ�ȼ�
       * @Error ָ�������𲻿ɺ��ӵĴ��󣬻ᵼ�³����˳����߳����޷�Ԥ�ϵ����������Ҫ
       *     ��ֹ��������С�һ�������ڳ�����ִ�й����г����˿�ָ�롢ִ���˲�Ӧ��ִ�е�
       *     ����Ƭ�λ��߳�����Ӧ����ֹ�Ĵ���������ɵġ�
       * @Warring ָ������ִ�й����г�����ʧЧ���������ļ�IO����δ��ȷ��ʼ���������
       *     һ�㲻��Ӱ��������ȷִ�У������ܻᵼ�²������ĳ�����Ϊ����Ҫ���䡣
       * @Debug һ�����ڴ�ӡ������Ϣ�������ܼ������ȣ�����@Warring�����ʧЧ����Ҳ��
       *     ����@Debug���𣻸ü���Ĵ���ָ������ִ�й����г������쳣��������ڿɿط�
       *     Χ�ڣ����������޷�Ԥ�ϵ���Ϊ������Ҫע�⡣
       * @Info ���ڼ�¼����ִ�й��̵Ĺ켣�����¼���ö�ջ������һЩ�޹ؽ�Ҫ����������
       *     �����ȡ�
       */
      MAKE_ENUMCLASS(MessageReportGrade, MRG,
         Error, Warring, Debug, Info);
      /*
       * ��Ϣ����
       * @None ָ����Ƭ�εĳ���ִ��û�д�����ȫ����Ԥ�ڵ���Ϊ��
       * @UnabletoLocate �޷���λ����ص㡣һ�������ڳ���Ƭ�δ�������Ϣ��û�н��и�
       *     ֵ������Ƭ�ε�ĳЩ��֧û�ж���Ϣ���и�ֵ��ɵģ����ǳ�����Ƶ�ʧ����Ҫ
       *     ���䲢������
       *     ���п�����@Error�ȼ��Ĵ�����ֵ�����Ƭ���޷��Դ���ԭ����ж�λ��
       * @FileSystemI0Fail �ļ�IO�������޷����ļ�����Ŀ¼���ô�������ļ�����
       *     �ڵ������
       * @ParametersUnReasonable �������Ϸ���ָ�������ú������ֵ��ú������ݵĲ���
       *     �����Ͻӿڹ涨��
       * @ExecutionConditionsDestroyed ִ���������ݻ٣���ĳЩ��Դ�޷���ȡ����û��
       *     ���أ����³���Ƭ�ε�ִ�����������㣬��ǰ�˳���
       * @ImproperCallSequence ����ȷ�ĵ���˳����Щ�ӿڵ���ʱ��Ҫ��ѭ�ӿڶ���ĵ�
       *     ��˳�򣬲���˳����ý��ᵼ�¸ýӿ��޷����������С�
       */ 
      MAKE_ENUMCLASS(MessageReportCode, MRC,
         None, UnabletoLocate, FileSystemI0Fail, ParametersUnReasonable,
         ExecutionConditionsDestroyed, ImproperCallSequence);

   protected:
      /*
       * ��Ϣ��ʵ�����ṹ
       * ��Ӧ�õ���Ҳ��Ӧ��ʹ��
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
