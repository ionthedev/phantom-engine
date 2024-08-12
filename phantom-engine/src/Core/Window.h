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
        unsigned int ID;
        Texture2D texture;
        Vector2 position;
        Vector2 velocity;
        bool open;
        bool focused;

        WindowSettings(const std::string& title = "PhantomEngine", unsigned int width = 1280, unsigned int height = 720) : Title(title), Width(width), Height(height){}
    };

class PHANTOM_API Window {
public:
    using EventCallbackFn = std::function<void(Event&)>;
    Window(const WindowSettings& settings);
    ~Window() {}

    void OnUpdate();
    unsigned int GetWidth();
    unsigned int GetHeight();

    virtual void SetEventCallback(const EventCallbackFn& callback_fn) = 0;
    static Window* Create(const WindowSettings& settings = WindowSettings());



};

} // Phantom

#endif //WINDOW_H
