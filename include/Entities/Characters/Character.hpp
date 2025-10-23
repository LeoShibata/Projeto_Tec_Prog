#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entities/Entity.hpp"

namespace Characters {
    class Character : public Entity {
        protected:
	    int hp;
	    const int max_hp;
	
	protected:
	    void setHp(int hp);
	    int getHp();


        public:
            Character(float speed, const sf::Vector2f position, const sf::Vector2f size);
            virtual ~Character();
	    const int get_Maxhp() const;
            virtual void move() = 0;
	    virtual void execute() = 0;
    };
}

#endif
