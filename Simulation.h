#ifndef SIMULATION_H
#define SIMULATION_H


class Level;
class Mario;
class Logger;


#include <string>


class Simulation {


   public:
       int number_of_levels;
       int currentLevel;
       Level** world;
       Logger *sim_logger;
       Mario *sim_mario;


       // Default Constructor
       Simulation(Mario *mario, Logger *logger);


       // Default Deconstructor
       ~Simulation();


       // Will play the whole game, and output whether or not Mario beats the game.
       void playGame();


};




#endif // SIMULATION_H

