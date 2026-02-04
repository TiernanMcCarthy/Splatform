#include <Objects/GameObject.h>
#include <Objects/Behaviour.h>
#include <Engine.h>
#include <Scenes/SceneManager.h>
#include <iostream>

GameObject::GameObject(std::string objectname,bool useStart)
{
	transform = Transform();
	name = objectname;
	behaviours = std::vector<Behaviour*>();
    SceneManagement::AddNewObject(this,useStart);
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

std::string GameObject::GetTypeName() const {
    return "GameObject";
}


void GameObject::RemoveBehaviour(Behaviour* b)
{
	behaviours.erase(std::remove(behaviours.begin(), behaviours.end(), b), behaviours.end());
}

void GameObject::SetBehaviourParent(Behaviour* b)
{
	b->SetGameObject(this);
}

//Serialisation
// Manually expanding the reflection logic to handle the vector of behaviours
void GameObject::Serialize(Serializer& s) {
    std::string oldCtx = s.currentContext;
    s.currentContext = "GameObject" + std::to_string(ObjectID);
    s.Property("ObjectID", ObjectID);

    s.Property("name", name);
    int count = (int)behaviours.size();
    s.Property("B_Count", count);

    if (s.mode == Mode::Saving) {
        for (int i = 0; i < count; i++) {
            std::string idx = std::to_string(i);

            // Ensure this is calling the version overridden by your macro!
            std::string typeName = behaviours[i]->GetTypeName();

            s.SaveString("B_Type_" + idx, typeName);
            s.Property("B_ObjectID_" + idx, behaviours[i]->ObjectID);
            behaviours[i]->Serialize(s);
        }
    } else {
        for (auto b : behaviours) delete b;
        behaviours.clear();
        for (int i = 0; i < count; i++) {
            std::string idx = std::to_string(i);
            std::string type;
            EntityID bID;
            s.Property("B_Type_" + idx, type);
            s.Property("B_ObjectID_" + idx, bID);

            Behaviour* b = BehaviourFactory::Create(type);
            if (b) {
                b->ForceID(bID);
                b->Serialize(s);
                behaviours.push_back(b);
            }
        }
    }
    s.currentContext = oldCtx;
}

std::vector<Behaviour *> GameObject::GetBehaviours()
{
    return behaviours;
}
