//
// Created by Brandon Friend on 8/8/24.
//


#include "Application.h"
#include "PhantomPch.h"
#include "Event_System/ApplicationEvent.h"
#include "Log.h"

Phantom::Application::Application()
{
}

Phantom::Application::~Application()
{
}

void Phantom::Application::Run()
{
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
