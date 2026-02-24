//
// Created by tiernan on 2/24/26.
//

#ifndef SPLATFORM_EDITORTEMPCAMERA_H
#define SPLATFORM_EDITORTEMPCAMERA_H

#include "Objects/Behaviour.h"
class EditorTempCamera: public Behaviour
{
public:


    sf::View cameraView;

    sf::RenderWindow *renderTarget;

    float zoomSpeed = 1.1f;
    float zoomLevel = 1;

    float oldZoom=1;

    void SetCameraPos(sf::Vector2f pos);
    void Start() override;

    void Update(float deltaTime) override;


    private:
};

#endif //SPLATFORM_EDITORTEMPCAMERA_H