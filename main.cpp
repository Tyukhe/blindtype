#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode({600, 250}), "blindtype");
    window->setVerticalSyncEnabled(true);

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
        }
        window->clear(sf::Color::Black);

        window->display();
    }
    window->close();
    delete window;

    return 0;
}
