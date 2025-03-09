#ifndef LEVEL_H
#define LEVEL_H



#include <string>

class Mario; // Forward Declaration to avoid circular dependencies
class Logger;

class Level {

   private:
       int level_dimension;
       int coins_percent, nothing_percent, goombas_percent, koopas_percent, mushrooms_percent;
       bool is_final_level;
       bool is_level_done;
       char** level;
       std::string mario_next_move;
       std::string tile_interaction;
      
       // Method to select a random int from a provided range.
       int getRandomIntInRange(int min, int max);


       // Method to select which game object to place a an individual tile in the level.
       char chooseRandObject(int coins_percent, int nothing_percent, int goombas_percent, int koopas_percent);
  
   public:
       // Default Constructor
       Level(Mario *inMario, Logger *inLogger, bool isFinalLevel);


       // Default Deconstructor
       ~Level();


       // Method to spawn mario, or the 'H' char in the level.
       void spawnMario(Mario *inMario);


       // Method to return current level as a 2D Array/Matrix
       char** getLevel();


       std::string getNextMove();


       std::string getTileInteraction();


       // Setting the selected tile to be nothing.
       void clearLevelTile(int row, int col);


       // Method to retrieve the char at a particular position.
       char getLevelTile(int row, int col);


       // Method to retrieve the current level's dimension.
       int getLevelDimension();


       // Method to set the char at a particular position.
       void setLevelTile(int row, int col, char newChar);


       // Methods to move Mario around the world
       void moveMarioUp(Mario *inMario, Logger *inLogger);
       void moveMarioDown(Mario *inMario, Logger *inLogger);
       void moveMarioLeft(Mario *inMario, Logger *inLogger);
       void moveMarioRight(Mario *inMario, Logger *inLogger);
       void moveMarioRandomly(Mario *inMario, Logger *inLogger);


       // Method that will handle Mario encountering an enemy
       bool fightEnemy(char enemy, Mario *inMario);


       // Method for if Mario loses a fight to a goomba or koopa.
       void undoMove(Mario *inMario, char lastMove, Logger *inLogger);


       // Method that will handle Mario's interactions with the world/level.
       void interactWithTile(Mario *inMario, char tile, char moveSelection, Logger *inLogger);

       // Method will returm the is_level_not_done member variable.
       bool isLevelDone();

       bool isFinalLevel();
      


};






#endif // LEVEL_H

