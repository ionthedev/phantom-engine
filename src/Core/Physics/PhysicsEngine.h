//
// Created by Brandon Friend on 8/18/24.
//

#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H
#include "Core/Application.h"

namespace Phantom {

class PhysicsEngine {
public:
    // Static method to access the singleton instance
    static PhysicsEngine* GetSingleton(bool initialized = false);

    // Delete copy constructor and assignment operator to prevent copies
    PhysicsEngine(const PhysicsEngine&);
    PhysicsEngine& operator=(const PhysicsEngine&) = delete;

    void Init();

    void SetScene(Scene* scene);
    Scene* GetScene();
    void PhysicsUpdate(double _deltaTime);

protected:
    PhysicsEngine(bool _initialized); // Protected constructor
    ~PhysicsEngine(); // Protected destructor


    Scene* m_Scene;
    Application* m_Application;

private:
    bool initialized;
    static PhysicsEngine* s_Instance; // Static instance pointer

};

} // Phantom

#endif //PHYSICSENGINE_H
