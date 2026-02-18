//
// Created by Tiern on 18/02/2026.
//

#ifndef SPLATFORM_LOADUI_H
#define SPLATFORM_LOADUI_H
#include "Constants.h"
#include "Objects/Behaviour.h"

class TextBox;
class ScreenSpaceButton;
class LoadUI : public Behaviour
{

    public:


    ScreenSpaceButton* loadSave=nullptr;

    TextBox* speedTitle=nullptr;

    void Start() override;


     //REFLECT_BEGIN(LoadUI,Behaviour)
    // REFLECT_END()


};

#endif // SPLATFORM_LOADUI_H

