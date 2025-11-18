#ifndef SKELETON_HPP 
#define SKELETON_HPP

#include "Entities/Characters/Enemies/Enemies.hpp"

namespace Entities::Characters {
    class Skeleton : public Enemies {
        private: 
            float soul; // Mudar atributo
        

        private:
            void initialize();

            void attack() override;
            sf::FloatRect getAttackHitbox() const override;
            void updateAnimation() override;

        protected:
            void performMovement(Player* pTarget, float distance_to_player_sq) override; // sobrescreve passos do template method

        public:
            Skeleton(const sf::Vector2f position, const sf::Vector2f size, int maldade);
            ~Skeleton();

            void move() override;
            void execute() override;
            void collision(Entities::Entity* other, float ds, int collisionType) override;    
    };
}

#endif