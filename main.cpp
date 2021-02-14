#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    // Adding antia-
    sf::ContextSettings AAsettings; AAsettings.antialiasingLevel = 8;

    // Create new window : 1600 x 900 px
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Fluid Simulation", sf::Style::Default, AAsettings);




    // Create a green circle with a radius of 100. pixels
    sf::CircleShape shape(200.f);
    shape.setFillColor(sf::Color::Green);

    // Main loop, while the window is open
    while (window.isOpen())
        {
            // Event loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                // If close is requested by user, close the window
                if (event.type == sf::Event::Closed) window.close();
            }
            // Display sequence : clear screen, draw circle and update display
            window.clear();
            window.draw(shape);
            window.display();
        }
    return 0;
}
