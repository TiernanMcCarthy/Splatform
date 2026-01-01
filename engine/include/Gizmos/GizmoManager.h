//
// Created by tiernux on 28/12/2025.
//

#ifndef SPLATFORM_GIZMOMANAGER_H
#define SPLATFORM_GIZMOMANAGER_H
#include <deque>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

#endif //SPLATFORM_GIZMOMANAGER_H


class GizmoDrawCommand
{
    public:
    virtual ~GizmoDrawCommand() = default;

    sf::Color color;
    GizmoDrawCommand();

    virtual void DrawGizmo(sf::RenderWindow *render);
};

class GizmoLine : public GizmoDrawCommand
{
    private:
    sf::Vector2f pointA;
    sf::Vector2f pointB;

    public:

    float thickness;

    GizmoLine(sf::Vector2f pointa, sf::Vector2f pointb,float lineThickness=10);
    void DrawGizmo(sf::RenderWindow *render) override;
};




class GizmoManager
{
    public:

    GizmoManager();

    void StartDraw(sf::RenderWindow* drawTarget);

    static sf::Color Colour;

    static void DrawLine(sf::Vector2f pointA, sf::Vector2f pointB,float lineThickness=10);

private:

    static std::deque<GizmoDrawCommand*> drawCommands;


};
