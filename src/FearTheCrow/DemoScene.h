//
// Created by Brandon Friend on 8/21/24.
//

#ifndef DEMOSCENE_H
#define DEMOSCENE_H
#include "Core/Game/Scene.h"


class DemoScene : public Phantom::Scene {
public:
    DemoScene();

    void Start() override;
    void Update(double deltaTime) override;
    void FixedUpdate(double deltaTime) override;
    void Render() override;



};



#endif //DEMOSCENE_H
