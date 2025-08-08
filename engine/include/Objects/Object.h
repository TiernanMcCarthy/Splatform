#pragma once


class Object
{
public:

	Object();

	virtual ~Object() = default;

	//Custom Destruction Logic for Object
	virtual void OnDestroy();

};