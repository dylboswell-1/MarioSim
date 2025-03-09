#include "Mario.h"

#include <iostream>
#include <string>


// Default Constructor
Mario::Mario(int numLives){
   number_of_lives = numLives;
   number_of_coins = 0;
   power_level = 0;
   x_position = -1; // Setting the default value of x_position/y_positinon to -1 to indicate that Mario has yet to be placed in the Level.
   y_position = -1;
   defeat_goomba_probability = 80;
   defeat_koopa_probability = 65;
   defeat_boss_probability = 50;
   kill_count = 0;
   std::cout << "Mario has been constructed." << std::endl;
}


// Default Deconstructor
Mario::~Mario(){}


/* --- Getters/Accessors --- */
int Mario::getCoins(){
   return number_of_coins;
}

int Mario::getPowerLevel(){
   return power_level;
}

int Mario::getKillCount(){
   return kill_count;
}

int Mario::getLives(){
   return number_of_lives;
}

int Mario::getXPosition(){
   return x_position;
}


int Mario::getYPosition(){
   return y_position;
}


/* --- Setters/Mutators --- */


void Mario::setPosition(int x, int y){
   x_position = x;
   y_position = y;
}


void Mario::resetCoins(){
   number_of_coins = 0;
}


void Mario::gainCoin(){
   number_of_coins = number_of_coins + 1;
   // If Mario's obtains 20 coins, increase his life count by 1 and reset his coin counter.
   if (number_of_coins == 20){
      increaseLives();
      resetCoins();
   }
}


void Mario::increaseLives(){
   number_of_lives = number_of_lives + 1;
}


// If Mario is ever killed, reset his power level, number of coins, and number of enemies defeated.
void Mario::decreaseLives(){
   number_of_lives = number_of_lives - 1;
   power_level = 0;
   resetCoins();
   resetKillCount();
}


void Mario::resetKillCount(){
   kill_count = 0;
}


void Mario::increaseKillCount(){
   kill_count = kill_count + 1;
   if(kill_count == 7){
      increaseLives();
      resetKillCount();
   }
}

void Mario::increasePowerLevel(){
   if(power_level <2){
      power_level = power_level + 1;
   } 
}


void Mario::decreasePowerLevel(){
   power_level = power_level - 1;
}


void Mario::takeDamage(int damage_amount){
   if(power_level - damage_amount < 0){
      decreaseLives();
   }
   else{
      power_level = power_level - damage_amount;
   }
}


/* --- Additional Methods --- */
bool Mario::hasLives(){
   return (number_of_lives > 0);
}

void Mario::moveUp(int level_dimension){
   if(x_position == 0){
      x_position = level_dimension - 1;
   }
   else {
      x_position = x_position - 1;
   }
}

void Mario::moveDown(int level_dimension){
   if(x_position == level_dimension - 1){
      x_position = 0;
   }
   else {
      x_position = x_position + 1;
   }
}

void Mario::moveRight(int level_dimension){
   if(y_position == level_dimension - 1){
      y_position = 0;
   }
   else {
      y_position = y_position + 1;
   }
}

void Mario::moveLeft(int level_dimension){
   if(y_position == 0){
      y_position = level_dimension - 1;
   }
   else {
      y_position = y_position - 1;
   }
}