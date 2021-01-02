#ifndef SARGASSO_WINDOW_WINDOW_INTERFACE_H_
#define SARGASSO_WINDOW_WINDOW_INTERFACE_H_

namespace sargasso {
namespace window {

struct WindowConfig {
    char title[128] = "Sample\0";
    uint32_t width = 960;
    uint32_t height = 540;
    uint8_t msaa = 0;
};

class IContextWrapper {
   public:
    virtual IContextWrapper(WindowConfig config) = 0;
    virtual bool should_close() const;
};

}  // namespace window
}  // namespace sargasso

#endif
