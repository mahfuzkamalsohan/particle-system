#include <SFML/Graphics.hpp>
#include <random>
#include <vector>


struct Particle
{
    sf::CircleShape circle;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;



    Particle(float radius, float randomVelocity, sf::Vector2f mousePosition) :
    circle(radius), velocity{randomVelocity, randomVelocity}, acceleration{0.f, 0.1}
    {
        circle.setFillColor(sf::Color::Black);
        circle.setPosition(mousePosition);
    }


    void isCollidingWith(Particle& other)
    {
        //distance between 2 particles
        sf::Vector2f pos1 = circle.getPosition();
        sf::Vector2f pos2 = other.circle.getPosition();
        float distance = std::sqrt(std::pow(pos2.x - pos1.x, 2) + std::pow(pos2.y - pos1.y, 2));

        //sum of radius of 2 particles
        float radius1 = circle.getRadius();
        float radius2 = other.circle.getRadius();
        float minDistance = radius1 + radius2;

        if (distance <= minDistance) //then they are colliding
        {
            sf::Vector2f normal = (pos2 - pos1) / distance; //normalizing
            sf::Vector2f relativeVelocity = other.velocity - velocity;
            float impulseMagnitude = (relativeVelocity.x * normal.x + relativeVelocity.y * normal.y); //dot product
            sf::Vector2f impulse = normal * impulseMagnitude;

            //inter-penetration bug fix
            sf::Vector2f repulse = normal * (minDistance - distance);
            circle.setPosition(pos1 - repulse);
            other.circle.setPosition(pos2 + repulse);


            // Update velocities
            velocity += impulse;
            other.velocity -= impulse;

        }
    }





    void update(int windowWidth, int windowHeight)
    {
        sf::Vector2f position = circle.getPosition();
        float radius = circle.getRadius();


        // Boundary Collision: Reverse direction while retaining velocity magnitude
        if (position.x <= 0)
        {
            position.x = 0; // Clamp position to avoid sticking
            velocity.x = std::abs(velocity.x); // Ensure positive X velocity
        }
        if (position.x >= windowWidth - 2 * radius)
        {
            position.x = windowWidth - 2 * radius; // Clamp position
            velocity.x = -std::abs(velocity.x); // Ensure negative X velocity
        }
        if (position.y <= 0)
        {
            position.y = 0; // Clamp position
            velocity.y = std::abs(velocity.y); // Ensure positive Y velocity
        }
        if (position.y >= windowHeight - 2 * radius)
        {
            position.y = windowHeight - 2 * radius; // Clamp position
            velocity.y = -std::abs(velocity.y); // Ensure negative Y velocity
        }


        //Update
        velocity += acceleration;
        position += velocity;
        circle.setPosition(position);

    }
};


int main ()
{
    const int windowWidth = 400;
    const int windowHeight = 400;
    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Particle System");
    window.setFramerateLimit(60);


    int N_Particles = 10;


    std::random_device rd; // Seed generator
    std::mt19937 gen(rd()); // Random number engine
    std::uniform_real_distribution<> randomVelocity(-1.0, 1.0); // Range [-1, 1]
    std::uniform_real_distribution<> randomRadius(5.f, 10.f); // Range [5, 10]

    std::vector<Particle> particles;

    for (int i = 0; i < N_Particles; i++)
    {
        particles.emplace_back(randomRadius(gen), randomVelocity(gen), sf::Vector2f{200,200});
    }


    while(window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                window.close();
            }
        }


        //Click to Spawn
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            particles.emplace_back(randomRadius(gen), randomVelocity(gen), (sf::Vector2f)sf::Mouse::getPosition(window));
        }



        //Update physics
        for (Particle& particle : particles)
        {
            particle.update(windowWidth, windowHeight);
        }

        // Check and resolve collisions
        for (int i = 0; i < particles.size(); ++i)
        {
            for (int j = i + 1; j < particles.size(); ++j)
            {
                particles[i].isCollidingWith(particles[j]);
            }
        }


        window.clear(sf::Color::White);

        for (Particle& particle : particles)
        {
            window.draw(particle.circle);
        }

        window.display();
    }

}
