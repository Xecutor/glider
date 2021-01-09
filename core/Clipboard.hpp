#pragma once

#include <string>

namespace glider {

void copyToClipboard(const char* utf8text);
std::string pasteFromClipboard();

}  // namespace glider
