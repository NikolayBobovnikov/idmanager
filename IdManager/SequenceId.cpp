// IdManager.cpp : Defines the entry point for the application.
//

#include <string>
#include "SequenceId.h"

namespace {
  using std::string_view;

  constexpr string_view  DISALLOWED_CHARS = "DFGJMQV";
  constexpr string_view  ALL_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  constexpr string_view  DIGITS = "123456789";
}

namespace SequenceId {
  SequenceId::SequenceId()
    : _id("A1")
  {
  }

  SequenceId::SequenceId(const string& id)
    : _id(id)
  {
  }

}