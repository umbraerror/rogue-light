#include <SFML/Graphics.hpp>
#include <optional>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Rogue Light");

    sf::RectangleShape box({200.f, 150.f});
    box.setFillColor(sf::Color::Green);
    box.setPosition({30.f, 25.f}); // vector param in SFML 3

    while (window.isOpen()){
        // SFML 3: pollEvent returns std::optional<sf::Event>
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(box);
        window.display();
    }
    return 0;
}
