#include <iostream>
#include <SFML/Graphics.hpp>

#define IX(i, j) ((i) + N * (j))

const int N = 800;

struct Fluid
{
    float diff;
    float visc;

    float s;
    float density;

    float Vx;
    float Vy;

    float Vx0;
    float Vy0;

} fluid[N * N];

void set_bnd(int N, int b, int x)
{

}

void add_source (int N, float *x, float *s, float dt)
// this routine adds the source s[] to the density. 
// The source corresponds to the "inlet" of our fluid flow. 
// We will give s[] a certain value depending on our initial state.
{
    // x and s array must have pointers
    for (int i = 0; i < N * N; i++)
        x[i] += dt * s[i] ;  
}

void diffuse (int N, int b, float *x, float *x0, float diff, float dt)
{
    float a = dt * diff * N * N;
    for (int k = 0; k < 20; k++)
    {
        for (int i = 1; i < N; i++)
        {
            for (int j = 1; j < N; j++)
            {
                x[IX(i,j)] = (x0[IX(i,j)] + a *(x[IX(i - 1, j)] + 
                                                x[IX(i + 1, j)] +
                                                x[IX(i, j - 1)] + 
                                                x[IX(i, j + 1)]
                                                )
                                ) / (1 + 4 * a);
            }
        }
        set_bnd(N, b, x);
    }    
}

void advect (int N, int b, float *d, float *d0, float *u, float *v, float dt)
{
    int i0, j0, i1, j1;
    float x, y, s0, t0, s1, t1, dt0;
    dt0 = dt * N;

    for (int i = 1; i < N; i++)
    {
        for (int j = 1; j < N; j++)
        {
            x = i - dt0 * u[IX(i,j)]; 
            y = j - dt0 * v[IX(i,j)];
            if (x < 0.5) x = 0.5; if (x > N + 0.5) x = N + 0.5; i0 = (int)x; i1 = i0 + 1;
            if (y < 0.5) y = 0.5; if (y > N + 0.5) y = N + 0.5; j0 = (int)y; j1 = j0 + 1;
            s1 = x - i0; 
            s0 = 1 - s1;
            t1 = y - j0;
            t0 = 1 - t1;
            d[IX(i,j)] =    s0 * (t0 * d0[IX(i0,j0)] + t1 *  d0[IX(i0,j1)]) +
                            s1 * (t0 * d0[IX(i1,j0)] + t1 *  d0[IX(i1,j1)]);
        }
    }
    set_bnd(N, b, x);
}

int main ()
{
    // Adding anti-aliasing
    sf::ContextSettings AAsettings;
    AAsettings.antialiasingLevel = 8;

    // Create new window : 800 x 600 px
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
                    {
                        fluid[IX(i,j)].diff = 0;
                        if(/* Pixel i,j a fluid*/ true) image.setPixel(i, j, sf::Color::Transparent);
                    
                        // Pixel i,j is a boundary
			            else image.setPixel(i, j, sf::Color(255.f*r, 255.f*g, 255.f*b));
                    }     

            texture.loadFromImage(image);
	        sprite.setTexture(texture, true);
	        window.draw(sprite);

            window.display();
        }
    return 0;
}