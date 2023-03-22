#pragma once

#include <string>
#include <memory>

namespace SequenceId
{
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
    class Impl;
    unique_ptr<Impl> _pimpl;
  };
}
