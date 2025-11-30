#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Entities/Entity.hpp"
#include "Managers/GraphicManager.hpp"
#include "SFML/Graphics.hpp"

#include <iostream>
#include <string>

namespace Entities {
    class Button : public Entity {
        private:
            sf::Text text;
            sf::Font font;
            bool selected;
        

        public:
            Button(sf::Vector2f position, std::string info, const float textSize = 30);
            ~Button();

            void select(bool isSelected);

            void execute() override;
            void update() override;
            void collision(Entity* other, float over, int collisionType) override;

            nlohmann::json save() override;
    };
}

#endif