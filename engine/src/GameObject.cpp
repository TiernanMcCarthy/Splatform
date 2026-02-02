#include <Objects/GameObject.h>
#include <Objects/Behaviour.h>
#include <Engine.h>
#include <Scenes/SceneManager.h>
#include <iostream>

GameObject::GameObject(std::string objectname)
{
	transform = Transform();
	name = objectname;
	behaviours = std::vector<Behaviour*>();
    SceneManagement::AddNewObject(this);
}

GameObject::~GameObject()
{
	
	for (auto b : behaviours)
	{
		if (b != nullptr)
		{
			delete b;
		}
	}
	behaviours.clear();

}
void GameObject::OnDestroy()
{
    SceneManagement::RemoveObject(this);
}




void GameObject::Update(float deltaTime)
{
	//iterate through all attached behaviours
	for (int i = 0; i < behaviours.size(); i++)
	{
		behaviours[i]->Update(deltaTime);
	}
}

void GameObject::FixedUpdate(float deltaTime)
{
    std::cout<<"Undefined Behaviour, fixed update is not implemented yet" <<std::endl;
}

void GameObject::Render()
{
}

void GameObject::UpdateTransform()
{
}

void GameObject::Start()
{

}




void GameObject::RemoveBehaviour(Behaviour* b)
{
	behaviours.erase(std::remove(behaviours.begin(), behaviours.end(), b), behaviours.end());
}

void GameObject::SetBehaviourParent(Behaviour* b)
{
	b->SetGameObject(this);
}
