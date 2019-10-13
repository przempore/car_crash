#ifndef CAR_CRASH_SRC_GAME_GRAPHICS_HPP_
#define CAR_CRASH_SRC_GAME_GRAPHICS_HPP_

#include <string>

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Game::Wrappers {

class Graphics {
 public:
  Graphics(sf::VideoMode mode, const std::string &title);
  void setFramerateLimit(const uint32_t frame_rate);
  bool isOpen() const;
  void close();
  bool pollEvent(sf::Event& event);
  void clear();
  void draw(const sf::Drawable &drawable, const sf::RenderStates &states = sf::RenderStates::Default);
  void display();

 private:
  sf::RenderWindow window_;
};

}

#endif //CAR_CRASH_SRC_GAME_GRAPHICS_HPP_
