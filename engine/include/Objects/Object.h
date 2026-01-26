#pragma once
#include <cstdint>
#include <unordered_map>


using EntityID = uint64_t;
class Serializer;

class Object
{
public:

	EntityID ObjectID;

	static std::unordered_map<EntityID, Object*> s_registry;

	Object();

	virtual ~Object() = default;

	//Custom Destruction Logic for Object
	virtual void OnDestroy();

	void Serialize(Serializer& serializer);

};