#include "render_window.hpp"

namespace Game::Wrappers {

RenderWindow::RenderWindow(sf::VideoMode mode, const std::string& title)
    : window_(mode, title) {}

void RenderWindow::setFramerateLimit(const uint32_t frame_rate) {
  window_.setFramerateLimit(frame_rate);
}

void RenderWindow::clear() { window_.clear(); }

void RenderWindow::draw(const sf::Drawable& drawable,
                        const sf::RenderStates& states) {
  window_.draw(drawable, states);
}

void RenderWindow::display() { window_.display(); }

bool RenderWindow::isOpen() const { return window_.isOpen(); }

void RenderWindow::close() { window_.close(); }

bool RenderWindow::pollEvent(sf::Event& event) {
  return window_.pollEvent(event);
}

}  // namespace Game::Wrappers
