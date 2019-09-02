#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../TouhouProjectShadow/include/texture/texturemanager.hpp"
#include "../TouhouProjectShadow/include/texture/textureanimation.hpp"
using namespace TouhouProjectShadow;

#define WRITEMESSAGE(x) Logger::WriteMessage(x.info.c_str())

namespace InterfaceLevelTest {
TEST_CLASS(InterfaceLevelTest) {
public:
   GLFWwindow* InitialOpenGL(void) {
      Assert::IsTrue(glfwInit());
      GLFWwindow* window = glfwCreateWindow(800, 600, "UnitTest", nullptr, nullptr);
      glfwSwapInterval(1);
      Assert::IsNotNull(window);
      glfwMakeContextCurrent(window);
      Assert::IsFalse(glewInit());
      return window;
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
                     tmh->Get(alias);
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

   TEST_METHOD(TextureAnimation_MultThread) {
      auto window = InitialOpenGL();
      srand(time(nullptr));
      auto OpenGLMutex = std::make_shared<UNIQUEMUTEX>();
      std::string const Tempdir =
         "F:\\Projects\\TouhouProjectShadow\\TouhouProjectShadow\\resource";
      TMI::Handle TMH =
         std::make_shared<TextureManager2D>(Tempdir, OpenGLMutex);
      TAI::Handle TAH =
         std::make_shared<TextureAnimation>(TMH);
      const int imagenum = 6;
      for (auto i = 0; i < imagenum; i++) {
         std::string filename(std::to_string(i) + ".png");
         TMI::TIPM tipm;
         tipm.relativePath = filename;
         tipm.parameteri.push_back(std::make_pair(GL_GENERATE_MIPMAP, GL_TRUE));
         tipm.parameterf.push_back(std::make_pair(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
         tipm.parameterf.push_back(std::make_pair(GL_TEXTURE_MAG_FILTER, GL_LINEAR));
         tipm.parameterf.push_back(std::make_pair(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
         tipm.parameterf.push_back(std::make_pair(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
         WRITEMESSAGE(TMH->PreloadTextureImage(std::to_string(i), tipm));
      }
      TMI::TCPM tcpm;
      tcpm.TIalias = "0";
      tcpm.texturesizezoom = 1;
      tcpm.coordmap.push_back(Vec2f(-1., -1.));
      tcpm.coordmap.push_back(Vec2f(1., -1.));
      tcpm.coordmap.push_back(Vec2f(1., 1.));
      tcpm.coordmap.push_back(Vec2f(-1., 1.));
      WRITEMESSAGE(TMH->PreloadTextureCoordmap("x0", tcpm));
      tcpm.TIalias = "1";
      WRITEMESSAGE(TMH->PreloadTextureCoordmap("x1", tcpm));
      tcpm.TIalias = "2";
      WRITEMESSAGE(TMH->PreloadTextureCoordmap("x2", tcpm));
      tcpm.TIalias = "3";
      WRITEMESSAGE(TMH->PreloadTextureCoordmap("x3", tcpm));
      tcpm.TIalias = "4";
      WRITEMESSAGE(TMH->PreloadTextureCoordmap("x4", tcpm));
      tcpm.TIalias = "5";
      WRITEMESSAGE(TMH->PreloadTextureCoordmap("x5", tcpm));

      TAI::AS animationsequence;
      animationsequence.duration = 1;
      animationsequence.animationsequencetype = TAI::AS::AST::Frame;
      animationsequence.TCaliasSequence.push_back("x0");
      animationsequence.TCaliasSequence.push_back("x1");
      animationsequence.TCaliasSequence.push_back("x2");
      animationsequence.TCaliasSequence.push_back("x3");
      animationsequence.TCaliasSequence.push_back("x4");
      animationsequence.TCaliasSequence.push_back("x5");
      WRITEMESSAGE(TAH->PreloadExecutionSlot({ REMI::REGMP::REC::camp0, TAI::REES::ELT::Creat }, animationsequence));

      UIC uic = UIC::GetUIC();
      WRITEMESSAGE(TMH->Create(uic, "x1"));
      TAI::AEM aem = { uic, { REMI::REGMP::REC::camp0, TAI::REES::ELT::Creat }};
      WRITEMESSAGE(TAH->ExecuteSlot(aem));
      
      int display_w, display_h;
      glfwGetFramebufferSize(window, &display_w, &display_h);
      glViewport(0, 0, display_w, display_h);
      float oldtimetime = glfwGetTime();
      while (!glfwWindowShouldClose(window) && !TAH->ExecuteSlotIsFinished(aem)) {
         glfwPollEvents();
         glColor3f(1, 1, 1);
         glClearColor(0, 0, 0, 0);
         glClear(GL_COLOR_BUFFER_BIT);

         float timei = static_cast<float>((glfwGetTime() - oldtimetime));
         oldtimetime = glfwGetTime();
         TAH->Update(timei);

         auto tcpm = TMH->Get(uic);
         auto textureid = TMH->Get(tcpm.TIalias);
         auto ptr = textureid.lock();
         
         glActiveTexture(GL_TEXTURE1);
         glEnable(GL_TEXTURE_2D);
         glEnable(GL_BLEND);
         glBindTexture(GL_TEXTURE_2D, *ptr);
         glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         glBegin(GL_QUADS);
         for (auto i = 0; i < 4; i++) {
            glMultiTexCoord2f(GL_TEXTURE1, tcpm.coordmap[i].s, tcpm.coordmap[i].t);
            glVertex2f(tcpm.coordmap[i].x / 2., tcpm.coordmap[i].y / 2.);
         }
         glEnd();
         glDisable(GL_TEXTURE_2D);
         glDisable(GL_BLEND);

         glfwMakeContextCurrent(window);
         glfwSwapBuffers(window);
      }
      glfwDestroyWindow(window);
      glfwTerminate();
      Assert::IsTrue(true);
   }
};
}
