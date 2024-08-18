//
// Created by ion on 8/17/24.
//

#ifndef PHYSICS_H
#define PHYSICS_H

#include <Jolt/Jolt.h>
#include "BroadphaseLayer.h"
#include "ObjectLayer.h"
#include "ObjectVsBroadPhaseLayer.h"
#include "ContactListener.h"
#include "BodyActivationListener.h"

// STL includes
#include <iostream>
#include <cstdarg>
#include <thread>

#include "Core/Application.h"
#include "Jolt/Physics/Body/BodyInterface.h"

namespace JPH
{
    class PhysicsSystem;
    class TempAllocatorImpl;
    class JobSystemThreadPool;
}

// Disable common warnings triggered by Jolt, you can use JPH_SUPPRESS_WARNING_PUSH / JPH_SUPPRESS_WARNING_POP to store and restore the warning state
JPH_SUPPRESS_WARNINGS

// All Jolt symbols are in the JPH namespace
using namespace JPH;

// If you want your code to compile using single or double precision write 0.0_r to get a Real value that compiles to double or float depending if JPH_DOUBLE_PRECISION is set or not.
using namespace JPH::literals;

// We're also using STL classes in this example
using namespace std;


static void TraceImpl(const char *inFMT, ...)
{
    // Format the message
    va_list list;
    va_start(list, inFMT);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), inFMT, list);
    va_end(list);

    // Print to the TTY
    cout << buffer << endl;
}

#ifdef JPH_ENABLE_ASSERTS

// Callback for asserts, connect this to your own assert handler if you have one
static bool AssertFailedImpl(const char *inExpression, const char *inMessage, const char *inFile, uint inLine)
{
    // Print to the TTY
    cout << inFile << ":" << inLine << ": (" << inExpression << ") " << (inMessage != nullptr? inMessage : "") << endl;

    // Breakpoint
    return true;
};

#endif // JPH_ENABLE_ASSERTS

class Physics {
public:
    Physics();
    virtual ~Physics();
    void PhysicsUpdate(double deltaTime);


    JPH::uint step{0};

    std::unique_ptr<Phantom::BodyActivationListener> body_activation_listener;
    std::unique_ptr<ContactListener> contact_listener;
    std::unique_ptr<BPLayerInterfaceImpl> broad_phase_layer_interface;
    std::unique_ptr<ObjectVsBroadPhaseLayerFilterImpl> object_vs_broadphase_layer_filter;
    std::unique_ptr<ObjectLayerPairFilterImpl> object_vs_object_layer_filter;
    Phantom::Application* application;


};
inline PhysicsSystem* physics_system;
inline TempAllocatorImpl* temp_allocator;
inline JobSystemThreadPool* job_system;
inline BodyInterface* body_interface;


#endif //PHYSICS_H
