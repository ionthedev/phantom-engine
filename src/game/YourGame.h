//
// Created by Brandon Friend on 7/21/24.
//

#ifndef YOURGAME_H
#define YOURGAME_H

#include "classes/Player.h"
#include "Core/PE_Core.h"
#include "Core/Game.h"

#include "BulletCollision/BroadphaseCollision/btBroadphaseProxy.h"

#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include "BulletCollision/CollisionShapes/btConvexPolyhedron.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"

#include "LinearMath/btVector3.h"
#include "btBulletDynamicsCommon.h"
#include "raylib-cpp.hpp"
#include "raylib.h"


#define MAX_COLUMNS 20
class YourGame : public Game {

public:

    YourGame() = default;
    YourGame(bool _initialized);
    ~YourGame();
    void Start() const override;
    void Update(double _deltaTime) const override;
    void FixedUpdate(double _deltaTime) const override;
    void Render() const override;
    void HandleInput() const override;
    mutable ImGuiIO io;




protected:
    PE_Core engine;



    private:
    bool initialized;

};



#endif //YOURGAME_H
