#pragma once

#include <string>
#include <codecvt>
#include <locale>

namespace codec_converter {
    std::wstring utf8_to_wstr(const std::string& utf8);

    std::string wstr_to_utf8(const std::wstring& utf16);

}
