#ifndef CAR_CRASH_SRC_GAME_INPUT_HPP_
#define CAR_CRASH_SRC_GAME_INPUT_HPP_

#include <cstdint>

namespace Game::Input {

enum class KeyState { Down, Up };

enum class Key : std::int32_t {
  Unknown = -1,  // Unhandled key
  // letters
  A = 0,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
  I,
  J,
  K,
  L,
  M,
  N,
  O,
  P,
  Q,
  R,
  S,
  T,
  U,
  V,
  W,
  X,
  Y,
  Z,

  // numbers
  Num0,
  Num1,
  Num2,
  Num3,
  Num4,
  Num5,
  Num6,
  Num7,
  Num8,
  Num9,

  // control keys
  Escape,
  LeftControl,
  LeftShift,
  LeftAlt,
  LeftSystem,  // The left OS specific key: window (Windows and Linux), apple
               // (MacOS X), ...
  RightControl,
  RightShift,
  RightAlt,
  RightSystem,  // The right OS specific key: window (Windows and Linux), apple
                // (MacOS X), ...
  Menu,         // The Menu key

  // special signs
  LeflBracket,   // The [ key
  RightBracket,  // The ] key
  Semicolon,     // The ; key
  Comma,         // The , key
  Period,        // The . key
  Quote,         // The ' key
  Slash,         // The / key
  Backslash,     // The \ key
  Tilde,         // The ~ key
  Equal,         // The = key
  Hyphen,        // The - key (hyphen)
  Space,         // The Space key
  Enter,         // The Enter/Return keys
  Backspace,     // The Backspace key
  Tab,           // The Tabulation key
  PageUp,        // The Page up key
  PageDown,      // The Page down key
  End,           // The End key
  Home,          // The Home key
  Insert,        // The Insert key
  Delete,        // The Delete key
  Add,           // The + key
  Subtract,      // The - key (minus, usually from numpad)
  Multiply,      // The * key
  Divide,        // The / key
  // arrows
  Left,
  Right,
  Up,
  Down,

  // The numpad numbers keys
  Numpad0,
  Numpad1,
  Numpad2,
  Numpad3,
  Numpad4,
  Numpad5,
  Numpad6,
  Numpad7,
  Numpad8,
  Numpad9,
  F1,
  F2,
  F3,
  F4,
  F5,
  F6,
  F7,
  F8,
  F9,
  F10,
  F11,
  F12,
  F13,
  F14,
  F15,

  Pause,  // The Pause key

  KeyCount,  // Keep last -- the total number of keyboard keys
};

struct Keyboard {
  KeyState state;
  Key code;
};

}  // namespace Game::Input

#endif  // CAR_CRASH_SRC_GAME_INPUT_HPP_
