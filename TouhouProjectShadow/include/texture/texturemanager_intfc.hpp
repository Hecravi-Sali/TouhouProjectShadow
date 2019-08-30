#pragma once
#ifndef TPS_TEXTUREMANAGERINTFC
#define TPS_TEXTUREMANAGERINTFC

#include "../generalpurposetype/generalpurposetype.hpp"

namespace TouhouProjectShadow {
/*
 * 贴图管理器接口（以下简称TMI）
 * TMI提供了预加载贴图文件的方法，避免重复加载。提供对贴图坐标和贴图大小的缩放的管理
 *    方法。
 *
 * 该类是可重入的，在方法内部实现了同步方法，外部调用者不需要做额外的同步操作。
 */
typedef class TextureManager_intfc : public MRI {
public:
   typedef std::shared_ptr<TextureManager_intfc> Handle;
   virtual ~TextureManager_intfc(void) = default;
   /*
    * 贴图预加载信息（以下简称TIPM）
    * 由于在构造TMI的时候传入了贴图库的绝对地址，此处@relativePath为相对贴图库地
    *    址的偏移。
    *    如实例化TMI时传入的地址是 F:/TextureLib，假设TIPM提供的地址@relativePath
    *    为/Airplane/airplane.png，那么TMI将会根据两个地址计算出该贴图的实际位
    *    置：F:/TextureLib/Airplane/airplane.png 并加载，并以该地址作为唯一
    *    标识防止同样的贴图文件重复加载。
    * @parameteri 和 @parameterf 是给OpenGL接口传递的关于该贴图的配置参数。
    * glTexParameteri(GL_TEXTURE_XD, parameteri.frist, parameteri.secoud);
    * glTexParameterf(GL_TEXTURE_XD, parameteri.frist, parameteri.secoud);
    */
   typedef struct TextureImagePreloadMessage {
      std::string relativePath;
      std::vector<std::pair<GLint, GLint>> parameteri;
      std::vector<std::pair<GLint, GLfloat>> parameterf;
   } TIPM;
   /*
    * 贴图坐标映射预加载信息（以下简称TCPM）
    * TCPM负责提供和贴图相关的贴图坐标、贴图别名和贴图大小缩放的管理。
    */
   typedef struct TextureCoordmapPreloadMessage {
      Vec2f texturesizezoom;
      std::vector<Vec2f> coordmap;
      std::string TIalias;
   } TCPM;
   typedef std::shared_ptr<TextureCoordmapPreloadMessage> TextureCoordmapHandle;
   typedef TextureCoordmapHandle TCHandle;
   /*
    * 预加载贴图文件
    * 通过TIPM加载贴图文件，并为该贴图起一个较短的别名(TIalias)便于调用。
    * 多个TIalias可能映射向同一个贴图文件，避免重复加载。
    */
   virtual MRI_Message PreloadTextureImage(
      std::string const& TIalias, TIPM const&) = 0;
   /*
    * 预加载贴图坐标信息
    * 使用别名(TCalias)绑定TCPM便于调用。
    */
   virtual MRI_Message PreloadTextureCoordmap(
         std::string const& TCalias, TCPM const&) = 0;
   virtual TCPM&& ReadTextureCoordmap(
         std::string const& TCalias) const = 0;
   /*
    * 根据UIC和<预加载贴图坐标信息>的别名创建贴图坐标映射
    */
   virtual MRI_Message Create(UIC const&, std::string const& TCalias) = 0;
   virtual MRI_Message Destroy(UIC const&) = 0;
   /*
    * 根据UIC获取 贴图映射
    * TextureAnimation 类需要对 贴图映射 进行操作。
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
