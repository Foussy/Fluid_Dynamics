#include <iostream>
#include <SFML/Graphics.hpp>
#include </home/foussy/Programming/C++/Fluid_Dynamics/Fluid.h>
#include <Grid.h>

#define IX(i,j) ((i)+(N)*(j))

int main ()
{
    sf::ContextSettings AAsettings;
    AAsettings.antialiasingLevel = 8;

    const int N = 500;
    int width = N, height = N;
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


    Fluid fluid(0.1, 0, 0);
    Grid grid(N*N);
    

    while (window.isOpen())
        {
            // fluid.update() {}
            /*
            get_from_UI (dens_prev, u_prev, v_prev);
            vel_step(N, u, v, u_prev, v_prev, visc, dt)
            dens_step(N, dens, dens_prev, u, v, diff, dt)
            */
           sf::Event e;
           while (window.pollEvent(e))
            {
                if (e.type == sf::Event::Closed)
                    window.close();
            }            

            window.clear();
            for (int i(0); i < width; i++)
                {
                    for (int j(0); j < height; j++)
                    {
                        // float d = fluid[IX(i,j)].density * 255;
                        // image.setPixel(i, j, sf::Color(d, d, d));
                    }
                }
            texture.loadFromImage(image);
	        sprite.setTexture(texture, true);
	        window.draw(sprite);

            window.display();
        }
    return 0;
}