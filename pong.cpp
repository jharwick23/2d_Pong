#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Create a window with a default resolution of 800x600
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");

    // Create user paddle
    sf::RectangleShape userPaddle(sf::Vector2f(100.f, 20.f));
    userPaddle.setFillColor(sf::Color::White);
    userPaddle.setOrigin(50.f, 10.f);
    userPaddle.setRotation(90.f);
    userPaddle.setPosition(40.f, 300.f);

    // Create computer paddle
    sf::RectangleShape compPaddle(sf::Vector2f(100.f, 20.f));
    compPaddle.setFillColor(sf::Color::Red);
    compPaddle.setOrigin(50.f, 10.f);
    compPaddle.setRotation(90.f);
    compPaddle.setPosition(760.f, 300.f);

    // Create the ball
    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::Blue);
    ball.setOrigin(10.f, 10.f);
    ball.setPosition(400.f, 300.f);

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

        // Get mouse position relative to the window
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // Convert to float and set shape position
        userPaddle.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // Clear the window before rendering a new frame
        window.clear();

        // Draw the user paddle
        window.draw(userPaddle);

        // Draw the computer paddle
        window.draw(compPaddle);

        // Draw the ball
        window.draw(ball);

        // Display the updated frame
        window.display();
    }

    return 0;
}
