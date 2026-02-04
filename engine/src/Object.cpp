#include "../include/Objects/Object.h"
#include "Scenes/SceneManager.h"

#include <random>
Object::Object()
{
    ObjectID=GenerateEntityID();
    Register();
}

//Assign the object to the object register
void Object::Register()
{
    SceneManagement::objectRegister[ObjectID]=this;
}

void Object::ForceID(EntityID id)
{
    SceneManagement::RemoveObjectFromRegister(ObjectID); // Remove old random ID
    ObjectID = id;
    SceneManagement::objectRegister[ObjectID] = this;    // Register new loaded ID
}

EntityID Object::GenerateEntityID() {
    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    return std::uniform_int_distribution<uint64_t>{}(gen);
}

Object *Object::Find(EntityID id)
{
    auto target = SceneManagement::objectRegister.find(id);
    return (target != SceneManagement::objectRegister.end()) ? target->second : nullptr;
}

void Object::Serialize(Serializer &s)
{

}

void Object::OnDestroy()
{
    SceneManagement::RemoveObjectFromRegister(ObjectID);
}
