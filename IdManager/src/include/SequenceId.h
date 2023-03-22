// IdManager.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <string>
#include <memory>
#include "IId.h"

namespace SequenceId
{
  using std::array;
  using std::string;
  using std::unique_ptr;

  class Id
  {
  public:
    Id();               // default
    Id(const string &); // implicit
    Id(const char *);   // implicit
    ~Id();              // need for pimpl, default in cpp

    Id(const Id &);
    Id &operator=(const Id &);
    Id(Id &&) = default;
    Id &operator=(Id &&) = default;

    Id &set(const string &);
    Id &next();
    string get() const;

  private:
    // static const size_t m_chars_count;
    // static const array<char, m_chars_count> m_allowed_chars;
    class Impl;
    unique_ptr<Impl> _pimpl;
  };
}
