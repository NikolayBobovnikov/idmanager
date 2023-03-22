#include <vector>
#include <array>
#include <string_view>
#include <algorithm>
#include <iterator>
#include "SequenceId.h"

namespace
{
  using std::size_t;
  using std::array;
  using std::string_view;

  static constexpr string_view forbidden_chars = "DFGJMQV";
  static constexpr string_view all_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  static constexpr size_t allowed_size = all_chars.size() - forbidden_chars.size();

  constexpr bool contains(char ch, const string_view where) noexcept {
    return string_view::npos != where.find(ch);
  }

  template <size_t N>
  constexpr array<char, N> get_allowed_chars() noexcept
  {
    std::array<char, N> allowed_chars{};
    size_t curr = 0;
    size_t i = 0;

    while (curr < N)
    {
      while (contains(all_chars[i], forbidden_chars)) {
        ++i;
      }
      allowed_chars[curr++] = all_chars[i++];
    }

    return allowed_chars;
  }
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
    static constexpr array<char, allowed_size> s_allowed_chars = get_allowed_chars<allowed_size>();
    static constexpr string_view s_digits = "123456789";
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