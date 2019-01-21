#pragma once
#include <vector>
class GameObject
{
private:
	std::vector<const char*>* objectTypes;
	const char* objectName;

public:
	GameObject();
	~GameObject();

	//==Public functions==//
	bool typeOf(const char* type);

	//==Getters==//
	std::vector<const char*>* getObjectTypes();
	const char* getObjectName();

	//==Setters==//
};

