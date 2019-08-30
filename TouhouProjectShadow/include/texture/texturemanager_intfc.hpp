#pragma once
#ifndef TPS_TEXTUREMANAGERINTFC
#define TPS_TEXTUREMANAGERINTFC

#include "../generalpurposetype/generalpurposetype.hpp"

namespace TouhouProjectShadow {
/*
 * ��ͼ�������ӿڣ����¼��TMI��
 * TMI�ṩ��Ԥ������ͼ�ļ��ķ����������ظ����ء��ṩ����ͼ�������ͼ��С�����ŵĹ���
 *    ������
 *
 * �����ǿ�����ģ��ڷ����ڲ�ʵ����ͬ���������ⲿ�����߲���Ҫ�������ͬ��������
 */
typedef class TextureManager_intfc : public MRI {
public:
   typedef std::shared_ptr<TextureManager_intfc> Handle;
   virtual ~TextureManager_intfc(void) = default;
   /*
    * ��ͼԤ������Ϣ�����¼��TIPM��
    * �����ڹ���TMI��ʱ��������ͼ��ľ��Ե�ַ���˴�@relativePathΪ�����ͼ���
    *    ַ��ƫ�ơ�
    *    ��ʵ����TMIʱ����ĵ�ַ�� F:/TextureLib������TIPM�ṩ�ĵ�ַ@relativePath
    *    Ϊ/Airplane/airplane.png����ôTMI�������������ַ���������ͼ��ʵ��λ
    *    �ã�F:/TextureLib/Airplane/airplane.png �����أ����Ըõ�ַ��ΪΨһ
    *    ��ʶ��ֹͬ������ͼ�ļ��ظ����ء�
    * @parameteri �� @parameterf �Ǹ�OpenGL�ӿڴ��ݵĹ��ڸ���ͼ�����ò�����
    * glTexParameteri(GL_TEXTURE_XD, parameteri.frist, parameteri.secoud);
    * glTexParameterf(GL_TEXTURE_XD, parameteri.frist, parameteri.secoud);
    */
   typedef struct TextureImagePreloadMessage {
      std::string relativePath;
      std::vector<std::pair<GLint, GLint>> parameteri;
      std::vector<std::pair<GLint, GLfloat>> parameterf;
   } TIPM;
   /*
    * ��ͼ����ӳ��Ԥ������Ϣ�����¼��TCPM��
    * TCPM�����ṩ����ͼ��ص���ͼ���ꡢ��ͼ��������ͼ��С���ŵĹ���
    */
   typedef struct TextureCoordmapPreloadMessage {
      Vec2f texturesizezoom;
      std::vector<Vec2f> coordmap;
      std::string TIalias;
   } TCPM;
   typedef std::shared_ptr<TextureCoordmapPreloadMessage> TextureCoordmapHandle;
   typedef TextureCoordmapHandle TCHandle;
   /*
    * Ԥ������ͼ�ļ�
    * ͨ��TIPM������ͼ�ļ�����Ϊ����ͼ��һ���϶̵ı���(TIalias)���ڵ��á�
    * ���TIalias����ӳ����ͬһ����ͼ�ļ��������ظ����ء�
    */
   virtual MRI_Message PreloadTextureImage(
      std::string const& TIalias, TIPM const&) = 0;
   /*
    * Ԥ������ͼ������Ϣ
    * ʹ�ñ���(TCalias)��TCPM���ڵ��á�
    */
   virtual MRI_Message PreloadTextureCoordmap(
         std::string const& TCalias, TCPM const&) = 0;
   virtual TCPM&& ReadTextureCoordmap(
         std::string const& TCalias) const = 0;
   /*
    * ����UIC��<Ԥ������ͼ������Ϣ>�ı���������ͼ����ӳ��
    */
   virtual MRI_Message Create(UIC const&, std::string const& TCalias) = 0;
   virtual MRI_Message Destroy(UIC const&) = 0;
   /*
    * ����UIC��ȡ ��ͼӳ��
    * TextureAnimation ����Ҫ�� ��ͼӳ�� ���в�����
    * TextureCoordmap tcm;
    * @TMI->GetTextureCoordmap(uic, tcm);
    * ...
    */
   virtual MRI_Message GetTextureCoordmap(UIC const&, TCHandle&) const = 0;
   virtual std::weak_ptr<GLuint> GetTextureID(
      std::string const& TIalias) const = 0;
} TMI;
}
#endif // !TPS_TEXTUREMANAGERINTFC
