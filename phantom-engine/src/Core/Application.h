//
// Created by Brandon Friend on 8/8/24.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include "Layer.h"
#include "LayerStack.h"
#include "Event_System/Event.h"

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <gl2d/gl2d.h> //my 2d library, just to try OpenGL
#include <Debug/openglErrorReporting.h>
#undef main

#pragma region imgui
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include "imguiThemes.h"
#pragma endregion
#include "PhantomPch.h"
#include "WindowBase.h"


int main(int argc, char** argv);

namespace Phantom
{

class Application {

public:
    Application();
    virtual ~Application();

    virtual void Run();
    void MakeLayer(Layer* layer);
    void MakeOverlay(Layer* layer);


    Scope<Window> m_Window;
private:

    LayerStack m_LayerStack;

};

    Application* CreateApplication();

}
#endif //APPLICATION_H
