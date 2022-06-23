#ifndef SARGASSO_ENGINE_H_
#define SARGASSO_ENGINE_H_

#include "sargasso/project_config.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace sargasso {

class Engine {
   public:
    Engine(const ProjectConfig& projectConfig);

    Engine() = delete;
    Engine(Engine&&) = delete;
    Engine(const Engine&&) = delete;
    Engine&& operator=(Engine&&) = delete;
    const Engine&& operator=(const Engine&&) = delete;

    Engine(Engine&) = delete;
    Engine(const Engine&) = delete;
    Engine& operator=(Engine&) = delete;
    const Engine& operator=(const Engine&) = delete;

    virtual void load();
    virtual void update(const double dt);
    virtual void draw();
    void run();

   protected:
    const ProjectConfig _projectConfig;

   private:
    void pollEvents();
    void swapBuffer();
    void init();
    void quit();
    bool quitRequested() const;
    static void error(int errorCode, const char* errorMessage);
    static void keyAction(GLFWwindow* window, int key, int scancode, int action, int mods);
};

}  // namespace sargasso

#endif  // SARGASSO_ENGINE_H_
