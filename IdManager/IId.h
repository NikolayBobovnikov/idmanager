#pragma once

#include <string>

struct IId {
  virtual IId& operator=(IId&) = 0;
  virtual IId& operator++() = 0;
};