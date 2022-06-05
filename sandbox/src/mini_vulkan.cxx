#define GLFW_INCLUDE_VULKAN

#include "miniVk/application.cxx"

#include <exception>
#include <sargasso/common/log.h>

using sargasso::common::Log;

int main() {
    miniVk::MiniVulkanApplication application;
    try {
        application.run();
    } catch (const std::exception& e) {
        Log("minVk").error(e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
