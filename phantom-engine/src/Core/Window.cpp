//
// Created by Brandon Friend on 8/12/24.
//
#include "Window.h"

#include "WindowBase.h"

Phantom::Scope<Phantom::Window> Phantom::Window::Create(const WindowSettings &settings)
{
    return CreateScope<WindowBase>(settings);
}
