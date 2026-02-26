//
// Created by tiernan on 2/25/26.
//

#ifndef SPLATFORM_BUTTONFUNCTIONALITY_H
#define SPLATFORM_BUTTONFUNCTIONALITY_H
#include <Objects/Behaviour.h>
#include <UI/Button.h>

class EditorButton;
class BoxRenderer;

class ButtonFunctionality : public Behaviour
{
public:

    void Start() override;

private:

    EditorButton* deleteObject =nullptr;

    BoxRenderer* canvas = nullptr;

    BoxRenderer* terrainCanvas=nullptr;
};
#endif //SPLATFORM_BUTTONFUNCTIONALITY_H