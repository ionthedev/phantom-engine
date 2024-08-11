//
// Created by Brandon Friend on 8/11/24.
//

#ifndef WINDOWBASE_H
#define WINDOWBASE_H
#include "Window.h"

namespace Phantom {

class WindowBase : public Window {
public:

    ~WindowBase();

    void OnUpdate() override;
    unsigned int GetWidth() const override;
    unsigned int GetHeight() const override;

    void SetEventCallback(const EventCallbackFn &callback_fn) override;

    void Init(const WindowSettings& settings);
    void Shutdown();

private:


    struct WindowData
    {
        std::string Title;
        unsigned int Width, Height;
        EventCallbackFn EventCallback;
    };

    WindowData m_Data;

};

} // Phantom

#endif //WINDOWBASE_H
