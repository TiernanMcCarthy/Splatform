#pragma once
#include <cstdint>
#include <unordered_map>
#include "EntityID.h"
#include "Serialization/Serializer.h"

using EntityID = uint64_t;
class Serializer;

class Object
{
public:

	EntityID ObjectID;

	Object();

	virtual ~Object() = default;

	//Custom Destruction Logic for Object
	virtual void OnDestroy();

	void Serialize(Serializer& serializer);

};