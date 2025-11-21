#ifndef STAGE_HPP
#define STAGE_HPP

#include <iostream>

#include "Managers/GraphicManager.hpp"
#include "Managers/EventManager.hpp"
#include "Managers/CollisionManager.hpp"

#include "Being.hpp"
#include "List/EntityList.hpp"

#include "Entities/Entity.hpp"
#include "Entities/Projectile.hpp"
#include "Entities/Characters/Enemies/Enemies.hpp"
#include "Entities/Characters/Enemies/Bat.hpp"
#include "Entities/Characters/Enemies/Skeleton.hpp"
#include "Entities/Characters/Enemies/Death.hpp"

#include "Entities/Obstacles/Obstacle.hpp"
#include "Entities/Floor.hpp"
#include "Entities/Obstacles/Platform.hpp"
#include "Entities/Obstacles/Spike.hpp"
#include "Entities/Obstacles/MudHand.hpp"
#include "utils/json.hpp"

#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

class Player;
namespace Stages {
    class Stage : public Being {
        protected:
            sf::RectangleShape background;
            sf::Texture bgTexture;
            sf::RectangleShape background2;
            sf::Texture bgTexture2;
            sf::RectangleShape background3;
            sf::Texture bgTexture3;

            Managers::EventManager* pEvent; 
            Managers::CollisionManager* pCollision;
            Managers::GraphicManager* pGraphic;

            Entities::Characters::Player* pPlayer1;
            Entities::Characters::Player* pPlayer2;

            List::EntityList* characterList;
            List::EntityList* obstacleList;
            List::EntityList* projectileList;
            List::EntityList* structureList;
            
            const int max_bats;
            const int max_obstacles;
            static const int tileSize = 32;

            
        protected:
            void createPlayer1(sf::Vector2f pos);
            void createPlayer2(sf::Vector2f pos);
            void createFloor(sf::Vector2f pos);
            void createPlatform(sf::Vector2f pos);
            void createSkeleton(sf::Vector2f pos);    
            
            virtual void createMap() = 0;

        public:
            Stage();
            virtual ~Stage();
            void createProjectile(sf::Vector2f size, int ddamage, float speed, float maxrange, sf::Vector2f position, int whoShot, bool useGravity);

            void draw(sf::RenderWindow* window);
            void execute() override;
            
    };
}

#endif