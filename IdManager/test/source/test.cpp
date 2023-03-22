#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "SequenceId.h"
#include <iostream>

using namespace SequenceId;

TEST_CASE("Default value")
{
    Id id;
    CHECK(id.get() == "A1");
}

TEST_CASE("Next digit (1)")
{
    Id id = "A1";
    id.next();

    CHECK(id.get() == "A2");
}

TEST_CASE("Next digit (1) + assignment")
{
    Id id = "A1";
    id = id.next();

    CHECK(id.get() == "A2");
}

TEST_CASE("Next digit (2)")
{
    Id id = "A1-A1";
    id.next();

    CHECK(id.get() == "A1-A2");
}

TEST_CASE("Update group after last digit")
{
    Id id = "A9";
    id.next();

    CHECK(id.get() == "B1");
}

TEST_CASE("Add new group (1)")
{
    Id id = "Z9";
    id.next();

    CHECK(id.get() == "A1-A1");
}

TEST_CASE("Add new group (2)")
{
    Id id = "Z9-Z9";
    id.next();

    CHECK(id.get() == "A1-A1-A1");
}

TEST_CASE("Update prev group (1)")
{
    Id id = "A1-Z9";
    id.next();

    CHECK(id.get() == "A2-A1");
}

TEST_CASE("Update prev group (2)")
{
    Id id = "Z9-A2-Z9";
    id.next();

    CHECK(id.get() == "Z9-A2-Z9");
}

TEST_CASE("Update prev group (3)")
{
    Id id = "Z9-A9-Z9";
    id.next();

    CHECK(id.get() == "Z9-B2-Z9");
}

TEST_CASE("Max id")
{
    Id id = "Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9";
    CHECK_THROWS(id.next());
}