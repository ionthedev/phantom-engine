//
// Created by Brandon Friend on 8/11/24.
//

#include "WindowBase.h"

#include <iostream>
#include <Debug/openglErrorReporting.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>

namespace Phantom {
    WindowBase::WindowBase(const WindowSettings &settings)
    {
        Init(settings);
    }

    WindowBase::~WindowBase()
    {
        Shutdown();
    }

    void WindowBase::OnUpdate()
    {
    }

    unsigned int WindowBase::GetWidth() const
    {
    }

    unsigned int WindowBase::GetHeight() const
    {
    }

    void WindowBase::SetEventCallback(const EventCallbackFn &callback_fn)
    {
    }

    void WindowBase::Init(const WindowSettings &settings)
    {

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        // Create a window
        m_Window = SDL_CreateWindow(settings.Title.c_str(), 100, 100, settings.Width, settings.Height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);


        // Create OpenGL context
        //enableReportGlErrors();
    }

    void WindowBase::Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        // Cleanup SDL
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }
} // Phantom