#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entities/Characters/Character.hpp"

namespace Stages {
    class Stage;
} //referencia bidirecional, fazer foward declaration para evitar include circular dependecies;

namespace Entities::Characters {
    class Player : public Character {
        private:
            int playerID;
            float jumpSpeed;
            float currentDamageMultiplier;
            bool isTakingDamage;
            Stages::Stage* pStage;
            
            bool isShooting;
            float shootingCooldown;
            sf::Clock shootingTimer;

            bool isSlowed;
            float slowDuration;
            sf::Clock slowTimer;

            int score;


        private:
            void initialize();

        public:
            Player(const sf::Vector2f position, const sf::Vector2f size, int playerID);
            virtual ~Player();
            
            void jump();
            void setDamageMultiplier(float mult);
            void applySlow(float duration);
            void attack();
            bool getIsAttacking() const;
            sf::FloatRect getAttackHitbox() const;
            void updateAnimation();
            void collision(Entities::Entity* other, float ds, int collisionType);
            void setStage(Stages::Stage* pStage);
            void shoot();   

            void addScore(int points);
            int getScore() const;

            void operator++();

            void takeDamage(int damage) override;
            void move() override;
            void update() override;
            void execute() override;

            nlohmann::json save() override;
    };
}

#endif
