#include "roman.h"
#include <cinttypes>
#include <string>
#include <string_view>

#define IMPLEMENTATION 1

#if IMPLEMENTATION == 1

constexpr const alignas(64) std::string_view romand_decades[3][10]{
    {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
    {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
    {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
};

std::string to_roman(unsigned int value) noexcept
{
    if (value == 0)
        return "nulla";

    std::string s;

    auto milla = value / 1000;
    s.append(milla, 'M');

    value %= 1000;
    auto centum = value / 100;
    if (centum != 0)
        s += romand_decades[2][centum];

    value %= 100;
    auto decem = value / 10;
    if (decem != 0)
        s += romand_decades[1][decem];

    value %= 10;
    if (value != 0)
        s += romand_decades[0][value];

    return s;
}

#elif IMPLEMENTATION == 2

std::string to_roman(unsigned int value) noexcept
{
    if (value == 0)
        return "nulla";

    std::string s;

    auto milla = value / 1000;
    s.append(milla, 'M');

    switch (value % 1000 / 100) {
        case 1: s += std::string_view{"C"}; break;
        case 2: s += std::string_view{"CC"}; break;
        case 3: s += std::string_view{"CCC"}; break;
        case 4: s += std::string_view{"CD"}; break;
        case 5: s += std::string_view{"D"}; break;
        case 6: s += std::string_view{"DC"}; break;
        case 7: s += std::string_view{"DCC"}; break;
        case 8: s += std::string_view{"DCCC"}; break;
        case 9: s += std::string_view{"CM"}; break;
    }

    switch (value % 100 / 10) {
        case 1: s += std::string_view{"X"}; break;
        case 2: s += std::string_view{"XX"}; break;
        case 3: s += std::string_view{"XXX"}; break;
        case 4: s += std::string_view{"XL"}; break;
        case 5: s += std::string_view{"L"}; break;
        case 6: s += std::string_view{"LX"}; break;
        case 7: s += std::string_view{"LXX"}; break;
        case 8: s += std::string_view{"LXXX"}; break;
        case 9: s += std::string_view{"XC"}; break;
    }

    switch (value % 10) {
        case 1: s += std::string_view{"I"}; break;
        case 2: s += std::string_view{"II"}; break;
        case 3: s += std::string_view{"III"}; break;
        case 4: s += std::string_view{"IV"}; break;
        case 5: s += std::string_view{"V"}; break;
        case 6: s += std::string_view{"VI"}; break;
        case 7: s += std::string_view{"VII"}; break;
        case 8: s += std::string_view{"VIII"}; break;
        case 9: s += std::string_view{"IX"}; break;
    }

    return s;
}

#elif IMPLEMENTATION == 3

static alignas(64) constexpr char kRomanDigits[]{"IVIIIXLXXXCDCCCM"};

static alignas(64) constexpr std::pair<uint8_t, uint8_t> kRomanGroupsIndex[]{
    {0, 0},  {0, 1},  {2, 2},  {2, 3},  {0, 2},  {1, 1},  {1, 2},  {1, 3},
    {1, 4},  {4, 2},  {0, 0},  {7, 1},  {7, 2},  {7, 3},  {5, 2},  {6, 1},
    {6, 2},  {6, 3},  {6, 4},  {9, 2},  {0, 0},  {12, 1}, {12, 2}, {12, 3},
    {10, 2}, {11, 1}, {11, 2}, {11, 3}, {11, 4}, {14, 2},
};

std::string to_roman(unsigned int value) noexcept
{
    if (value == 0)
        return "nulla";

    std::string s;

    auto milla = value / 1000;
    if (milla > 16)
        s.reserve(milla + 3 * 4);

    s.append(milla, 'M');

    value %= 1000;
    auto centum = value / 100;
    if (centum != 0) {
        auto p = kRomanGroupsIndex[20 + centum];
        s.append(&kRomanDigits[p.first], p.second);
    }

    value %= 100;
    auto decem = value / 10;
    if (decem != 0) {
        auto p = kRomanGroupsIndex[10 + decem];
        s.append(&kRomanDigits[p.first], p.second);
    }

    value %= 10;
    if (value != 0) {
        auto p = kRomanGroupsIndex[value];
        s.append(&kRomanDigits[p.first], p.second);
    }

    return s;
}


#endif
