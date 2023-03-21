#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "SequenceId.h"
#include <iostream>

using namespace SequenceId;

TEST_CASE("Default value") {
  Id id;
  CHECK(static_cast<string>(id) == "A1");
}