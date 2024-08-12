//
// Created by Brandon Friend on 8/8/24.
//


#include "Application.h"
#include "PhantomPch.h"
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <gl2d/gl2d.h> //my 2d library, just to try OpenGL
#include <Debug/openglErrorReporting.h>
#undef main

#pragma region imgui
#include "WindowBase.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include "imguiThemes.h"
#include "Event_System/ApplicationEvent.h"
#pragma endregion



Phantom::Application::Application()
{
    m_Window = Window::Create(WindowSettings("Phantom Engine"));
}

Phantom::Application::~Application()
{
    	// Cleanup ImGui


}

void Phantom::Application::Run() // Literally just int maint()
{
    //rlViewport(viewportPos.x, viewportPos.y, viewportSize.x, viewportSize.y);

    WindowResizeEvent e (1280, 720);
    PH_INFO(e);

}

void Phantom::Application::MakeLayer(Layer *layer)
{
    m_LayerStack.MakeLayer(layer);
}

void Phantom::Application::MakeOverlay(Layer *layer)
{
    m_LayerStack.MakeOverlay(layer);
}
