#include "pch.h"

#include "../TouhouProjectShadow/include/texture/texturemanager.hpp"

namespace TouhouProjectShadow {
TEST(TextureManager_inrerface_Case, TextureManager2D_MultThread) {
   auto OpenGLMutex = std::make_shared<UNIQUEMUTEX>();
   TMI::Handle TMH =
      std::make_shared<TextureManager2D>(std::string("F:\Projects\TouhouProjectShadow\TouhouProjectShadow\resource"), OpenGLMutex);
   TMI::TIPM tipm;
   tipm.relativePath = "explode1.png";
   tipm.parameteri.push_back(std::make_pair(GL_GENERATE_MIPMAP, GL_TRUE));
   tipm.parameterf.push_back(std::make_pair(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
   tipm.parameterf.push_back(std::make_pair(GL_TEXTURE_MAG_FILTER, GL_LINEAR));
   tipm.parameterf.push_back(std::make_pair(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
   tipm.parameterf.push_back(std::make_pair(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
   TMH->PreloadTextureImage("hehe", std::move(tipm));
   EXPECT_EQ(1, 1);
   EXPECT_TRUE(true);
}
}