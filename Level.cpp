#include "Level.h"
#include "Mario.h"
#include "Logger.h"


#include <random>
#include <iostream>


// Default Constructor
Level::Level(Mario *inMario, Logger *inLogger, bool isFinalLevel) {
    // Assignning member variables
    level_dimension = inLogger->level_dimension;
    coins_percent = inLogger->coin_percentage;
    nothing_percent = inLogger->nothing_percentage;
    goombas_percent = inLogger->goomba_percentage;
    koopas_percent = inLogger->koopa_percentage;
    mushrooms_percent = inLogger->mushroom_percentage;
    is_final_level = isFinalLevel;
    is_level_done = false;

    std::cout << "Initializing level matrix...\n"<< std::endl;

    // Allocating memory for level matrix
    level = new char*[level_dimension];

    // Debug Message
    if (level == nullptr) {
        std::cerr << "ERROR: Failed to allocate memory for `level[][]`.\n";
        return;
    }

    for (int i = 0; i < level_dimension; i++) {
        level[i] = new char[level_dimension];

        // Debug Message
        if (level[i] == nullptr) {
            std::cerr << "ERROR: Failed to allocate memory for `level[" << i << "]`.\n";
            return;
        }

        for (int j = 0; j < level_dimension; j++) {
            level[i][j] = 'x';  // Fill with empty spaces by default
        }
    }

    std::cout << "Level matrix successfully initialized.\n"<< std::endl;

    // Generate random positions for the boss and warp pipe
    int boss_random_row = getRandomIntInRange(0, level_dimension - 1);
    int boss_random_col = getRandomIntInRange(0, level_dimension - 1);
    int pipe_random_row, pipe_random_col;

    // Place the boss
    level[boss_random_row][boss_random_col] = 'b';
    std::cout << "Boss placed at: (" << boss_random_row << ", " << boss_random_col << ")\n"<< std::endl;

    // Place the warp pipe (only if it's not the final level) and ensure it doesn't overlap with the boss
    if (!is_final_level) {
        do {
            pipe_random_row = getRandomIntInRange(0, level_dimension - 1);
            pipe_random_col = getRandomIntInRange(0, level_dimension - 1);
        } while (pipe_random_row == boss_random_row && pipe_random_col == boss_random_col);

        level[pipe_random_row][pipe_random_col] = 'w';
        std::cout << "Warp pipe placed at: (" << pipe_random_row << ", " << pipe_random_col << ")\n"<< std::endl;
    }

    // Fill the rest of the level with game objects
    for (int i = 0; i < level_dimension; i++) {
        for (int j = 0; j < level_dimension; j++) {
            if (level[i][j] != 'w' && level[i][j] != 'b') {  // Ensure we don't overwrite boss or warp pipe
                level[i][j] = chooseRandObject(coins_percent, nothing_percent, goombas_percent, koopas_percent);
            }
        }
    }

    std::cout << "Level successfully generated.\n"<< std::endl;
}

// Default Deconstructor
Level::~Level() {
    std::cout << "Destroying Level Object...\n"<< std::endl;

    if (level == nullptr) {
        std::cerr << "WARNING: `level[][]` is already NULL before deletion!\n";
        return;
    }

    // Delete each row safely
    for (int i = 0; i < level_dimension; i++) {
        if (level[i] == nullptr) {
            std::cerr << "WARNING: `level[" << i << "]` is already NULL before deletion!\n";
        } else {
            delete[] level[i];
        }
    }

    // Delete the array of pointers
    delete[] level;
    level = nullptr;

    std::cout << "Level object successfully deleted.\n"<< std::endl;
}

// Accessors
char** Level::getLevel(){
   return level;
}
std::string Level::getNextMove(){
   return mario_next_move;
}
std::string Level::getTileInteraction(){
   return tile_interaction;
}
bool Level::isFinalLevel() {
    return is_final_level;
}
// Method to place Mario into level
void Level::spawnMario(Mario *inMario) {
    int randRow, randCol;

    // Using a do-while loop because I check wheter or not the locations are overlapping at least once
    do {
        randRow = getRandomIntInRange(0, level_dimension - 1);
        randCol = getRandomIntInRange(0, level_dimension - 1);
    } while (level[randRow][randCol] == 'x'); // checking to see if it's an empty space

    // Place Mario at the selected position
    level[randRow][randCol] = 'H';
    inMario->setPosition(randRow, randCol);

    std::cout << "Mario spawned at: (" << randRow << ", " << randCol << ")\n"<< std::endl;
}

// Method to select a random int from a provided range.
int Level::getRandomIntInRange(int min, int max){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// Method to select which game object to place a an individual tile in the level based on provided percentages.
char Level::chooseRandObject(int coins_percent, int nothing_percent, int goombas_percent, int koopas_percent){
   int choice = getRandomIntInRange(1,100);
   if(choice <= coins_percent){
       return 'c';
   }
   else if(choice <= coins_percent + nothing_percent){
       return 'x';
   }
   else if(choice <= coins_percent + nothing_percent + goombas_percent){
       return 'g';
   }
   else if(choice <= coins_percent + nothing_percent + goombas_percent + koopas_percent){
       return 'k';
   }
   else{
       return 'm';
   }
}

// Setting the selected tile to be nothing. For when mario defeats an enemy, or moves off of a nothing tile.
void Level::clearLevelTile(int row, int col){
   level[row][col] = 'x';
}

// Method to retrieve the char at a particular position.
char Level::getLevelTile(int row, int col) {

    // Error messages for if I try to improperly access a tile out of range
    if (level == nullptr) {
        std::cerr << "ERROR: level[][] is NULL in getLevelTile()!\n";
        return 'E';
    }
    if (row < 0 || row >= level_dimension || col < 0 || col >= level_dimension) {
        std::cerr << "ERROR: Attempted to access invalid tile at (" << row << ", " << col << ")\n";
        return 'X';
    }

    std::cout << "getLevelTile(): Getting tile at (" << row << ", " << col << ") -> "  << level[row][col] << "\n"<< std::endl;
    return level[row][col];
}

// Method to set level tile.
void Level::setLevelTile(int row, int col, char newChar) {

    // Error messages for if I try to improperly access a tile out of range
    if (row < 0 || row >= level_dimension || col < 0 || col >= level_dimension) {
        std::cerr << "ERROR: Attempted to write outside level bounds at ("  << row << ", " << col << ")\n";
    }
    else{
        level[row][col] = newChar;
        std::cout << "Tile at (" << row << ", " << col << ") set to '" << newChar << "'\n"<< std::endl;
    }
}

// Methods that handles Mario's movement in the level.
void Level::moveMarioUp(Mario *inMario, Logger *inLogger) {
    std::cout << "Before moving up: (" << inMario->getXPosition() << ", " << inMario->getYPosition() << ")\n"<< std::endl;

    int oldX = inMario->getXPosition();
    int oldY = inMario->getYPosition();

    // Debug Message
    if (oldX < 0 || oldX >= level_dimension || oldY < 0 || oldY >= level_dimension) {
        std::cerr << "ERROR: Mario is at an invalid position before moving up! (" << oldX << ", " << oldY << ")\n";
        exit(1); // Kicks me out of method if this issue occurs
    }

    clearLevelTile(oldX, oldY);  // Clear Mario's current tile

    // Move Mario up
    inMario->moveUp(level_dimension);

    int newX = inMario->getXPosition();
    int newY = inMario->getYPosition();

    // Debug Message - Making sure mario is in an acceptable range
    if (newX < 0 || newX >= level_dimension || newY < 0 || newY >= level_dimension) {
        std::cerr << "ERROR: Mario moved to an invalid position! (" << newX << ", " << newY << ")\n";
        exit(1); // Kicks me out of method if this issue occurs
    }

    interactWithTile(inMario, getLevelTile(newX, newY), 'U',inLogger);

    std::cout << "After moving up: (" << newX << ", " << newY << ")\n"<< std::endl;
}

void Level::moveMarioDown(Mario *inMario, Logger *inLogger) {
    std::cout << "Before moving down: (" << inMario->getXPosition() << ", " << inMario->getYPosition() << ")\n"<< std::endl;

    int oldX = inMario->getXPosition();
    int oldY = inMario->getYPosition();

    // Debug 
    if (oldX < 0 || oldX >= level_dimension || oldY < 0 || oldY >= level_dimension) {
        std::cerr << "ERROR: Mario is at an invalid position before moving down! (" << oldX << ", " << oldY << ")\n";
        exit(1); // Kicks me out of method if this issue occurs
    }

    clearLevelTile(oldX, oldY);  // Clear Mario's current tile

    // Move Mario down
    inMario->moveDown(level_dimension);

    int newX = inMario->getXPosition();
    int newY = inMario->getYPosition();

    // Debug
    if (newX < 0 || newX >= level_dimension || newY < 0 || newY >= level_dimension) {
        std::cerr << "ERROR: Mario moved to an invalid position! (" << newX << ", " << newY << ")\n";
        exit(1); // Kicks me out of method if this issue occurs
    }

    interactWithTile(inMario, getLevelTile(newX, newY), 'D',inLogger);

    std::cout << "After moving down: (" << newX << ", " << newY << ")\n"<< std::endl;
}

void Level::moveMarioLeft(Mario *inMario, Logger *inLogger) {
    std::cout << "Before moving left: (" << inMario->getXPosition() << ", " << inMario->getYPosition() << ")\n"<< std::endl;

    int oldX = inMario->getXPosition();
    int oldY = inMario->getYPosition();

    // Debug
    if (oldX < 0 || oldX >= level_dimension || oldY < 0 || oldY >= level_dimension) {
        std::cerr << "ERROR: Mario is at an invalid position before moving left! (" << oldX << ", " << oldY << ")\n";
        exit(1); // Kicks me out of method if this issue occurs
    }

    clearLevelTile(oldX, oldY);  // Clear Mario's current tile

    // Move Mario left
    inMario->moveLeft(level_dimension);

    int newX = inMario->getXPosition();
    int newY = inMario->getYPosition();

    // Debug
    if (newX < 0 || newX >= level_dimension || newY < 0 || newY >= level_dimension) {
        std::cerr << "ERROR: Mario moved to an invalid position! (" << newX << ", " << newY << ")\n";
        exit(1); // Kicks me out of method if this issue occurs
    }

    interactWithTile(inMario, getLevelTile(newX, newY), 'L',inLogger);

    std::cout << "After moving left: (" << newX << ", " << newY << ")\n"<< std::endl;
}

void Level::moveMarioRight(Mario *inMario, Logger *inLogger) {
    std::cout << "Before moving right: (" << inMario->getXPosition() << ", " << inMario->getYPosition() << ")\n"<< std::endl;

    int oldX = inMario->getXPosition();
    int oldY = inMario->getYPosition();

    // Debug
    if (oldX < 0 || oldX >= level_dimension || oldY < 0 || oldY >= level_dimension) {
        std::cerr << "ERROR: Mario is at an invalid position before moving right! (" << oldX << ", " << oldY << ")\n";
        exit(1);// Kicks me out of method if this issue occurs
    }

    clearLevelTile(oldX, oldY);  // Clearing Mario's current tile

    // Move Mario right
    inMario->moveRight(level_dimension);

    int newX = inMario->getXPosition();
    int newY = inMario->getYPosition();

    // Debug
    if (newX < 0 || newX >= level_dimension || newY < 0 || newY >= level_dimension) {
        std::cerr << "ERROR: Mario moved to an invalid position! (" << newX << ", " << newY << ")\n";
        exit(1); // Kicks me out of method if this issue occurs
    }

    interactWithTile(inMario, getLevelTile(newX, newY), 'R',inLogger);

    std::cout << "After moving right: (" << newX << ", " << newY << ")\n"<< std::endl;
}


void Level::moveMarioRandomly(Mario *inMario, Logger *inLogger) {
    std::cout << "Mario's current position: (" << inMario->getXPosition() << ", " << inMario->getYPosition() << ")" << std::endl;

    int randomSelection = getRandomIntInRange(1, 4);

    std::cout << "Random move choice: " << randomSelection << " -- Key: 1 = Up, 2 = Down, 3 = Left, 4 = Right" << std::endl;

    switch (randomSelection) {
        case 1:
            std::cout << "Moving Up" << std::endl;
            inLogger->writeOutputMessage("Mario moves up. \n");
            moveMarioUp(inMario, inLogger);
            break;
        case 2:
            std::cout << "Moving Down" << std::endl;
            inLogger->writeOutputMessage("Mario moves down. \n");
            moveMarioDown(inMario, inLogger);
            break;
        case 3:
            std::cout << "Moving Left" << std::endl;
            inLogger->writeOutputMessage("Mario moves left. \n");
            moveMarioLeft(inMario, inLogger);
            break;
        case 4:
            std::cout << "Moving Right" << std::endl;
            inLogger->writeOutputMessage("Mario moves right. \n");
            moveMarioRight(inMario, inLogger);
            break;
    }

    int mario_X_Position = inMario->getXPosition(); // From Mario
    int mario_Y_Position = inMario->getYPosition();
    std::string string_mario_X_Position = std::to_string(mario_X_Position);
    std::string string_mario_Y_Position = std::to_string(mario_Y_Position);

    inLogger->writeOutputMessage("Mario is now at (" + string_mario_X_Position + "," + string_mario_Y_Position + ")\n");

    std::cout << "New position after move: (" << inMario->getXPosition() << ", " << inMario->getYPosition() << ")" << std::endl;
}

// Method to handle Mario's interactions with the level. Also moves the H char around the char map.
void Level::interactWithTile(Mario *inMario, char tile, char moveSelection, Logger *inLogger) {
    std::cout << "Mario landed on tile '" << tile << "' at (" << inMario->getXPosition() << ", " << inMario->getYPosition() << ")\n"<< std::endl;

    switch(tile) {
        case 'c':  // Coin
            inMario->gainCoin();
            setLevelTile(inMario->getXPosition(), inMario->getYPosition(), 'H');
            std::cout << "Mario picked up a coin.\n"<< std::endl;
            inLogger->writeOutputMessage("Mario picked up a coin.\n");
            break;

        case 'm':  // Mushroom
            std::cout << "Mario landed on a mushroom at (" << inMario->getXPosition() << ", " << inMario->getYPosition() << ")\n"<< std::endl;

            inMario->increasePowerLevel();  // Increase power level
            setLevelTile(inMario->getXPosition(), inMario->getYPosition(), 'H');  // Replace mushroom with Mario
            inLogger->writeOutputMessage("Mario ate a mushroom.\n");
            std::cout << "Mario ate a mushroom. New power level: " << inMario->getPowerLevel() << "\n"<< std::endl;
            break;

        case 'w':  // Warp pipe 
            inLogger->writeOutputMessage("Taking Warp Pipe");
            std::cout << "Mario found the warp pipe! Level complete.\n"<< std::endl;
            is_level_done = true;
            break;

        case 'x':  // Empty tile
            setLevelTile(inMario->getXPosition(), inMario->getYPosition(), 'H');
            inLogger->writeOutputMessage("Mario moved to an empty tile.\n");
            std::cout << "Mario moved to an empty tile.\n"<< std::endl;
            break;

        case 'g':  // Goomba
            if (fightEnemy(tile, inMario)) {
                setLevelTile(inMario->getXPosition(), inMario->getYPosition(), 'H');
                inMario->increaseKillCount();
                inLogger->writeOutputMessage("Mario beat the goomba.\n");
                std::cout << "Mario defeated the Goomba!\n"<< std::endl;
            } else {
                inMario->takeDamage(1);
                inLogger->writeOutputMessage("Mario lost to goomba.\n");
                undoMove(inMario, moveSelection,inLogger);
                std::cout << "Mario lost to the Goomba and moved back.\n"<< std::endl;
            }
            break;

        case 'k':  // Koopa
            if (fightEnemy(tile, inMario)) {
                setLevelTile(inMario->getXPosition(), inMario->getYPosition(), 'H');
                inMario->increaseKillCount();
                inLogger->writeOutputMessage("Mario beat the koopa.\n");
                std::cout << "Mario defeated the Koopa!\n"<< std::endl;
            } else {
                inMario->takeDamage(1);
                inLogger->writeOutputMessage("Mario lost to koopa.\n");
                undoMove(inMario, moveSelection,inLogger);
                std::cout << "Mario lost to the Koopa and moved back.\n"<< std::endl;
            }
            break;

        case 'b':  // Boss
            if (fightEnemy(tile, inMario)) {
                is_level_done = true;
                setLevelTile(inMario->getXPosition(), inMario->getYPosition(), 'H');
                inLogger->writeOutputMessage("Mario defeated the Boss! Level complete.\n");
                break;
                inMario->increaseKillCount();
                std::cout << "Mario defeated the Boss! Level complete.\n"<< std::endl;
            } else {
                inMario->takeDamage(2);
                inLogger->writeOutputMessage("Mario lost to the Boss.\n");
                undoMove(inMario, moveSelection,inLogger);
                std::cout << "Mario lost to the Boss and moved back.\n"<< std::endl;
            }
            break;
    }
}

// If Mario loses a fight, move him to where he was before he attacked an enemy.
void Level::undoMove(Mario *inMario, char lastMove, Logger *inLogger){
   switch(lastMove){
       // Doing the opposite movement from what was provided.
       case 'U':
           inMario->moveDown(level_dimension);
           interactWithTile(inMario, getLevelTile(inMario->getXPosition(), inMario->getYPosition()),'x',inLogger);
           // Move selection doesn't matter because he should be returning to an empty 'x' tile in which case nothing happens.
           break;
       case 'D':
           inMario->moveUp(level_dimension);
           interactWithTile(inMario, getLevelTile(inMario->getXPosition(), inMario->getYPosition()),'x',inLogger);
           // Move selection doesn't matter because he should be returning to an empty 'x' tile in which case nothing happens.
           break;
       case 'L':
           inMario->moveRight(level_dimension);
           interactWithTile(inMario, getLevelTile(inMario->getXPosition(),inMario->getYPosition()),'x',inLogger);
           // Move selection doesn't matter because he should be returning to an empty 'x' tile in which case nothing happens.
           break;
       case 'R':
           inMario->moveLeft(level_dimension);
           interactWithTile(inMario, getLevelTile(inMario->getXPosition(),inMario->getYPosition()),'x',inLogger);
           // Move selection doesn't matter because he should be returning to an empty 'x' tile in which case nothing happens.
           break;
   }
}

// Using provided probabilities to determine fight outcome. True = win, False = lose.
bool Level::fightEnemy(char enemy, Mario *inMario){
   int probability;
   int diceRoll = getRandomIntInRange(1,100);
   switch(enemy){
       case 'g':
           probability = inMario->defeat_goomba_probability;
           break;
       case 'k':
           probability = inMario->defeat_koopa_probability;
           break;
       case 'b':
           probability = inMario->defeat_boss_probability;
           break;
   }


   if(diceRoll <= probability){
       // Mario Wins
       return true;
   }
   else{
       // Mario Loses
       return false;
   }


}

// Method to return whether or not the level is done.
bool Level::isLevelDone() {
    std::cout << "Checking isLevelDone(): " << is_level_done << std::endl;
    return is_level_done;
}












