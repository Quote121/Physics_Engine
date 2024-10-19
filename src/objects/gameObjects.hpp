#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "components.hpp"


enum class GameObjectType {
    MESHOBJECT,
    SPRITEOBJECT
};

// Mesh object - 3d object from .obj
// Sprite object - 2d sprite from image file

// Future?
// Light object - point/directional
// Camera object - player and cinematic
//      Render - screenspace
//      Update - any player inputs or cinematic track position
// UI object - UI assets like health bars
//      Render - Display information
//      Update - update the values they have/animation
// DecalObject - Projected textures such as bullet holes/blood
// ParticleObject

// General game object interface
class IGameObject
{
private:
    using ComponentID = std::size_t;

    // Map of all components, indexed by a hash of their type
    std::unordered_map<ComponentID, std::shared_ptr<IComponent>> componentMap;

protected:
    // Display to the screen
    virtual void Render() = 0;

    // Update any components of the objects such as physics elements
    virtual void Update() = 0;

    // Component based methods
    template<typename T>
    void AddComponent(const T& component)
    {
        componentMap[typeid(T).hash_code()] = component;
    }

    template<typename T>
    void AddComponent(const T&& component)
    {
        componentMap[typeid(T).hash_code()] = component;
    }

    template<typename T>
    T& GetComponent(const T& component)
    {
        auto index = componentMap.find(typeid(T).hash_code());
        if (index != componentMap.end())
        {
            return index->second;
        }
        return nullptr;
    }

    template<typename T>
    void RemoveComponent(const T& component)
    {
        auto index = componentMap.find(typeid(T).hash_code());
        if (index != componentMap.end())
        {
            componentMap.erase(index);
        }
    }
};



// Singleton IGameObjectFactory
// Extensable factory, we can keep adding methods as long as they have the Create() method
class GameObjectFactory
{
    using GameObjectCallback = std::shared_ptr<IGameObject> (*)();
    using factoryCallBackMap = std::unordered_map<GameObjectType, GameObjectCallback>;

private:
    static factoryCallBackMap callbackMap;

public:
    static void RegisterObject(const GameObjectType type, GameObjectCallback cb)
    {
        callbackMap[type] = cb;
    }

    static void UnRegisterObject(const GameObjectType type)
    {
        callbackMap.erase(type);
    }

    static std::shared_ptr<IGameObject> CreateObject(const GameObjectType type)
    {
        const auto& entry = callbackMap.find(type);
        if (entry != callbackMap.end())
        {
            return (entry->second)(); 
        }
        return nullptr;
    }
};

// Example object becuase I cant think rn
class MeshObject : public IGameObject
{
private:

public:
    void Render() {}
    void Update() {}

    void MeshPrint() {}

    // Call back function for factory
    static std::shared_ptr<IGameObject> Create()
    {
        return std::make_shared<MeshObject>();
    }
};
