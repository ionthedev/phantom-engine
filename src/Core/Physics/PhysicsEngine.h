//
// Created by Brandon Friend on 8/18/24.
//

#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H
#include "Core/Application.h"

namespace Phantom {
    class PhysicsComponent;

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
    void SetGravity(Vector3 gravityDir);
    Vector3 GetGravity();
    void RemovePhysicsObject(size_t object, PhysicsComponent* _object);
    PhysicsComponent* AddPhysicsObject(std::unique_ptr<PhysicsComponent> component);

    PhysicsComponent* GetPhysicsObject(size_t objectID);
    std::unordered_map<size_t, std::unique_ptr<PhysicsComponent>> PhysicsObjects;
protected:
    PhysicsEngine(bool _initialized); // Protected constructor
    ~PhysicsEngine(); // Protected destructor


    Scene* m_Scene;
    Application* m_Application;

private:
    bool initialized;
    static PhysicsEngine* s_Instance; // Static instance pointer
    Vector3 Gravity = {0, -9.81f, 0};


};

} // Phantom

#endif //PHYSICSENGINE_H
