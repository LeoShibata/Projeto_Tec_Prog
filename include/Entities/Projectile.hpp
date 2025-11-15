#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entities/Entity.hpp"
#include "Entities/Characters/Enemies/Enemies.hpp"

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
        int idEnt;
        //maybe add stage pointer
    private:
        void removeProjectile();
    public:
        Projectile(sf::Vector2f size, int damage, float speed, float maxrange, sf::Vector2f position);
        ~Projectile();
        virtual void collision(Entity* other, float over, int collisionType);
        virtual void update();
        virtual void execute();
        
        void damageEnemy(Entities::Characters::Enemies* pEnemy);//use id system and maybe one more bool to make targets
        //for now, the projectile will damage everything;
        void updateAnimation();
        void initialize();
};

}
#endif