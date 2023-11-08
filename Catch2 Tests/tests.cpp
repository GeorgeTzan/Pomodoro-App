#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "pomodoro_mock.h"

TEST_CASE("pomodoro PauseSession Test", "[pomodoro][PauseSession]") {
    PomodoroMock mock;

    SECTION("Test unPauseSession") {
       
        
        mock.PauseSession();

        REQUIRE(mock.pause == true);
    }
}

TEST_CASE("pomodoro unPauseSession Test", "[pomodoro][unPauseSession]") {
 
    PomodoroMock mock;

    SECTION("Test PauseSession") {
        
        mock.unPauseSession();
        REQUIRE(mock.pause == false);
        
    }
    
}



