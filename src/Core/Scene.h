//
// Created by Brandon Friend on 8/17/24.
//

#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"



#include "GameObject.h"

namespace Phantom {

class Scene : public GameObject{
public:
    Scene();
    virtual ~Scene();
    Color Background = DARKGRAY;



    void Start() override;
    void Update(double deltaTime) override;
    void FixedUpdate(double deltaTime) override;
    void Render() override;
    GameObject* AddObject() { return AddChild(); }



    Camera camera;
};

} // Phantom

#endif //SCENE_H
