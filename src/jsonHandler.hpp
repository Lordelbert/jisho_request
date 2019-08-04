#pragma once
#include "Dictionnary.hpp"
#include <array>
#include <string>

class JsonHandler {
  public:
	Dictionnary parse(std::string jsonString);
};
