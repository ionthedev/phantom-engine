//
// Created by Brandon Friend on 8/8/24.
//

#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H
#include "Application.h"
#include "Log.h"


extern Phantom::Application* Phantom::CreateApplication();

int main(int argc, char** argv) {



    Phantom::Log::Init();
    PH_CORE_TRACE("Logging Initialized");
    PH_CORE_TRACE("Entry Point Created");
    auto program = Phantom::CreateApplication();  // Ensure usage of the Phantom namespace
    delete program;
    return 0;
}




#endif // ENTRYPOINT_H
