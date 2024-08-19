//
// Created by Brandon Friend on 8/17/24.
//

#ifndef PROTOTYPESCENE_H
#define PROTOTYPESCENE_H
#include "Core/Game/Scene.h"

#include "Core/Physics/Collision.h"

namespace FTC {

class PrototypeScene : public Phantom::Scene {


public:
    PrototypeScene();
    ~PrototypeScene();
    void Start() override;
    void Update() override;
    void FixedUpdate() override;
    void Render() override;
    Object* test_mesh;
    Object* floorMesh;

    Collider test_meshCol;
    Collider floorMeshCol;

    bool collision;


};

} // FearTheCrow

#endif //PROTOTYPESCENE_H
