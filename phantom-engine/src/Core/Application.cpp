//
// Created by Brandon Friend on 8/8/24.
//


#include "Application.h"
#include "PhantomPch.h"
#include "Event_System/ApplicationEvent.h"
#include "Log.h"
#include "rlgl.h"
#include <iostream>



Phantom::Application::Application() = default;

void Phantom::Application::Start() const
{
    PH_CORE_WARN("Application Started");
    PH_WARN("Application Started");


}

void Phantom::Application::Update(double _deltaTime) const
{

}

void Phantom::Application::FixedUpdate(double _deltaTime) const
{
}

void Phantom::Application::Render() const
{
}

