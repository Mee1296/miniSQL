#pragma once
#include "storage/schema.h"
#include <string>

void writeSchema(const Schema& schema, const std::string& path);
Schema readSchema(const std::string& path);
