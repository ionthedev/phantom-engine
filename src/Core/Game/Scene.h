//
// Created by Brandon Friend on 8/17/24.
//

#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"

#include <vector>

#include "Object.h"

namespace Phantom {

class Scene : public Object {
public:
    Scene();
    virtual ~Scene();
    Color Background = DARKGRAY;

    Object* AddObject() { return AddChild(); }

    virtual void Start();
    virtual void Update(double deltaTime);
    virtual void FixedUpdate(double deltaTime);
    virtual void Render();

    Camera camera = { 0 };
};

} // Phantom

#endif //SCENE_H
