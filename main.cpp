#include <SFML/Graphics.hpp>

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(1200,1600), "Hello From SFML");
    sf::RectangleShape shape(70.f , 70.f);
    shape.setFillColor(sf::Color::Magenta);
    float vel_r = 3;
    float vel_l = 3;
    float vel_u = 3;
    float vel_d = 3;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
	    
            }
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
    		// left key is pressed: move our character
			printf("le keyboard\n");
    			shape.move(-vel_l, 0.f);
		}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                // left key is pressed: move our character
                        printf("le keyboard\n");
                        shape.move(vel_r, 0.f);
                }
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                // left key is pressed: move our character
                        printf("le keyboard\n");
                        shape.move(0.f, -vel_u);
                }
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                // left key is pressed: move our character
                        printf("le keyboard\n");
                        shape.move(0.f, vel_d);
                }


	}
        window.clear();
        window.draw(shape);
        window.display();
        
    }

    return 0;
}
