#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entities/Entity.hpp"
#include "Entities/Characters/Enemies/Enemies.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities {

class Projectile : public Entity{
    private:
        float maxrange;
        int damage;
        //maybe a fancy math
        float maxtime;
        float distance;
        bool isEraseble;
        float dt;
        int whoShot;
        //maybe add stage pointer
    private:
        void removeProjectile();
    public:
        Projectile(sf::Vector2f size, int damage, float speed, float maxrange, sf::Vector2f position, int whoShot);
        ~Projectile();
        virtual void collision(Entity* other, float over, int collisionType);
        virtual void update();
        virtual void execute();

        void damageEntity(Entity* other);//use id system and maybe one more bool to make targets
        //for now, the projectile will damage everything;
        void updateAnimation();
        void initialize();
};

}
#endif