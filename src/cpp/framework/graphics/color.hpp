#ifndef CAR_CRASH_SRC_DETAILS_COLOR_HPP_
#define CAR_CRASH_SRC_DETAILS_COLOR_HPP_

#include <SFML/Graphics/Color.hpp>

namespace Game::Wrappers {

    class Color {
    public:
        Color(sf::Color c);

        ~Color() = default;

        Color() = delete;

        Color(Color const &) = default;

        Color(Color &&) = default;

        Color &operator=(Color const &) = default;

        Color &operator=(Color &&) = default;

    public:
        sf::Color getUnderlying();

    public:
        static const Color Black;
        static const Color White;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Yellow;
        static const Color Magenta;
        static const Color Cyan;
        static const Color Transparent;

    private:
        sf::Color color_;
    };

}  // namespace Game::Wrappers

#endif  // CAR_CRASH_SRC_DETAILS_COLOR_HPP_
