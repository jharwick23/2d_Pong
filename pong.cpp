#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Create a window with a default resolution of 800x600
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");

    // Main loop ends when window is closed
    while (window.isOpen())
    {
        // Create event to hold even data
        sf::Event event;

        while (window.pollEvent(event))
        {

            // Check if the window close event was triggered
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Clear the window before rendering a new frame
        window.clear();

        window.display();
    }

    return 0;
}
