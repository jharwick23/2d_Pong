#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

// Helper function to reset the game state.
void resetGame(sf::CircleShape &ball, sf::Vector2f &velocity, const sf::Vector2u &windowSize)
{
    // Center the ball.
    ball.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
    // Reset the ball's velocity to its initial value.
    velocity = sf::Vector2f(-0.5f, 0.f);
}

int main()
{
    // Create a window with a default resolution of 800x600
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");

    // Create user paddle
    sf::RectangleShape userPaddle(sf::Vector2f(50.f, 5.f));
    userPaddle.setFillColor(sf::Color::White);
    userPaddle.setOrigin(userPaddle.getSize().x / 2, userPaddle.getSize().y / 2);
    userPaddle.setRotation(90.f);
    userPaddle.setPosition(40.f, 300.f);

    // Create computer paddle
    sf::RectangleShape compPaddle(sf::Vector2f(50.f, 5.f));
    compPaddle.setFillColor(sf::Color::White);
    compPaddle.setOrigin(compPaddle.getSize().x / 2, compPaddle.getSize().y / 2);
    compPaddle.setRotation(90.f);
    compPaddle.setPosition(760.f, 300.f);

    // Create the ball
    const float ballRadius = 5.f;
    sf::CircleShape ball(ballRadius);
    ball.setFillColor(sf::Color::White);
    ball.setOrigin(10.f, 10.f);
    ball.setPosition(400.f, 300.f);

    // Initial velocity of the ball moving left
    sf::Vector2f velocity(-0.5f, 0.f);

    // maxBounceAngle for ball
    const float maxBounceAngle = 75.f * 3.14159f / 180.f;
    // AI paddle speed
    const float aiSpeed = 0.5f;

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

        // Define margin to keep whitespace from boundary
        float margin = 10.f;

        // Get mouse position relative to the window
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        float newY = static_cast<float>(mousePos.y);

        // Correct boundary limits considering the rotated paddle
        float paddleHeight = userPaddle.getSize().x;
        float topBound = margin + (paddleHeight / 2);
        float bottomBound = 600.f - (paddleHeight / 2) - margin;

        // Clamp Y position correctly
        newY = std::clamp(newY, topBound, bottomBound);

        // Set only the Y position, keeping X fixed
        userPaddle.setPosition(userPaddle.getPosition().x, newY);

        // Ai paddle movement logic
        float compPaddleCenter = compPaddle.getPosition().y;
        float ballCenter = ball.getPosition().y + ballRadius;

        // Move the AI paddle towards the ball
        if (ballCenter < compPaddleCenter)
        {
            compPaddle.move(0, -aiSpeed);
        }
        else if (ballCenter > compPaddleCenter)
        {
            compPaddle.move(0, aiSpeed);
        }

        sf::Vector2f compPos = compPaddle.getPosition();
        compPos.y = std::clamp(compPos.y, topBound, bottomBound);
        compPaddle.setPosition(compPos);

        // Update ball position
        ball.move(velocity);

        if (ball.getPosition().y - ball.getRadius() <= 0 ||
            ball.getPosition().y + ball.getRadius() >= window.getSize().y)
        {
            velocity.y = -velocity.y;
        }

        // User paddle collision
        if (ball.getGlobalBounds().intersects(userPaddle.getGlobalBounds()))
        {
            // Determine where on the paddle the ball hit:
            float paddleCenterY = userPaddle.getPosition().y;
            float ballY = ball.getPosition().y;
            float relativeIntersectY = paddleCenterY - ballY; // positive if hit above the center

            // Normalize (assume half the paddle's length is the maximum offset)
            float paddleHalfLength = userPaddle.getSize().x / 2.f; // 25.f in this case
            float normalizedRelativeIntersectionY = relativeIntersectY / paddleHalfLength;

            // Calculate the bounce angle.
            float bounceAngle = normalizedRelativeIntersectionY * maxBounceAngle;

            // Increase the ball's speed a little
            float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
            speed *= 1.05f;

            // For the left paddle, the ball should travel to the right.
            velocity.x = speed * std::cos(bounceAngle);
            velocity.y = -speed * std::sin(bounceAngle);
        }

        // Computer paddle collision
        else if (ball.getGlobalBounds().intersects(compPaddle.getGlobalBounds()))
        {
            float paddleCenterY = compPaddle.getPosition().y;
            float ballY = ball.getPosition().y;
            float relativeIntersectY = paddleCenterY - ballY;
            float paddleHalfLength = compPaddle.getSize().x / 2.f;
            float normalizedRelativeIntersectionY = relativeIntersectY / paddleHalfLength;
            float bounceAngle = normalizedRelativeIntersectionY * maxBounceAngle;

            float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
            speed *= 1.05f;

            // For the right paddle, the ball should travel to the left.
            velocity.x = -speed * std::cos(bounceAngle);
            velocity.y = -speed * std::sin(bounceAngle);
        }

        if (ball.getPosition().x - ball.getRadius() < 0 ||
            ball.getPosition().x + ball.getRadius() > window.getSize().x)
        {
            resetGame(ball, velocity, window.getSize());
        }

        // Rendering
        window.clear();
        window.draw(userPaddle);
        window.draw(compPaddle);
        window.draw(ball);
        window.display();
    }

    return 0;
}
