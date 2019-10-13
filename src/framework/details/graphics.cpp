#include "graphics.hpp"

namespace Game::Wrappers {

Graphics::Graphics(sf::VideoMode mode, const std::string &title) : window_(mode, title) {}

void Graphics::setFramerateLimit(const uint32_t frame_rate) {
  window_.setFramerateLimit(frame_rate);
}

void Graphics::clear() {
  window_.clear();
}

void Graphics::draw(const sf::Drawable &drawable, const sf::RenderStates &states) {
  window_.draw(drawable, states);
}

void Graphics::display() {
  window_.display();
}

bool Graphics::isOpen() const {
  return window_.isOpen();
}

void Graphics::close() {
  window_.close();
}

bool Graphics::pollEvent(sf::Event &event) {
  return window_.pollEvent(event);
}

}
