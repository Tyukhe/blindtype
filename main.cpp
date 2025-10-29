#include <SFML/Graphics.hpp>

sf::FloatRect resizeSprite(sf::Vector2f wSize, sf::Vector2f sSize){
    sf::FloatRect res(wSize, sSize);
    if (wSize.x * sSize.y >= wSize.y * sSize.x) {
        float mod = wSize.y / sSize.y;
        res.size = {mod, mod};
        res.position = {(wSize.x - (sSize.x * mod)) / 2.f, 0.f};
    } else {
        float mod = wSize.x / sSize.x;
        res.size = {mod, mod};
        res.position = {0.f, (wSize.y - (sSize.y * mod)) / 2.f};
    }
    return res;
}

int main()
{
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode({600, 250}), "blindtype");
    window->setFramerateLimit(10);
    sf::Vector2f wSize = sf::Vector2f(window->getSize());

    sf::Texture texture(("keyboard.png"));
    sf::Sprite sprite(texture);

    sf::FloatRect newState = resizeSprite(wSize, sf::Vector2f(texture.getSize()));
    sprite.setScale(newState.size);
    sprite.setPosition(newState.position);

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
                window->setView(sf::View(visibleArea));
                wSize = sf::Vector2f(window->getSize());
                newState = resizeSprite(wSize, sf::Vector2f(texture.getSize()));
                sprite.setScale(newState.size);
                sprite.setPosition(newState.position);
            }
        }
        window->clear(sf::Color::Black);

        window->draw(sprite);

        window->display();
    }
    window->close();
    delete window;

    return 0;
}
