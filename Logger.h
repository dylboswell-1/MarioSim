#ifndef LOGGER_H
#define LOGGER_H


#include <string>
#include <fstream>

class Simulation;
class Mario;
class Level;

class Logger {


   private:
       std::string inputFileName;
       std::string outputFileName;


   public:
       // Values from the input file to provide other classes with
       int number_of_levels;
       int level_dimension;
       int number_of_lives;
       int coin_percentage;
       int nothing_percentage;
       int goomba_percentage;
       int koopa_percentage;
       int mushroom_percentage;


       std::ifstream inFile;
       std::ofstream outFile;


       // Values to take in from Simulation that will be output.
           // From Simulation
       int level_number;


           // From Level
       char** level;
       std::string mario_tile_interaction;
       std::string mario_next_move;


           // From Mario
       int mario_X_Position;
       int mario_Y_Position;
       int mario_Power_Level;
       int mario_lives;
       int mario_coins;
      


       // Default Constructor - Variables will be read from input file and assigned with the constructor
       Logger(std::string inputName, std::string outputName);


       // Default Deconstructor
       ~Logger();


       // Method to accumulate all values needed from the game.
       std::string getValues(Mario *mario, Level *currentLevel, int currentLevelNumber);
      
       // Method to build level map as a string for file output.
       std::string makeLevelMap(Level* currentLevel);


       // Will produce output file of map and info.
       void writeOutputAll(std::string info, std::string map);     


       // Used for particular instances where the output structure differs, like when I first spawn Mario into a level.
       void writeOutputMessage(std::string message);


       // Used for printing just a level.
       void writeOutputMap(std::string map);


};



#endif

