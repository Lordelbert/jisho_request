#pragma once
#include "Dictionnary.hpp"
#include <array>
#include <string>
#include "Dictionnary.hpp"
class JsonHandler {
  public:
	Dictionnary parse(std::string jsonString, bool& empty);
};
