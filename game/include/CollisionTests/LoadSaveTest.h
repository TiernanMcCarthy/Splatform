//
// Created by Tiern on 18/02/2026.
//

#ifndef SPLATFORM_LOADSAVETEST_H
#define SPLATFORM_LOADSAVETEST_H
#include "LoadUI.h"
#include "Objects/GameObject.h"
#include "StartupSequence.h"
#include "UI/ScreenspaceButton.h"

class LoadSaveTEST: public  StartupSequence
{

public:



    void Execute() override
    {
        GameObject* newObj= new GameObject("Load Save Test");

        newObj->AddBehaviour<LoadUI>();


    }


};

#endif // SPLATFORM_LOADSAVETEST_H
