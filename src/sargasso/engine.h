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

    // methods
    void run();

   protected:
    const ProjectConfig _projectConfig;

    // methods
    virtual void load();
    virtual void update(const double dt);
    virtual void draw();

   private:
    unsigned int _windowWidth;
    unsigned int _windowHeight;

    // methods
    void pollEvents();
    void swapBuffer();
    void resetViewport();
    void clear();
    void init();
    void quit();
    bool quitRequested();
    void requestQuit();

    // instance callbacks
    void onKeyPressed(int key);
    void onKeyReleased(int key);

    // static callbacks
    static void onError(int errorCode, const char* errorMessage);
    static void onKeyAction(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void onWindowResize(GLFWwindow* window, int width, int height);
};

}  // namespace sargasso

#endif  // SARGASSO_ENGINE_H_
