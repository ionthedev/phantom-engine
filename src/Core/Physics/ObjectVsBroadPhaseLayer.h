//
// Created by Brandon Friend on 8/17/24.
//

#ifndef OBJECTVSBROADPHASELAYER_H
#define OBJECTVSBROADPHASELAYER_H

#include <Jolt/Jolt.h>

#include "BroadphaseLayer.h"
#include "ObjectLayer.h"
#include "Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h"

class ObjectVsBroadPhaseLayerFilterImpl : public JPH::ObjectVsBroadPhaseLayerFilter
{
public:
    virtual bool				ShouldCollide(JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2) const override
    {
        switch (inLayer1)
        {
        case Layers::NON_MOVING:
            return inLayer2 == BroadPhaseLayers::MOVING;
        case Layers::MOVING:
            return true;
        default:
            JPH_ASSERT(false);
            return false;
        }
    }
};
#endif //OBJECTVSBROADPHASELAYER_H
