#pragma once
#include "Object.h"
#include <functional>
#include <vector>

class GameObject;
/// <summary>
/// Version of a Component Or Adjacent to Unity Monobehaviour
/// </summary>
class Behaviour :public Object{
public:

    GameObject* gameObject = nullptr;

    virtual ~Behaviour() = default;

    void OnDestroy() override;

    // Called after being added to a gameobject
    virtual void Start();

    void CanUpdate(float deltaTime);

    // Set the parent GameObject pointer
    void SetGameObject(GameObject* parent) {
        gameObject = parent;
    }

    virtual std::string GetTypeName() const override {
        // Returns compiler specific name (will vary from compiler)
        return typeid(*this).name();
    }

private:
    //Main Update of a behaviour, once per frame
    virtual void Update(float deltaTime);
};


using Creator = std::function<Behaviour*()>;

class BehaviourFactory {
public:
    static std::unordered_map<std::string, Creator>& Registry();
    static void Register(std::string name, Creator c);
    static Behaviour* Create(std::string name);
};

// Helper to bridge the static call
struct BehaviourRegistrar {
    BehaviourRegistrar(const std::string& name, Creator c) {
        BehaviourFactory::Registry()[name] = c;
    }
};

#define REGISTER_BEHAVIOUR(ClassName) \
static BehaviourRegistrar ClassName##_registrar_clean(#ClassName, []() { return new ClassName(); }); \
static BehaviourRegistrar ClassName##_registrar_mangled(typeid(ClassName).name(), []() { return new ClassName(); });