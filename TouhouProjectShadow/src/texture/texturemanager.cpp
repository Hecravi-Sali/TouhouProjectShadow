#include "../../include/texture/texturemanager.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../include/texture/stb_image/stb_image.h"

namespace TouhouProjectShadow {
class TextureManager2D::Impl {
private:
   std::string const _textureabsolutepath;
   std::shared_ptr<UNIQUEMUTEX> _OpenGLContextLock;
   RWMUTEX _sync_AT;
   std::map<std::string, std::shared_ptr<GLuint>> _absolutepath_textureid;
   RWMUTEX _sync_TA;
   std::map<std::string, std::string> _TIalias_absolutepath;
   RWMUTEX _sync_TCPM;
   std::map<std::string, TCPM> _preloadTCPM;
   RWMUTEX _sync_UT;
   std::map<UIC, TCHandle> _UIC_TC;
public:
   Impl(std::string const& dir, std::shared_ptr<UNIQUEMUTEX>& openglc)
      :_textureabsolutepath(dir) {
      _OpenGLContextLock = openglc;
   }
   ~Impl(void) {
      {
         SYNCBLOCK_RW_UNIQUELOCK(_sync_UT);
         for (auto i = _UIC_TC.begin(); i != _UIC_TC.end(); ) {
            (*i).second.reset();
            i = _UIC_TC.erase(i);
         }
      }
      {
         SYNCBLOCK_LOCK(*_OpenGLContextLock);
         SYNCBLOCK_RW_UNIQUELOCK(_sync_AT);
         for (auto i = _absolutepath_textureid.begin(); 
               i != _absolutepath_textureid.end(); ) {
            GLuint moveid = *((*i).second);
            std::weak_ptr<GLuint> isout((*i).second);
            (*i).second.reset();
            while (isout.use_count() != 0)
               ;
            glDeleteTextures(1, &moveid);
            i = _absolutepath_textureid.erase(i);
         }
      }
   }
   MRI_Message PreloadTextureImage(
         std::string const& alias, TIPM const& tipm) {
      MRI_CreatMessage(re);
      std::string path = _textureabsolutepath + "/" + tipm.relativePath;
      bool TIalias_noused;
      {
         SYNCBLOCK_RW_SHAREDLOCK(_sync_TA);
         TIalias_noused = _TIalias_absolutepath.find(alias) ==
                          _TIalias_absolutepath.end();
      }
      if (TIalias_noused) {
         bool textureimagenotloaded;
         {
            SYNCBLOCK_RW_SHAREDLOCK(_sync_AT);
            textureimagenotloaded = _absolutepath_textureid.find(path) ==
                                    _absolutepath_textureid.end();
         }
         if (textureimagenotloaded) {
            static UNIQUEMUTEX stbilock;
            int width, height, nrChannels;
            unsigned char* imagedata;
            {
               SYNCBLOCK_LOCK(stbilock);
               imagedata = stbi_load(
                  path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
            }
            if (imagedata != nullptr) {
               std::shared_ptr<GLuint> textureid = 
                  std::make_shared<GLuint>();
               {
                  SYNCBLOCK_LOCK(*_OpenGLContextLock);
                  {
                     GLuint temp = 123;
                     glGenTextures(1, &temp);
                     (*textureid) = temp;
                  }
                  glBindTexture(GL_TEXTURE_2D, *(textureid));
                  for (auto const i : tipm.parameteri) {
                     glTexParameteri(GL_TEXTURE_2D, i.first, i.second);
                  }
                  for (auto const i : tipm.parameterf) {
                     glTexParameterf(GL_TEXTURE_2D, i.first, i.second);
                  }
                  glTexImage2D(
                     GL_TEXTURE_2D, 0, GL_RGBA,
                     width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     imagedata);
                  glGenerateMipmap(GL_TEXTURE_2D);
               }
               //  stbi_image_free -> free(imagedata); No need to sync
               stbi_image_free(imagedata);
               {
                  SYNCBLOCK_RW_UNIQUELOCK(_sync_AT);
                  _absolutepath_textureid[path] = textureid;
               }
               {
                  SYNCBLOCK_RW_UNIQUELOCK(_sync_TA);
                  _TIalias_absolutepath[alias] = path;
               }
               MRI_SetMessage(re, Info, None,
                  "Successful to preload texture image file <TIPM>:<" + path + ">, TIPM Alias is:<" + alias + ">");
            }
            else {
               MRI_SetMessage(re, Warring, FileSystemI0Fail,
                  "Fail to preload texture image file <TIPM>:<" + path + ">, TIPM Alias is:<" + alias + ">");
            }
         }
         else {
            {
               SYNCBLOCK_RW_UNIQUELOCK(_sync_TA);
               _TIalias_absolutepath[alias] = path;
            }
            MRI_SetMessage(re, Info, None,
               "Texture image <TIPM>:<" + path + "> is already loaded, Attach Alias:<" + alias + ">");
         }
      }
      else {
         MRI_SetMessage(re, Warring, ParametersUnReasonable,
            "The alias:<" + alias + ">is already in used£¬Can't to preload<TIPM>");
      }
      MRI_Retrun(re);
   }
   MRI_Message PreloadTextureCoordmap(
         std::string const& alias, TCPM const& tcpm) {
      MRI_CreatMessage(re);
      bool findTCPM;
      {
         SYNCBLOCK_RW_SHAREDLOCK(_sync_TCPM);
         findTCPM = _preloadTCPM.find(alias) == _preloadTCPM.end();
      }
      if (findTCPM) {
         {
            SYNCBLOCK_RW_UNIQUELOCK(_sync_TCPM);
            _preloadTCPM[alias] = tcpm;
         }
         MRI_SetMessage(re, Info, None, "Successful to preload<TCPM>, Alias is:<" + alias + ">");
      }
      else {
         MRI_SetMessage(re, Warring, ParametersUnReasonable,
            "The alias:<" + alias + ">is already in used, Can't to preload<TCPM>");
      }
      MRI_Retrun(re);
   }
   TCPM ReadTextureCoordmap(std::string const& TCalias) {
      TCPM re;
      {
         SYNCBLOCK_RW_SHAREDLOCK(_sync_TCPM);
         auto findediterator = _preloadTCPM.find(TCalias);
         if (findediterator != _preloadTCPM.end()) {
            re = (*findediterator).second;
         }
      }
      return std::move(re);
   }
   MRI_Message Create(UIC const& uic, std::string const& TCalias) {
      MRI_CreatMessage(re);
      bool UIC_notcreated;
      {
         SYNCBLOCK_RW_SHAREDLOCK(_sync_UT);
         UIC_notcreated = _UIC_TC.find(uic) == _UIC_TC.end();
      }
      if (UIC_notcreated) {
         {
            SYNCBLOCK_RW_SHAREDLOCK(_sync_TCPM);
            auto findediterator = _preloadTCPM.find(TCalias);
            auto findTCPM = findediterator != _preloadTCPM.end();
            if (findTCPM) {
               {
                  SYNCBLOCK_RW_UNIQUELOCK(_sync_UT);
                  _UIC_TC[uic] = std::make_shared<TCPM>((*findediterator).second);
               }
               MRI_SetMessage(re, Info, None, "Successful to Creat Texturemap for UIC:<" + uic.to_string() + ">");
            }
            else {
               MRI_SetMessage(re, Warring, ImproperCallSequence, "Preload <TCPM> information of alias:<" + TCalias + "> is not presence, Can't creat texturemap fo UIC:<" + uic.to_string() + ">");
            }
         }
      }
      else {
         MRI_SetMessage(re, Error, ParametersUnReasonable, "Repeat creation texturemap fo UIC:<" + uic.to_string() + ">, This operation should not happen");
      }
      MRI_Retrun(re);
   }
   MRI_Message Destroy(UIC const& uic) {
      MRI_CreatMessage(re);
      bool findUIC;
      {
         SYNCBLOCK_RW_UNIQUELOCK(_sync_UT);
         auto findUICiterator = _UIC_TC.find(uic);
         if (findUICiterator != _UIC_TC.end()) {
            _UIC_TC.erase(findUICiterator);
            findUIC = true;
         }
         else {
            findUIC = false;
         }
      }
      if (findUIC) {
         MRI_SetMessage(re, Info, None, "Successful to destory UIC:<" + uic.to_string() + ">");
      }
      else {
         MRI_SetMessage(re, Info, None, "UIC:<" + uic.to_string() + "> is already destory or not created");
      }
      MRI_Retrun(re);
   }
   TCPM Get(UIC const& uic) {
      TCPM re;
      {
         SYNCBLOCK_RW_SHAREDLOCK(_sync_UT);
         auto findUICiterator = _UIC_TC.find(uic);
         if (findUICiterator != _UIC_TC.end()) {
            re = (*(*findUICiterator).second);
         }
      }
      return re;
   }
   MRI_Message Set(UIC const& uic, TCPM const& tcpm) {
      MRI_CreatMessage(re);
      bool setUIC = false;
      {
         SYNCBLOCK_RW_SHAREDLOCK(_sync_UT);
         auto findUICiterator = _UIC_TC.find(uic);
         if (findUICiterator != _UIC_TC.end()) {
            setUIC = true;
            (*(*findUICiterator).second) = tcpm;
         }
      }
#ifndef MRI_CLOSEMESSAGE
      if (setUIC) {
         MRI_SetMessage(re, Info, None,
            "Successful to Set UIC: " +
            uic.to_string() + " texture coord map");
      }
      else {
         MRI_SetMessage(re, Info, None,
            "Texture coord map UIC: " +
            uic.to_string() + " maybe have been destory or not created");
      }
#endif
      MRI_Retrun(re);
   }
   std::weak_ptr<GLuint> Get(std::string const& TIalias) {
      std::weak_ptr<GLuint> re;
      std::string TIabsolutepath;
      {
         SYNCBLOCK_RW_SHAREDLOCK(_sync_TA);
         auto finditerator = _TIalias_absolutepath.find(TIalias);
         if (finditerator != _TIalias_absolutepath.end()) {
            TIabsolutepath = (*finditerator).second;
         }
      }
      {
         SYNCBLOCK_RW_SHAREDLOCK(_sync_AT);
         auto finditerator = _absolutepath_textureid.find(TIabsolutepath);
         if (finditerator != _absolutepath_textureid.end()) {
            re = (*finditerator).second;
         }
      }
      return re;
   }
};

TextureManager2D::TextureManager2D(
      std::string const& dir, std::shared_ptr<UNIQUEMUTEX>& lock){
   pImpl = std::make_unique<Impl>(dir, lock);
}
TextureManager2D::TextureManager2D(TextureManager2D&& tm) noexcept {
   pImpl = std::move(tm.pImpl);
}

EXPANSIONIMPL_2(TextureManager2D, MRI_Message, PreloadTextureImage, std::string const&, TIPM const&);
EXPANSIONIMPL_2(TextureManager2D, MRI_Message, PreloadTextureCoordmap, std::string const&, TCPM const&);
EXPANSIONIMPL_1_CONST(TextureManager2D, TMI::TCPM, ReadTextureCoordmap, std::string const&);
EXPANSIONIMPL_2(TextureManager2D, MRI_Message, Create, UIC const&, std::string const&);
EXPANSIONIMPL_1(TextureManager2D, MRI_Message, Destroy, UIC const&);
EXPANSIONIMPL_1_CONST(TextureManager2D, TextureManager2D::TCPM, Get, UIC const&);
EXPANSIONIMPL_2(TextureManager2D, MRI_Message, Set, UIC const&, TCPM const&);
EXPANSIONIMPL_1_CONST(TextureManager2D, std::weak_ptr<GLuint>, Get, std::string const&);
}
