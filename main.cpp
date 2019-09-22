#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include "catch.hpp"
#include "roman.h"
#include <string>
#include <algorithm>

TEST_CASE( "Property testing" )
{
    GIVEN("Any number from 1") {
        
        auto value = GENERATE(take(100, random(1, 10000)));
        auto roman = to_roman(value);
 
        THEN("There are never more than three consecutive decimals except for 1000") {
            REQUIRE( std::search_n(roman.begin(), roman.end(), 4, 'I') == roman.end());
            REQUIRE( std::search_n(roman.begin(), roman.end(), 4, 'X') == roman.end());
            REQUIRE( std::search_n(roman.begin(), roman.end(), 4, 'C') == roman.end());
        }
        
        THEN("There are never more than one half-decimal") {
            REQUIRE( std::search_n(roman.begin(), roman.end(), 2, 'V') == roman.end());
            REQUIRE( std::search_n(roman.begin(), roman.end(), 2, 'L') == roman.end());
            REQUIRE( std::search_n(roman.begin(), roman.end(), 2, 'D') == roman.end());
        }
    }
}

TEST_CASE( "Life the universe and everything", "[hhgttg]" )
{
    SECTION("Test") {
    REQUIRE( to_roman(1) == "I" );
    REQUIRE( to_roman(2) == "II" );
    REQUIRE( to_roman(3) == "III" );
    REQUIRE( to_roman(4) == "IV" );
    REQUIRE( to_roman(5) == "V" );
    REQUIRE( to_roman(6) == "VI" );
    REQUIRE( to_roman(7) == "VII" );
    REQUIRE( to_roman(8) == "VIII" );
    REQUIRE( to_roman(9) == "IX" );

    REQUIRE( to_roman(10) == "X" );
    REQUIRE( to_roman(20) == "XX" );
    REQUIRE( to_roman(30) == "XXX" );
    REQUIRE( to_roman(40) == "XL" );
    REQUIRE( to_roman(50) == "L" );
    REQUIRE( to_roman(60) == "LX" );
    REQUIRE( to_roman(70) == "LXX" );
    REQUIRE( to_roman(80) == "LXXX" );
    REQUIRE( to_roman(90) == "XC" );
    
    REQUIRE( to_roman(100) ==    "C" );
    REQUIRE( to_roman(200) ==   "CC" );
    REQUIRE( to_roman(300) ==  "CCC" );
    REQUIRE( to_roman(400) ==   "CD" );
    REQUIRE( to_roman(500) ==    "D" );
    REQUIRE( to_roman(600) ==   "DC" );
    REQUIRE( to_roman(700) ==  "DCC" );
    REQUIRE( to_roman(800) == "DCCC" );
    REQUIRE( to_roman(900) ==   "CM" );

    REQUIRE( to_roman(1000) == "M" );
    REQUIRE( to_roman(2000) == "MM" );
    REQUIRE( to_roman(3000) == "MMM" );
    REQUIRE( to_roman(4000) == "MMMM" );
    REQUIRE( to_roman(5000) == "MMMMM" );

    REQUIRE( to_roman(1990) == "MCMXC" );
    REQUIRE( to_roman(2008) == "MMVIII" );
    REQUIRE( to_roman(99) == "XCIX" );
    REQUIRE( to_roman(47) == "XLVII" );
    REQUIRE( to_roman(42) == "XLII" );
    }

#ifdef CATCH_CONFIG_ENABLE_BENCHMARKING
    SECTION("Benchmark") {
        BENCHMARK("1 digit") {
            return to_roman(1);
        };

        BENCHMARK("long") {
            return to_roman(1973);
        };

        BENCHMARK("full") {
            return to_roman(1888);
        };

        BENCHMARK("extreme") {
            return to_roman(5573);
        };
    }
#endif
}
