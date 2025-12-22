#pragma once
#include "../row/user.h"
#include <vector>

std::vector<char> serializeUser(const User& u);
User deserializeUser(const char* data);
