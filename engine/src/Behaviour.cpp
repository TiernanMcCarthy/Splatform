#include <Objects/Behaviour.h>
#include <Objects/GameObject.h>

void Behaviour::OnDestroy()
{
	if (gameObject)
	{
		gameObject->RemoveBehaviour(this);
	}
}

void Behaviour::Start()
{
}

void Behaviour::CanUpdate(float deltaTime)
{
    if (isActive)
    {
        Update(deltaTime);
    }
}


void Behaviour::Update(float deltaTime)
{
}


std::unordered_map<std::string, Creator>& BehaviourFactory::Registry() {
    static std::unordered_map<std::string, Creator> reg;
    return reg;
}

void BehaviourFactory::Register(std::string name, Creator c) {
    Registry()[name] = c;
}

// In Behaviour.cpp (or wherever your Factory lives)
Behaviour* BehaviourFactory::Create(std::string name) {
    // If the name from the file is "11BoxRenderer", we need to be careful.
    // But since we use the REGISTER_BEHAVIOUR macro with #ClassName,
    // the registry key will be exactly "BoxRenderer".

    if (Registry().count(name)) {
        return Registry()[name]();
    }

    std::cout << "Error: Behaviour Type [" << name << "] not registered!" << std::endl;
    return nullptr;
}
