//
// Created by Brandon Friend on 8/17/24.
//

#ifndef PROTOTYPESCENE_H
#define PROTOTYPESCENE_H
#include "Core/Game/Scene.h"

namespace FTC {

class PrototypeScene : public Phantom::Scene{
public:
    PrototypeScene();
    ~PrototypeScene();
    void Start() override;
    void Update() override;
    void FixedUpdate() override;
    void Render() override;
    Object* test_mesh;
};

} // FearTheCrow

#endif //PROTOTYPESCENE_H
