#ifndef MARIO_H
#define MARIO_H

#include <string>


class Mario{


   private:
       int number_of_lives;
       int number_of_coins;
       int power_level;
       int x_position, y_position;
       int kill_count;
      
   public:


       int defeat_goomba_probability, defeat_koopa_probability, defeat_boss_probability;


       // Default Constructor, passing in a logger object to get the number of lives.
       Mario(int numLives);


       // Default Deconstructor
       ~Mario();


       /* --- Getters/Accessors --- */


       // Method to return Mario's current coin count.
       int getCoins();


       // Method to return Mario's current power level.
       int getPowerLevel();


       // Method to return Mario's current life count.
       int getLives();


       // Method to return the number of enemies Mario has defeated on his current life.
       int getKillCount();


       // Method to return Mario's current X position within the Level/matrix.
       int getXPosition();


       // Method to return Mario's current Y position within the Level/matrix.
       int getYPosition();


       /* --- Setters/Mutators --- */


       // Method for setting Mario's position.
       void setPosition(int x, int y);


       // Method for increasing Mario's coin count.
       void gainCoin();


       // Method to reset Mario's current coin count.
       void resetCoins();


       // Method for increasing number of enemies defeated.
       void increaseKillCount();


       // Method for resetting Mario's kill count.
       void resetKillCount();


       // Method for increasing Mario's life count.
       void increaseLives();


       // Method for decreasing Mario's life count.
       void decreaseLives();


       // Method for increasing Mario's power level.
       void increasePowerLevel();


       // Method for decreasing Mario's power level
       void decreasePowerLevel();


       // Method for updating Mario's power level or lives based on incoming damage.
       void takeDamage(int damage_amount);


       // Methods for changing Marios x and y position.
       void moveUp(int level_dimension);


       void moveDown(int level_dimension);


       void moveRight(int level_dimension);


       void moveLeft(int level_dimension);


       /* ---Additional Methods--- */


       // Method to return whether or not Mario has lives remainning or not.
       bool hasLives();


      


};


#endif // MARIO_H

