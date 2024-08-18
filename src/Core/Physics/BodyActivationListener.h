//
// Created by Brandon Friend on 8/17/24.
//

#ifndef BODYACTIVATIONLISTENER_H
#define BODYACTIVATIONLISTENER_H


#include <iostream>
#include <Jolt/Jolt.h>

#include "Jolt/Physics/Body/BodyActivationListener.h"
namespace Phantom
{
class BodyActivationListener : public JPH::BodyActivationListener
{
public:
    void OnBodyActivated(const JPH::BodyID &inBodyID, JPH::uint64 inBodyUserData) override
    {
        std::cout << "A body got activated" << std::endl;
    }

    void OnBodyDeactivated(const JPH::BodyID &inBodyID, JPH::uint64 inBodyUserData) override
    {
        std::cout << "A body went to sleep" << std::endl;
    }
};}

#endif //BODYACTIVATIONLISTENER_H
