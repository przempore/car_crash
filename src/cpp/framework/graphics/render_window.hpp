#ifndef CAR_CRASH_SRC_DETAILS_RENDER_WINDOW_HPP_
#define CAR_CRASH_SRC_DETAILS_RENDER_WINDOW_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <string>

namespace Game::Wrappers {

class RenderWindow {
 public:
  RenderWindow(sf::VideoMode mode, const std::string& title);
  ~RenderWindow() = default;
  RenderWindow() = delete;
  RenderWindow(RenderWindow const&) = delete;
  RenderWindow(RenderWindow&&) = delete;
  RenderWindow& operator=(RenderWindow const&) = delete;
  RenderWindow& operator=(RenderWindow&&) = delete;
  void setFramerateLimit(const uint32_t frame_rate);
  bool isOpen() const;
  void close();
  bool pollEvent(sf::Event& event);
  void clear();
  void draw(const sf::Drawable& drawable,
            const sf::RenderStates& states = sf::RenderStates::Default);
  void display();

 private:
  sf::RenderWindow window_;
};

}  // namespace Game::Wrappers

#endif  // CAR_CRASH_SRC_DETAILS_RENDER_WINDOW_HPP_
