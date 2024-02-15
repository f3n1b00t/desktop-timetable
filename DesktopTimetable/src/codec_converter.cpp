#include "codec_converter.h"

namespace codec_converter {
    std::wstring utf8_to_wstr(const std::string &utf8) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> wcu8;
        return wcu8.from_bytes(utf8);
    }

    std::string wstr_to_utf8(const std::wstring &utf16) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> wcu8;
        return wcu8.to_bytes(utf16);
    }
} // codec_converter