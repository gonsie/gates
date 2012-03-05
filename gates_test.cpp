//Elsa Gonsiorowski
//October 7, 2011
//Rensselaer Polytechnic Institute

//Test file, using Catch [see https://github.com/philsquared/Catch]

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

//make sure all the types, variable, functions, etc. are available


//specify C (default C++)
//name the functions to be called in your tests
extern "C" {
    
}

TEST_CASE("test1", "a simple test case") {
    REQUIRE( 0 == 0 );
}
