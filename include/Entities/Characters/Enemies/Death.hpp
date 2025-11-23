#ifndef DEATH_HPP 
#define DEATH_HPP

#include "Entities/Characters/Enemies/Enemies.hpp"

namespace Stages {
    class Stage;
}

namespace Entities::Characters {
    class Death : public Enemies {
        private: 
            float soul; // Mudar atributo
            Stages::Stage* pStage;
        

        private:
            void initialize();

            void attack() override;
            sf::FloatRect getAttackHitbox() const override;
            void updateAnimation() override;

        protected:
            void performMovement(Player* pTarget, float distance_to_player_sq) override; 

        public:
            Death(const sf::Vector2f position, const sf::Vector2f size, int maldade);
            ~Death();

            void shoot();
            void setStage(Stages::Stage* pStage);
            
            void move() override;
            void execute() override;
            void collision(Entities::Entity* other, float ds, int collisionType) override;
            
            nlohmann::json save() override;
    };
}

#endif