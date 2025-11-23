#ifndef BAT_HPP
#define BAT_HPP

#include "Entities/Characters/Enemies/Enemies.hpp"

namespace Entities::Characters {
    class Bat : public Enemies {
        private:
            float soul;


        private:
            void initialize();
            sf::Vector2f normalize(sf::Vector2f vector);

            void attack() override;
            sf::FloatRect getAttackHitbox() const override;
            void updateAnimation() override;
        
        protected:
            void performMovement(Player* pTarget, float distance_to_player_sq) override; // sobrescreve passos do template method

        public:
            Bat(const sf::Vector2f position, const sf::Vector2f size, int maldade);
            ~Bat();
            
            void move() override;
            void execute() override;
            void collision(Entities::Entity* other, float ds, int collisionType) override;

            nlohmann::json save() override;
    };
}

#endif
