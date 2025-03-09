#include "Logger.h"
#include "Level.h"
#include "Mario.h"


#include <string>
#include <fstream>
#include <iostream>


// Default constructor
Logger::Logger(std::string inputFile, std::string outputFile) : inFile(inputFile), outFile(outputFile) {

   if(inFile.is_open()){
        // Grabbing each line from the input file, and assigning values
        std::string line;
        
        int inputValues[8];
        for(int i = 0; i < 8; i++){
            std::getline(inFile, line);
            int num = std::stoi(line); // Casting string to integer
            inputValues[i] = num;
        }

        number_of_levels = inputValues[0];
        std::cout << "DEBUG: Read number_of_levels = ------------------------------------------------- " << number_of_levels << std::endl;
        level_dimension = inputValues[1];
        number_of_lives = inputValues[2];
        coin_percentage = inputValues[3];
        nothing_percentage = inputValues[4];
        goomba_percentage = inputValues[5];
        koopa_percentage = inputValues[6];
        mushroom_percentage = inputValues[7];
        std::cout << "Logger has been constructed" << std::endl;
    }
    else{
        std::cout << "Couldn't open the input file." << std::endl; // Error message if the computer fails to open the input file.
    }


};

Logger::~Logger(){
    std::cout << "Closed the files." << std::endl;
    inFile.close();
    outFile.close();
};

// Method handles gathering values and creating output string.
std::string Logger::getValues(Mario *mario, Level* currentLevel, int currentLevelNumber) {
    std::cout << "Getting values from game...\n"<< std::endl;
    int level_number = currentLevelNumber; // From Simulation
    std::string mario_tile_interaction = currentLevel->getTileInteraction();
    std::string mario_next_move = currentLevel->getNextMove();
    int mario_X_Position = mario->getXPosition(); // From Mario
    int mario_Y_Position = mario->getYPosition();
    int mario_Power_Level = mario->getPowerLevel();
    int mario_lives = mario->getLives();
    int mario_coins = mario->getCoins();

    // Debugging: Print values before converting to string
    std::cout << "Level: " << level_number << "\n"<< std::endl;
    std::cout << "Mario's Position: (" << mario_X_Position << ", " << mario_Y_Position << ")\n"<< std::endl;
    std::cout << "Mario's Power Level: " << mario_Power_Level << "\n"<< std::endl;
    std::cout << "Mario's Lives: " << mario_lives << "\n"<< std::endl;
    std::cout << "Mario's Coins: " << mario_coins << "\n"<< std::endl;
    std::cout << "Tile Interaction: " << mario_tile_interaction << "\n"<< std::endl;
    std::cout << "Mario's Next Move: " << mario_next_move << "\n"<< std::endl;

    // Convert integer values to strings
    std::string string_level_number = std::to_string(level_number);
    std::string string_mario_X_Position = std::to_string(mario_X_Position);
    std::string string_mario_Y_Position = std::to_string(mario_Y_Position);
    std::string string_mario_Power_Level = std::to_string(mario_Power_Level);
    std::string string_mario_lives = std::to_string(mario_lives);
    std::string string_mario_coins = std::to_string(mario_coins);

    // Build output string
    std::string outputString = "Level: " + string_level_number + ". Mario is at position: (" + 
        string_mario_X_Position + "," + string_mario_Y_Position + "). Mario is at power level " +
        string_mario_Power_Level + ". " + mario_tile_interaction + 
        " Mario has " + string_mario_lives + " lives left. Mario has " +
        string_mario_coins + " coins.\n\n";

    std::cout << "getValues() successfully generated output string.\n"<< std::endl;
    return outputString;
}

std::string Logger::makeLevelMap(Level* currentLevel) {

    std::cout << "Generating level map...\n"<< std::endl;

    // Debugging to see if the level we are accessing is just nullptr
    if (currentLevel == nullptr) {
        std::cerr << "ERROR: currentLevel is NULL in makeLevelMap()!\n";
        return "ERROR: Level not found.\n";
    }

    // Checking to see if the char** level at the provided level is uninitialized/empty.
    if (currentLevel->getLevel() == nullptr) {
        std::cerr << "ERROR: level[][] is NULL in makeLevelMap()!\n";
        return "ERROR: Level data missing.\n";
    
    }

    // Making the map as a string.
    std::string output = "==================\n";
    for (int i = 0; i < level_dimension; i++) { 
        for (int j = 0; j < level_dimension; j++) {
            std::cout << "Reading tile at (" << i << ", " << j << ")...\n"<< std::endl;

            if (currentLevel == nullptr){
                return "ERROR: Level deleted unexpectedly.";
            } 

            char tile = currentLevel->getLevelTile(i, j);
            output += tile;
        }
        output += "\n";  
    }
    

    std::cout << "makeLevelMap() successfully created map string.\n"<< std::endl;
    return output;
}

void Logger::writeOutputAll(std::string info, std::string map) {
    std::cout << "Combining map and info into a string...\n"<< std::endl;
    
    std::string output = map + info;
    std::cout << "Output string prepared!\n"<< std::endl;

    if(outFile.is_open()) { 
        std::cout << "File is open, writing output...\n"<< std::endl;
        outFile << output << std::endl;
        std::cout << "Output written to file.\n"<< std::endl;
    } else {
        std::cerr << "ERROR: Couldn't open output file: " << outputFileName << std::endl;
    }
}

void Logger::writeOutputMessage(std::string message) {
   // Checking if the file opened successfully
   if (outFile.is_open()) { 
       outFile << message << std::endl;
   } else {
       std::cerr << "Couldn't open output file: " << outputFileName << std::endl;
   }
}

void Logger::writeOutputMap(std::string map) {
   // Checking if the file opened successfully
   if (outFile.is_open()) { 
       outFile << map << std::endl;
   } else {
       std::cerr << "Couldn't open output file: " << outputFileName << std::endl;
   }
}





