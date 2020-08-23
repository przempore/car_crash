#include "color.hpp"

namespace Game::Wrappers {

    Color::Color(sf::Color c) : color_(c) {}

    sf::Color Color::getUnderlying() { return color_; }

    const Color Color::Black = Color(sf::Color::Black);
    const Color Color::White = Color(sf::Color::White);
    const Color Color::Red = Color(sf::Color::Red);
    const Color Color::Green = Color(sf::Color::Green);
    const Color Color::Blue = Color(sf::Color::Blue);
    const Color Color::Yellow = Color(sf::Color::Yellow);
    const Color Color::Magenta = Color(sf::Color::Magenta);
    const Color Color::Cyan = Color(sf::Color::Cyan);
    const Color Color::Transparent = Color(sf::Color::Transparent);

}  // namespace Game::Wrappers
