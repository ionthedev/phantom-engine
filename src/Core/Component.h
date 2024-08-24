//
// Created by Brandon Friend on 8/22/24.
//

#ifndef COMPONENT_H
#define COMPONENT_H
#include <memory>
namespace Phantom {



// macro to define common code that all components need
// computes a runtime unique ID for each component using the name
// NOTE that this ID is not deterministic, a real system would hash the name and use a better ID
#define DEFINE_COMPONENT(T) \
static const char* GetComponentName() { return #T;}  \
static size_t GetComponentId() { return reinterpret_cast<size_t>(#T); } \
inline size_t GetTypeId() const override { return GetComponentId(); } \
T(Phantom::GameObject& object) : Component(object) {}

class GameObject;

class Component
{
private:
    GameObject& HostingObject;

protected:
    GameObject& GetGameObject() { return HostingObject; }
    const GameObject& GetGameObject() const { return HostingObject; }

public:
    virtual size_t GetTypeId() const = 0;

    Component(GameObject& object)
        : HostingObject(object)
    {
    }
    virtual ~Component() = default;

    // no copy
    Component(const Component&) = delete;
    Component& operator=(Component const&) = delete;

    Component* GetComponent(size_t componentID);

    template<class T>
    T* GetComponent()
    {
        return static_cast<T*>(GetComponent(T::GetComponentId()));
    }

    virtual void OnCreate() {};
    virtual void OnDestoy() {};
    virtual void OnUpdate(double deltaTime = 0) {};
    virtual void OnFixedUpdate(double deltaTime = 0) {};
    virtual void OnRender() {};
};
}

#endif //COMPONENT_H
