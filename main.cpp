#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    // Adding anti-aliasing
    sf::ContextSettings AAsettings;
    AAsettings.antialiasingLevel = 8;

    // Create new window : 800 x 600 px
    int width = 1600, height = 1200;
    sf::RenderWindow window(sf::VideoMode(width, height), 
        "Fluid Simulation", sf::Style::Default, AAsettings);

    // Plotter
    sf::Image image;        // object for manipulating image
    sf::Texture texture;    // image living on the graphics card used for drawing    
    sf::Sprite sprite;      // drawable representation of texture, color, etc...
    sf::VertexArray VA;     // define a set of one 2D primitive

    // image init
    image.create(width, height, sf::Color::Black);
	texture.loadFromImage(image);
	sprite.setTexture(texture, true);
	VA.setPrimitiveType(sf::Lines);

    while (window.isOpen())
        {
            
            // fluid.update() {}
            /*
            get_from_UI (dens_prev, u_prev, v_prev);
            vel_step(N, u, v, u_prev, v_prev, visc, dt)
            dens_step(N, dens, dens_prev, u, v, diff, dt)
            */

            window.clear();

            // Draw the scalar field
            float r(0), g(0), b(0);
            for (int i(0); i < width; i++)
                for (int j(0); j < height; j++)
                    image.setPixel(i, j, sf::Color(255.f*r, 255.f*g, 255.f*b));
            
            // Draw the boundaries
            for (int i(0); i < width; i++)
		        for (int j(0); j < height; j++)
			        if(/* Pixel i,j a fluid*/ true) image.setPixel(i, j, sf::Color::Transparent);
                    
                    // Pixel i,j is a boundary
			        else image.setPixel(i, j, sf::Color(255.f*r, 255.f*g, 255.f*b));


            texture.loadFromImage(image);
	        sprite.setTexture(texture, true);
	        window.draw(sprite);

            window.display();
        }
    return 0;
}
