#include "Entities/Entity.hpp"

   void Entity::setSpeedmod(float spd){
      speed_mod = spd;
   }
   void Entity::setVelocity(sf::Vector2f vel){
      velocity = vel;
   }

   Entity::Entity(float speed, sf::Vector2f position, sf::Vector2f size):
	   Being(size), speed_mod(speed){
	      body.setPosition(position);
              body.setFillColor(sf::Color::Green);
              velocity = sf::Vector2f(0.f, 0.f);
	   }
   Entity::~Entity(){}

   sf::Vector2f Entity::getVelocity(){
      return velocity;
   }
   sf::Vector2f Entity::getVelocity();
