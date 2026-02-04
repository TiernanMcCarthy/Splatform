#pragma once
#include <cstdint>
#include <unordered_map>
#include <string>
#include "EntityID.h"
#include "Serialization/Serializer.h"
#include <SFML/Graphics.hpp>

class Serializer;

class Object
{
public:

	EntityID ObjectID;

	Object();

	virtual ~Object() = default;

	//Custom Destruction Logic for Object
	virtual void OnDestroy();


    void Register();

    void ForceID(EntityID id);

    static EntityID GenerateEntityID();
    static Object* Find(EntityID id);

    virtual std::string GetTypeName() const { return "Object"; }
    virtual void Serialize(Serializer& s);

};