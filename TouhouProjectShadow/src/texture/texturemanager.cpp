#include "../../include/texture/texturemanager.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../include/texture/stb_image/stb_image.h"

namespace TouhouProjectShadow {
   class TextureManager2D::Impl {
   public:
      struct LoadedTexture {
         std::string relativePath;
         GLuint textureid;
      };
      std::map<std::string, GLuint> _absolutepath_textureid;
      std::map<std::string, std::string> _TIalias_absolutepath;
      std::map<std::string, TCPM> _preloadTCPM;

      std::string const _textureabsolutepath;
      
      Impl(std::string const& dir)
         :_textureabsolutepath(dir) {
         ;
      }

      MRI_Message LoadTexture(std::string const& alias, TIPM const& tipm) {
         MRI_CreatMessage(re);
         std::string path = _textureabsolutepath + "/" + tipm.relativePath;
         
         if (_TIalias_absolutepath.find(alias) == _TIalias_absolutepath.end()) {
            if (_absolutepath_textureid.find(path) == _absolutepath_textureid.end()) {
               int width, height, nrChannels;
               unsigned char* imagedata = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
               if (imagedata != nullptr) {
                  GLuint textureid;
                  glGenTextures(1, &textureid);
                  glBindTexture(GL_TEXTURE_2D, textureid);
                  for (auto const i : tipm.parameteri) {
                     glTexParameteri(GL_TEXTURE_2D, i.first, i.second);
                  }
                  for (auto const i : tipm.parameterf) {
                     glTexParameterf(GL_TEXTURE_2D, i.first, i.second);
                  }
                  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagedata);
                  glGenerateMipmap(GL_TEXTURE_2D);
                  stbi_image_free(imagedata);

                  _TIalias_absolutepath[alias] = path;
                  _absolutepath_textureid[path] = textureid;
                  MRI_SetMessage(re, Info, None,
                     "成功读取TextureImage:<" + path + ">，使用别名:<" + alias + ">");
               }
               else {
                  MRI_SetMessage(re, Warring, FileSystemI0Fail,
                     "无法读取TextureImage:<" + path + ">，预期使用别名:<" + alias + ">");
               }
            }
            else {
               _TIalias_absolutepath[alias] = path;
               MRI_SetMessage(re, Info, None,
                  "为TextureImage:<" + path + ">附加别名:<" + alias + ">");
            }
         }
         else {
            MRI_SetMessage(re, Warring, ParametersUnReasonable,
               "别名:<" + alias + ">已经在使用中");
         }
         MRI_Retrun(re);
      }
      
      MRI_Message PreloadTC(std::string const& alias, TCPM const& tcpm) {
         MRI_CreatMessage(re);
         if (_preloadTCPM.find(alias) == _preloadTCPM.end()) {

         }
         else {

         }
         MRI_Retrun(re);
      }
   };
}