#include <SFML/Graphics.hpp>
#include <optional>
#include <cmath> // std::sqrt

#ifndef GAME_TEST
sf::Vector2f fetchDir(){
    sf::Vector2f dir{0.f, 0.f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
        dir.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
        dir.x += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
        dir.y -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
        dir.y += 1.f;
    }
    if (dir.x != 0.f || dir.y != 0.f) {
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        dir /= len;
    }

    return dir;
}
#endif

class Player{
public:
    sf::RectangleShape myBox;

    Player(){
        myBox = sf::RectangleShape({200.f, 150.f});
        myBox.setFillColor(sf::Color::Green);
        myBox.setPosition({30.f, 25.f}); // SFML 3: vector param

        speed = 300.f;
        pos  = myBox.getPosition();
        size = myBox.getSize();
    };

    void MoveEvent(float dt, sf::Vector2u winSize){
        myBox.move(fetchDir() * speed * dt);

        pos  = myBox.getPosition();
        size = myBox.getSize();

        // left/top
        if (pos.x < 0.f){
            pos.x = 0.f;
        }

        // left/top
        if (pos.y < 0.f){
            pos.y = 0.f;
        }

        // right/bottom
        if (pos.x + size.x > static_cast<float>(winSize.x)){
            pos.x = static_cast<float>(winSize.x) - size.x;
        }

        // right/bottom
        if (pos.y + size.y > static_cast<float>(winSize.y)){
            pos.y = static_cast<float>(winSize.y) - size.y;
        }

        myBox.setPosition(pos);
    };
private:
    float speed;
    sf::Vector2f pos;
    sf::Vector2f size;
};

int main() {
    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "Rogue Light");
    sf::Clock clock;
    Player aGuy = Player();

    while (window.isOpen()) {
        // Events
        while (const std::optional ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()){
                 window.close();
            }
        }

        // Update
        float dt = clock.restart().asSeconds();

        // Check Action Events
        aGuy.MoveEvent(dt, window.getSize());

        // Draw
        window.clear(sf::Color::Black);
        window.draw(aGuy.myBox);
        window.display();
    }
    return 0;
}

