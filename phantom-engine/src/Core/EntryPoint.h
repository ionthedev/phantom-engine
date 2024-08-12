//
// Created by Brandon Friend on 8/8/24.
//

#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H
#include "Application.h"
#include "Log.h"
#include "Window.h"


extern Phantom::Application* Phantom::CreateApplication();

int main(int argc, char** argv) {

    Phantom::Log::Init();
    PH_CORE_WARN("Initialized Log!");
    PH_INFO("Hello!");

    auto program = Phantom::CreateApplication();  // Ensure usage of the Phantom namespace

    program->Run();
    delete program;
    return 0;
}



#endif // ENTRYPOINT_H
