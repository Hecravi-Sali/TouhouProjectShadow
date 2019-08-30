#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../TouhouProjectShadow/include/texture/texturemanager.hpp"

using namespace TouhouProjectShadow;

namespace InterfaceLevelTest {
TEST_CLASS(InterfaceLevelTest) {
public:
   void InitialOpenGL(void) {
      Assert::IsTrue(glfwInit());
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
      GLFWwindow* window = glfwCreateWindow(200, 200, "m30", nullptr, nullptr);
      Assert::IsNotNull(window);
      glfwMakeContextCurrent(window);
      Assert::IsFalse(glewInit());
   }

   TEST_METHOD(TMI_MultiThreadedAccessTest) {
      InitialOpenGL();
      srand(time(nullptr));
      auto OpenGLMutex = std::make_shared<UNIQUEMUTEX>();
      std::string Tempdir = "F:\\Projects\\TouhouProjectShadow\\TouhouProjectShadow\\resource\\";
      uint16_t imagenum = rand() % 100 + 200;
      TMI::Handle TMH =
         std::make_shared<TextureManager2D>(Tempdir, OpenGLMutex);

      std::vector<std::string> preloadfilename;
      for (auto i = 0; i < imagenum; i++) {
         preloadfilename.push_back(std::to_string(i % 3) + ".png");
      }

      {
         std::thread([](std::vector<std::string> preloadfilename, TMI::Handle tmh)->void {
            for (auto i = 0; i < preloadfilename.size(); i++) {
               std::string tcalias = "TIalias" + std::to_string(i);
               TMI::TIPM tipm;
               tipm.relativePath = preloadfilename[i];
               std::thread([](std::string alias, TMI::TIPM tipm, TMI::Handle tmh) {

                  uint16_t milliseconds = rand() % 100;
                  std::chrono::milliseconds dura(milliseconds);
                  std::this_thread::sleep_for(dura);

                  tmh->PreloadTextureImage(alias, tipm);
                  for (auto i = 0; i < rand() + 10000; i++) {
                     tmh->GetTextureID(alias);
                  }
                  }, tcalias, tipm, tmh).detach();
            }
            }, preloadfilename, TMH).detach();
      }
      {
         std::thread([](uint16_t number, TMI::Handle tmh) -> void {
            for (auto i = 0; i < number; i++) {
               TMI::TCPM tcpm;
               tcpm.TIalias = "TIalias" + std::to_string(i);
               std::string TCalias = "TCalias" + std::to_string(i);

               std::thread([](std::string TCalias, TMI::TCPM tcpm, TMI::Handle tmh) -> void {
                  uint16_t milliseconds = rand() % 100;
                  std::chrono::milliseconds dura(milliseconds);
                  std::this_thread::sleep_for(dura);

                  tmh->PreloadTextureCoordmap(TCalias, tcpm);
                  for (auto i = 0; i < rand() + 10000; i++) {
                     tmh->ReadTextureCoordmap(TCalias);
                  }
                  }, TCalias, tcpm, tmh).detach();
            }
            }, imagenum, TMH).detach();
      }

      while (TMH.use_count() != 1)
         ;
      TMH.reset();

      /* TMI::TIPM tipm;
       tipm.relativePath = "explode1.png";
       tipm.parameteri.push_back(std::make_pair(GL_GENERATE_MIPMAP, GL_TRUE));
       tipm.parameterf.push_back(std::make_pair(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
       tipm.parameterf.push_back(std::make_pair(GL_TEXTURE_MAG_FILTER, GL_LINEAR));
       tipm.parameterf.push_back(std::make_pair(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
       tipm.parameterf.push_back(std::make_pair(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
       TMH->PreloadTextureImage("ss", tipm);*/
   }
};
}
