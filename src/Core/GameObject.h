//
// Created by Brandon Friend on 8/22/24.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

#include "Component.h"
namespace Phantom {




class GameObject
{
private:
    GameObject* Parent = nullptr;
    std::vector<GameObject*> Children;

    std::string Name;

protected:
    std::unordered_map<size_t, std::unique_ptr<Component>> Components;

public:
    ~GameObject();

    virtual void Start();
    virtual void Update(double deltaTime);
    virtual void FixedUpdate(double deltaTime);
    virtual void Render();

    Component* AddComponent(std::unique_ptr<Component> component);
    void RemoveComponent(size_t componentID);
    Component* GetComponent(size_t componentID);

    template<class T>
    T* AddComponent()
    {
        return static_cast<T*>(AddComponent(std::make_unique<T>(*this)));
    }

    template<class T>
    void RemoveComponent()
    {
        RemoveComponent(T::GetComponentId());
    }

    template<class T>
    T* GetComponent()
    {
        return static_cast<T*>(GetComponent(T::GetComponentId()));
    }

    const std::vector<GameObject*>& GetChildren() const { return Children; }
    GameObject* GetParent() const { return Parent; }

    GameObject* AddChild();

    std::string_view GetName() const;
    void SetName(std::string_view name);
};

} // Phantom

#endif //GAMEOBJECT_H
