#include <vector>
#include <array>
#include <string_view>
#include <algorithm>
#include <iterator>
#include <cassert>
#include "SequenceId.h"

namespace
{
  using std::array;
  using std::size_t;
  using std::string_view;

  static constexpr string_view forbidden_chars = "DFGJMQV";
  static constexpr string_view all_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  static constexpr size_t allowed_size = all_chars.size() - forbidden_chars.size();

  constexpr bool contains(char ch, const string_view where) noexcept
  {
    return string_view::npos != where.find(ch);
  }

  template <size_t N>
  constexpr bool contains(char ch, const array<char, N> where) noexcept
  {
    return end(where) != std::find(begin(where), end(where), ch);
  }

  template <size_t N>
  constexpr array<char, N> get_allowed_chars() noexcept
  {
    std::array<char, N> allowed_chars{};
    size_t curr = 0;
    size_t i = 0;

    while (curr < N)
    {
      while (contains(all_chars[i], forbidden_chars))
      {
        ++i;
      }
      allowed_chars[curr++] = all_chars[i++];
    }

    return allowed_chars;
  }
}

// implementation class
namespace SequenceId
{
  using namespace std;
  using std::array;
  using std::exception;
  using std::string_view;
  using std::vector;

  class Id::Impl
  {
  public:
    Impl()
    {
      _groups.reserve(s_max_groups);
      _groups.emplace_back();
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

    void set(const string &id)
    {
      for (auto it = begin(id); it != end(id); ++it)
      {
        if (*it == s_delimeter)
        {
          ++it;
        }

        const auto &ch = *it;
        if (!contains(ch, s_chars))
        {
          throw invalid_argument("Incorrect format of the identifier. Char is not allowed: " + ch);
        }

        if (!contains(ch, s_digits))
        {
          throw invalid_argument("Incorrect format of the identifier. Char is not allowed: " + ch);
        }
      }
    }

    void advance()
    {
      // get rightmost grouch
      auto &last_group = _groups.back();

      // if the rightmost group is not max, advance it
      if (!last_group.is_max())
      {
        last_group.advance();
      }
      else
      {
        // otherwise, try find first non max group
        auto first_nonmax_it = find_if(
            begin(_groups),
            end(_groups),
            [&](const Group &g)
            { return g.is_max(); });

        // if found advance it
        // otherwise add new group at the back
        if (first_nonmax_it != end(_groups))
        {
          first_nonmax_it->advance();
        }
        else
        {
          _groups.emplace_back();
        }
      }
    }

    string get() const
    {
      string result;
      result.reserve(_groups.size() * 3); // reserve for 3 elements (char,  digit, delimeter) per group

      for (auto it = begin(_groups); it != end(_groups); ++it)
      {
        result.push_back(s_chars[it->char_index]);
        result.push_back(s_digits[it->digit_index]);

        if (next(it) != end(_groups))
        {
          result.push_back(s_delimeter);
        }
      }

      result.shrink_to_fit(); // space for one delimeter possibly redundant

      return result;
    }

  private:
    static constexpr array<char, allowed_size> s_chars = get_allowed_chars<allowed_size>();
    static constexpr string_view s_digits = "123456789";
    static const size_t s_last_char_index = s_chars.size() - 1;
    static const size_t s_last_digit_index = s_digits.size() - 1;
    static constexpr size_t s_max_groups = 10;
    static const char s_delimeter = '-';

    struct Group
    {
      uint8_t char_index = 0;
      uint8_t digit_index = 0;

      bool is_max() const noexcept
      {
        return char_index == s_last_char_index && digit_index == s_last_digit_index;
      }

      void advance() noexcept
      {
        // precondition: group is not max
        assert(!is_max());

        if (digit_index < s_last_digit_index)
        {
          ++digit_index;
        }
        else
        {
          ++char_index;
          digit_index = 0;
        }
      }
    };

    auto find_first_nonmax()
    {
      return find_if(
          begin(_groups),
          end(_groups),
          [&](const Group &g)
          { return g.is_max(); });
    }

    vector<Group> _groups;
  };
}

// main class
namespace SequenceId
{
  using namespace std;
  using std::array;
  using std::string_view;
  using std::vector;

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

  Id &Id::advance()
  {
    _pimpl->advance();
    return *this;
  }

  // const size_t Id::m_chars_count = getDim(all_chars) - getDim(disallowed_chars);

  string Id::get() const
  {
    return _pimpl->get();
  }
}