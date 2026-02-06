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
    for (auto b : behaviours)
    {
        b->OnDestroy();
    }
    SceneManagement::RemoveObject(this);
}


void GameObject::Update(float deltaTime)
{

    if (isActive)
    {
        //Check if any behaviours need to be started for their first execution
        //BehaviourStartSequence();

        //iterate through all attached behaviours
        for (int i = 0; i < behaviours.size(); i++)
        {
            behaviours[i]->CheckActiveState();
            behaviours[i]->CanUpdate(deltaTime);
        }
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
    transform.gameObject = this;

    GameObject* parentTarget= (GameObject*)SceneManagement::objectRegister[transform.parentID];

    if (parentTarget)
    {
        transform.parent=&parentTarget->transform;
    }
}

std::string GameObject::GetTypeName() const {
    return "GameObject";
}

void GameObject::BehaviourSetup(Behaviour *b)
{
    SceneManagement::AddBehaviourForStart(b);
}

void GameObject::RemoveBehaviour(Behaviour* b)
{
	behaviours.erase(std::remove(behaviours.begin(), behaviours.end(), b), behaviours.end());
}

void GameObject::SetBehaviourParent(Behaviour* b)
{
	b->SetGameObject(this);
}

// -------------------------------------------------------------------------
// SERIALIZATION LOGIC
// -------------------------------------------------------------------------

void GameObject::Serialize(Serializer& s) {
    // 1. Context Setup
    std::string oldCtx = s.currentContext;
    s.currentContext = "GameObject" + std::to_string(ObjectID);

    // 2. Base Properties
    s.Property("ObjectID", ObjectID);
    s.Property("name", name);

    //Transform Properties
    s.Property("Position",transform.localPosition);
    s.Property("Rotation",transform.localRotation);
    s.Property("Scale",transform.localScale);

    if (transform.parent)
    {
        s.Property("ParentID",transform.parent->gameObject->ObjectID);
    }

    // 3. Behaviour Count
    int count = (int)behaviours.size();
    s.Property("B_Count", count);

    // ---------------- SAVE MODE ----------------
    if (s.mode == Mode::Saving) {
        for (int i = 0; i < count; i++) {
            std::string idx = std::to_string(i);

            // Get the clean type name (e.g., "SceneLoadDummy")
            std::string typeName = behaviours[i]->GetTypeName();

            // Save header info for the behaviour
            s.SaveString("B_Type_" + idx, typeName);
            s.Property("B_ObjectID_" + idx, behaviours[i]->ObjectID);



            // Serialize the behaviour's own data
            behaviours[i]->Serialize(s);
        }
    }
    // ---------------- LOAD MODE ----------------
    else {
        // Clear existing behaviours to prevent duplication during reload
        for (auto b : behaviours) delete b;
        behaviours.clear();

        for (int i = 0; i < count; i++) {
            std::string idx = std::to_string(i);
            std::string type;
            EntityID bID = 0;

            // Retrieve Header Info
            s.Property("B_Type_" + idx, type);
            s.Property("B_ObjectID_" + idx, bID);

            if (type.empty()) continue;

            // Factory creates new instance -> Generates RANDOM ID
            Behaviour* b = BehaviourFactory::Create(type);

            if (b) {

                // 1. Overwrite the Random ID with the Saved ID
                if (bID != 0) b->ForceID(bID);

                // 2. Link Parent immediately (so OnSerialize logic can use it if needed)
                b->gameObject = this;

                // 3. Now load the data (Serializer uses the Correct ID to find keys)
                b->Serialize(s);

                // *** CRITICAL FIX END ***

                behaviours.push_back(b);
            }
            else {
                std::cout << "[Error] Failed to create Behaviour of type: " << type << std::endl;
            }
        }
    }

    // Restore context
    s.currentContext = oldCtx;
}

std::vector<Behaviour *> GameObject::GetBehaviours()
{
    return behaviours;
}
