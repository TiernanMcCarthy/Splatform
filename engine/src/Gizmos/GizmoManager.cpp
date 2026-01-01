//
// Created by tiernux on 31/12/2025.
//
#include "Gizmos/GizmoManager.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include <cmath>


std::deque<GizmoDrawCommand*> GizmoManager::drawCommands;
sf::Color GizmoManager::Colour;

GizmoManager::GizmoManager()
{

}

GizmoLine::GizmoLine(sf::Vector2f a,sf::Vector2f b, float lineThickness)
{
    pointA=a;
    pointB=b;
    thickness=lineThickness;
}

void GizmoManager::StartDraw(sf::RenderWindow* drawTarget)
{
    if (drawTarget == nullptr)
    {
        printf(("DrawTarget for Gizmo is nullptr\n"));
    }

    int elementsToDraw=GizmoManager::drawCommands.size();
    for (int i=0; i<elementsToDraw; i++)
    {
        drawCommands[i]->DrawGizmo(drawTarget);
    }

    drawCommands.clear();
}

void GizmoManager::DrawLine(sf::Vector2f pointA, sf::Vector2f pointB, float lineThickness)
{
    GizmoLine* command= new GizmoLine(pointA, pointB,lineThickness);
    command->color=GizmoManager::Colour;
    drawCommands.push_back(command);
}

void GizmoLine::DrawGizmo(sf::RenderWindow *render)
{
    float dx = pointB.x - pointA.x;
    float dy = pointB.y - pointA.y;

    float distance = std::sqrt(dx * dx + dy * dy);
    sf::RectangleShape line({distance, thickness});

    line.setPosition(pointA);
    line.setOrigin(sf::Vector2f(0.f, 0.5f));

    line.setFillColor(color);

    float angle = std::atan2(dy, dx);

    line.rotate(sf::degrees(angle*57.2958f));



    render->draw(line);
}




void GizmoDrawCommand::DrawGizmo(sf::RenderWindow *render)
{
    printf("Unimplemented GizmoDrawCommands::GizmoDrawCommand::DrawGizmo\n");
}

GizmoDrawCommand::GizmoDrawCommand()
{

}

