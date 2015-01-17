#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "game.cpp"
#include "System.cpp"
#include "menu.cpp"

#include <time.h>

int main()
{
    srand(time(0));
                                        //1086, 768
    sf::RenderWindow window(sf::VideoMode(1086, 768), "Dirty Spatula in Vegas", sf::Style::Close);

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    System system;

    do
    {
        if(!game(window,system,menu(window)))
            return 0;

    } while(system.inPlay());

    std::cin.ignore(1000);


    return 0;
}

/*
    TODO BUG LIST:
    1. TOWER KILLING ENEMIES ON RANGE LINE DOES NOT FIRE ROCKET OUT DUE TO IT PUTTING THE TARGET TO NULL
        - MAYBE ONLY DAMAGE ENEMY WHEN THE BULLET REACHES THE TARGET
    2. TOWER GETS PLACED IN TOP LEFT OF THE SCREEN IF THE CURSOR IS USED TO CLICK ANOTHER WINDOW

*/


/*
    TODO FEATURE LIST:

    (PRODUCE 2 NEW MUSIC TRACKS PER VERSION)

    TO DO FOR ALPHA-3
    1. TOWER THAT SLOWS ENEMIES drawn, logic to do, tower choice to do
    2. 3 MORE ENEMIES one to draw
    3. RANDOM CHANCE (5% OR 10%) FOR A TOWER TO MISS THE TARGET done
  3.5. TEXT TO SHOW THAT THE TOWER MISSED
    4. HEALTH ABOVE EACH ENEMY need to compile
    5. OPTIONS MENU (VOLUMES, SMOOTHING,FULLSCREEN,DIFFICULTY-FOR FUTURE)

    TO DO FOR ALPHA-4
    1. ENEMIES SPAWN IN BOTH LANES
    2. CHANGE TOWER AI 'TARGETFIRST' TO ALSO ALLOW TOWERS TO KILL ENEMIES IN SECOND LANE
    3. SOUND EFFECTS FOR TOWER SHOOTING AND EMENY KILLING
    4. TRY AND GET ENEMIES TO MOVE DEPENDANT ON FRAMERATE SO IT'S NOT DEPENDANT ON 60FPS

    TO DO FOR ALPHA-5
    1. BALANCE THE GAME
    2. IMPLEMENT WEAKEST AND STRONGEST FIRST TOWER AI
    3. ABLE TO CHANGE BETWEEN THE DIFFERENT TOWER AI
    4. 2 NEW TOWERS

    TO DO FOR ALPHA-6
    1. TOWER EXPERIENCE FROM ENEMIES
    2. TOWERS DO DIFFERENT DAMAGE TO SPECIFIC ENEMIES
    3. TOWER UPGRADE BUTTON WHEN ENOUGH EXPERIENCE TO DO SO
    4. 2 NEW TOWERS
*/
