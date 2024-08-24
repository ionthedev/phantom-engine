//
// Created by Brandon Friend on 8/22/24.
//

#include "GameObject.h"

namespace Phantom {


GameObject::~GameObject()
{
    for (auto* child : Children)
        delete(child);
}

void GameObject::Start()
{
}

void GameObject::Update(double deltaTime)
{
    for (auto& [id, componentPtr] : Components)
        componentPtr->OnUpdate(deltaTime);

    for (auto* child : Children)
        child->Update(deltaTime);
}

void GameObject::FixedUpdate(double deltaTime)
{

    for (auto& [id, componentPtr] : Components)
        componentPtr->OnFixedUpdate(deltaTime);

    for (auto* child : Children)
        child->FixedUpdate(deltaTime);

}

void GameObject::Render()
{
    for (auto& [id, componentPtr] : Components)
        componentPtr->OnRender();

    for (auto* child : Children)
        child->Render();
}

Component* GameObject::AddComponent(std::unique_ptr<Component> component)
{
    component->OnCreate();
    size_t id = component->GetTypeId();
    Components.insert_or_assign(id, std::move(component));
    return GetComponent(id);
}

void GameObject::RemoveComponent(size_t componentID)
{
    auto itr = Components.find(componentID);
    if (itr == Components.end())
        return;

    itr->second->OnDestoy();
    Components.erase(itr);
}

Component* GameObject::GetComponent(size_t componentID)
{
    auto itr = Components.find(componentID);
    if (itr == Components.end())
        return nullptr;

    return itr->second.get();
}

GameObject* GameObject::AddChild()
{
    GameObject* newChild = new GameObject();
    newChild->Parent = this;
    Children.emplace_back(newChild);
    return newChild;
}

std::string_view GameObject::GetName() const
{
    return Name;
}

void GameObject::SetName(std::string_view name)
{
    Name = name;
}

//----------------Component---------------------//
Component* Component::GetComponent(size_t componentID)
{
    return HostingObject.GetComponent(componentID);
}
} // Phantom