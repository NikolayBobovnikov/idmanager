// IdManager.cpp : Defines the entry point for the application.
//

#include <string>
#include <array>
#include "SequenceId.h"

namespace SequenceId {
  using std::string_view;
  using std::size_t;

  template <typename T, size_t N>
  constexpr size_t getDim(T const (&)[N])
  {
    return N;
  }


  static constexpr string_view  DISALLOWED_CHARS = "DFGJMQV";
  static constexpr string_view  ALL_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  static constexpr string_view  DIGITS = "123456789";

  static constexpr char disallowed_chars[] = { 'D','F','G','J','M','Q','V' };
  static constexpr char all_chars[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
  static constexpr std::array<char, getDim(disallowed_chars)> disallowed_chars_array = { 'D','F','G','J','M','Q','V' };
  static constexpr std::array<char, getDim(all_chars)> all_chars_array = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };


  constexpr bool isAllowed(char ch)
  {
    for (size_t i = 0; i < getDim(disallowed_chars); ++i)
      if (disallowed_chars[i] == ch) {
        return false;
      }

    return true;
  }

  constexpr size_t get_next_pos(size_t i)
  {
    while (!isAllowed(all_chars[i])) {
      ++i;
    }

    return i; // for example
  }

  template <int N>
  
  constexpr std::array<char, N> generate_allowed_chars_array()
  {
    std::array<char, N> arr{};

    size_t j = 0;
    size_t i = 0;

    while (j < N) {
      i = get_next_pos(i);
      arr[j++] = all_chars[get_next_pos(i)];
      ++i;
    }

    return arr;
  }

  static constexpr size_t allowed_chars_dim = getDim(all_chars) - getDim(disallowed_chars);

  static constexpr std::array<char, allowed_chars_dim> allow = generate_allowed_chars_array<allowed_chars_dim>();
}

namespace SequenceId {
  Id::Id()
    : _id("A1")
  {
  }

  Id::Id(const string& id)
    : _id(id)
  {
  }

  Id& Id::set(const string& s)
  {
    // TODO: insert return statement here
    return *this;
  }

  Id& Id::next()
  {
    // TODO: insert return statement here
    return *this;
  }

  Id::operator string() const
  {
    return _id;
  }

}