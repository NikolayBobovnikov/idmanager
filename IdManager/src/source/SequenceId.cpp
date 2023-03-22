// IdManager.cpp : Defines the entry point for the application.
//

#include <vector>
#include <array>
#include <string_view>
#include <algorithm>
#include <iterator>
#include "SequenceId.h"

namespace SequenceId
{
  using std::size_t;
  using std::string_view;

  template <typename T, size_t N>
  constexpr size_t getDim(T const (&)[N])
  {
    return N;
  }

  static constexpr string_view DISALLOWED_CHARS = "DFGJMQV";
  static constexpr string_view ALL_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  static constexpr string_view DIGITS = "123456789";

  static constexpr char disallowed_chars[] = {'D', 'F', 'G', 'J', 'M', 'Q', 'V'};
  static constexpr char all_chars[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  static constexpr std::array<char, getDim(disallowed_chars)> disallowed_chars_array = {'D', 'F', 'G', 'J', 'M', 'Q', 'V'};
  static constexpr std::array<char, getDim(all_chars)> all_chars_array = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

  constexpr bool isAllowed(char ch)
  {
    for (size_t i = 0; i < getDim(disallowed_chars); ++i)
      if (disallowed_chars[i] == ch)
      {
        return false;
      }

    return true;
  }

  constexpr size_t get_next_pos(size_t i)
  {
    while (!isAllowed(all_chars[i]))
    {
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

    while (j < N)
    {
      i = get_next_pos(i);
      arr[j++] = all_chars[get_next_pos(i)];
      ++i;
    }

    return arr;
  }

  static constexpr size_t allowed_chars_dim = getDim(all_chars) - getDim(disallowed_chars);

  static constexpr std::array<char, allowed_chars_dim> allow = generate_allowed_chars_array<allowed_chars_dim>();
}

namespace SequenceId
{
  using namespace std;
  using std::array;
  using std::string_view;
  using std::vector;

  class Id::Impl
  {
  public:
    Impl()
    {
      _id.reserve(MAX_GROUPS);
      _id.emplace_back();
    }

    Impl(const Impl &) = default;

    Impl(string_view id)
    {
      // TODO
    }

    Impl(const char *id)
    {
      // TODO
    }

    void set(const string &)
    {
      // TODO
    }

    void next()
    {
      // TODO
    }

    string get() const
    {
      string result;
      result.reserve(_id.size() * 3); // 3 elements (char,  digit, delimeter) per group

      static const char delimeter = '-';
      for (auto it = begin(_id); it != end(_id); ++it)
      {
        result.push_back(s_allowed_chars[it->index_char]);
        result.push_back(s_digits[it->index_digit]);

        if (std::next(it) != end(_id))
        {
          result.push_back(delimeter);
        }
      }

      result.shrink_to_fit(); // one group possibly unnecessary

      return result;
    }

  private:
    static constexpr array<char, allowed_chars_dim> s_allowed_chars = generate_allowed_chars_array<allowed_chars_dim>();
    static constexpr array<char, 9> s_digits = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    static constexpr size_t MAX_GROUPS = 10;
    struct Group
    {
      uint8_t index_char = 0;
      uint8_t index_digit = 0;
    };

    vector<Group> _id;
  };

  Id::Id()
      : _pimpl(make_unique<Impl>())
  {
  }

  Id::Id(const string &id)
      : _pimpl(make_unique<Impl>(id))
  {
  }

  Id::Id(const char *id)
      : _pimpl(make_unique<Impl>(id))
  {
  }

  Id::Id(const Id &other)
      : _pimpl(make_unique<Impl>(*other._pimpl))
  {
  }

  Id &Id::operator=(const Id &other)
  {
    if (this == &other)
    {
      return *this;
    }

    _pimpl = make_unique<Impl>(*other._pimpl);
    return *this;
  }

  Id::~Id() = default;

  Id &Id::set(const string &s)
  {
    _pimpl->set(s);
    return *this;
  }

  Id &Id::next()
  {
    _pimpl->next();
    return *this;
  }

  // const size_t Id::m_chars_count = getDim(all_chars) - getDim(disallowed_chars);

  string Id::get() const
  {
    return _pimpl->get();
  }
}