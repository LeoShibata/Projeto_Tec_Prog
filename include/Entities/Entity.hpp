#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Being.hpp"

    class Entity : public Being {
    
       protected:
	  //sf::Vector2f position;
	  sf::Vector2f velocity;
	  float speed_mod;
	  //buffer ostream
       
       protected:
	  void setSpeedmod(float spd);
	  void setVelocity(sf::Vector2f vel);

       public:
	  Entity(float speed, sf::Vector2f position, sf::Vector2f size);
	  virtual ~Entity();
  
	  float getSpeedmod();
	  sf::Vector2f getVelocity();
    };

#endif
