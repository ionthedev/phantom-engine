//
// Created by Brandon Friend on 8/10/24.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <Core/Core.h>
#include <Event_System/Event.h>

namespace Phantom {

    struct WindowSettings
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowSettings(const std::string& title = "PhantomEngine", unsigned int width = 1280, unsigned int height = 720) : Title(title), Width(width), Height(height){}
    };

class PHANTOM_API Window {
public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() {}

    virtual void OnUpdate() = 0;

    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;

    virtual void SetEventCallback(const EventCallbackFn& callback_fn) = 0;
    static Window* Create(const WindowSettings& settings = WindowSettings());



};

} // Phantom

#endif //WINDOW_H
