// IdManager.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <string>
#include "IId.h"

namespace {
  /*
#include <array>

  using ResultT = int;
  constexpr ResultT f(int i)
  {
    return i * 2;
  }

  constexpr auto LUT = []
  {
    constexpr auto LUT_Size = 1024;
    std::array<ResultT, LUT_Size> arr = {};

    for (int i = 0; i < LUT_Size; ++i)
    {
      arr[i] = f(i);
    }

    return arr;
  }();

  static_assert(LUT[100] == 200);
  */
}

namespace SequenceId {
  using std::string;

  class SequenceId {
  public:
    SequenceId(); // default
    SequenceId(const string& id); // implicit

    virtual SequenceId& operator=(SequenceId&) = 0;

    virtual SequenceId& operator++() = 0;

  private:
    std::string _id;
  };

}
