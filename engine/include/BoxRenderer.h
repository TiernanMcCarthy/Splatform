#pragma once
#include <RenderObject.h>
#include <SFML/Graphics.hpp>


//Box that uses GameObject Size as reference for Rendering Shape
class BoxRenderer : public RenderObject
{
public:
	sf::RectangleShape box;

	sf::Color color;

	sf::Texture* renderTexture = nullptr;

	bool ApplyImage(std::string path);

    void ApplyImage(sf::Image& image);

	void Render(sf::RenderWindow *target) override;

	void UpdateVisualComponents() override;

	void Start() override;

	BoxRenderer(sf::Vector2<float> dimensions = sf::Vector2<float>(100,100));

    std::string imagePath;

    REFLECT_BEGIN(BoxRenderer, Behaviour)
         s.Property("color", color);
        // Save box size
        sf::Vector2f size = box.getSize();
        s.Property("size", size);
        s.Property("imagePath",imagePath);
        if (s.mode == Mode::Loading)
        {
            box.setSize(size);
            if (!imagePath.empty())
            {
                ApplyImage(imagePath);
            }
        }
    REFLECT_END()

private:


};
