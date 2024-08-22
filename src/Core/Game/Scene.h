//
// Created by Brandon Friend on 8/17/24.
//

#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"

#include <vector>


namespace Phantom {

class Scene{
public:
    Scene();
    virtual ~Scene();
    Color Background = DARKGRAY;


    virtual void Start();
    virtual void Update(double deltaTime);
    virtual void FixedUpdate(double deltaTime);
    virtual void Render();

    Camera camera = { 0 };
};

} // Phantom

#endif //SCENE_H
