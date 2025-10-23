#include "Entities/Characters/Character.hpp"

namespace Characters {

   void Character::setHp(int life){
      hp = life;
   }

   int Character::getHp(){
      return hp;
   }
   
   const int Character::get_Maxhp() const{
      return max_hp;
   }

   Character::Character(float speed, const sf::Vector2f position, const sf::Vector2f size): Entity(speed, position, size),
	max_hp(10), 
	hp(max_hp){
	
   }
   Character::~Character() { }


   }

//------------------------------------------------------------

// void andar(const bool toLeft);
// void stop();
// virtual void updatePosition();
// virtual void update() = 0;
