//
// Created by Brandon Friend on 8/17/24.
//

#ifndef OBJECTBEHAVIOR_H
#define OBJECTBEHAVIOR_H


#include "Component.h"
#include "raylib.h"

namespace Phantom
{
#define DEFINE_BEHAVIOR(T) \
T(Object& object) : ObjectBehavior(object){}

class ObjectBehavior : public Component
{
public:
    static const char* GetComponentName() { return "ObjectBehavior"; }
    static size_t GetComponentId() { return reinterpret_cast<size_t>("ObjectBehavior"); }
    inline size_t GetTypeId() const override { return GetComponentId(); }
    ObjectBehavior(Object& object) : Component(object) {}

};}

#endif //OBJECTBEHAVIOR_H
