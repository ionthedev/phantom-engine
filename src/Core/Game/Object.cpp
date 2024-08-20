//
// Created by Brandon Friend on 8/17/24.
//

#include "Object.h"

#include "Components/PhysicsComponent.h"
#include "Components/TransformComponent.h"
#include "Core/Engine.h"


namespace Phantom {
    Object::~Object()
    {
        for (auto* child : Children)
            delete(child);
    }

    void Object::Update(double deltaTime)
    {
        for (auto& [id, componentPtr] : Components)
        {
            // Check if the component is of type PhysicsComponent

            componentPtr->OnUpdate(deltaTime);

        }

        for (auto* child : Children)
        {
            child->Update(deltaTime);
        }
    }

    void Object::FixedUpdate(double deltaTime)
    {
        for (auto& [id, componentPtr] : Components)
        {
            componentPtr->OnFixedUpdate(deltaTime);
        }

        for (auto* child : Children)
        {
            child->FixedUpdate(deltaTime);
        }
    }


    void Object::Render()
    {
        for (auto& [id, componentPtr] : Components)
            componentPtr->OnRender();

        for (auto* child : Children)
            child->Render();
    }
    Component* Object::AddComponent(std::unique_ptr<Component> component)
    {

        component->OnCreate();
        size_t id = component->GetTypeId();
        Components.insert_or_assign(id, std::move(component));
        return GetComponent(id);
    }

    void Object::RegisterPhysicsComponents()
    {
        for (auto& [id, componentPtr] : Components)
        {
            if (auto* physicsComponent = dynamic_cast<PhysicsComponent*>(componentPtr.get()))
            {
                PhysicsEngine::GetSingleton()->AddPhysicsObject(static_cast<std::unique_ptr<PhysicsComponent>>(physicsComponent));
            }
        }

        for (auto* child : Children)
        {
            child->RegisterPhysicsComponents();
        }
    }

    void Object::RemoveComponent(size_t componentID)
    {
        auto itr = Components.find(componentID);
        if (itr == Components.end())
            return;

        itr->second->OnDestoy();
        Components.erase(itr);
    }
    Component* Object::GetComponent(size_t componentID)
    {
        auto itr = Components.find(componentID);
        if (itr == Components.end())
            return nullptr;

        return itr->second.get();
    }

    Object* Object::AddChild()
    {
        Object* newChild = new Object();
        newChild->Parent = this;
        newChild->AddComponent<Phantom::TransformComponent>();
        Children.emplace_back(newChild);
        return newChild;
    }

    std::string_view Object::GetName() const
    {
        return Name;
    }

    void Object::SetName(std::string_view name)
    {
        Name = name;
    }

    //----------------Component---------------------//
    Component* Component::GetComponent(size_t componentID)
    {
        return HostingObject.GetComponent(componentID);
    }
} // Phantom