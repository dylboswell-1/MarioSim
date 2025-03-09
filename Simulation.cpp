#include "Simulation.h"
#include "Level.h"
#include "Mario.h"
#include "Logger.h"

#include <iostream>
#include <string>


// Default Constructor
Simulation::Simulation(Mario *inMario, Logger *inLogger) : sim_mario(inMario), sim_logger(inLogger) {
    // Set number of levels
    number_of_levels = sim_logger->number_of_levels;

    // Allocate array for levels
    world = new Level*[number_of_levels];

    // Initializing levels
    std::cout << "\nThere are " << number_of_levels << " levels in total" << std::endl;
    for (int i = 0; i < number_of_levels; i++) { 

        if (i >= number_of_levels) {  // Debug check
            std::cerr << "ERROR: Trying to create a level that does not exist! (i = " << i << ")\n";
            exit(1);
        }

        bool isFinalLevel = (i == number_of_levels - 1);
        std::cout << "Queuing Level " << i << std::endl;
        

        world[i] = new Level(sim_mario, sim_logger, isFinalLevel);

        std::cout << "Level " << i << " Created" << std::endl;
        std::cout << "Calling makeLevelMap() on Level " << i << "..." << std::endl;

        // Output the level
        std::string tempMapMessage = sim_logger->makeLevelMap(world[i]);
        std::cout << "Made the map string." << std::endl;
        sim_logger->writeOutputMap(tempMapMessage);
        std::cout << "Wrote the level to the output file." << std::endl;
    }

    std::cout << "Constructed the simulation." << std::endl;
}

void Simulation::playGame() {
    std::cout << "Starting playGame()\n"<< std::endl;

    // Debug checking to see if number_of_levels is correct
    std::cout << "DEBUG: number_of_levels = " << number_of_levels << std::endl;

    for (int i = 0; i < number_of_levels; i++) {  
        if (i >= number_of_levels) {  
            std::cerr << "ERROR: Trying to access non-existent level " << i;
            exit(1);
        }

        std::cout << "Starting Level " << i << std::endl;

        if (world[i] == nullptr) {
            std::cerr << "ERROR: world[" << i << "] is NULL before accessing it!\n";
            exit(1);
        }

        while (sim_mario->hasLives() && !world[i]->isLevelDone()) {
            if (sim_mario->getXPosition() == -1 && sim_mario->getYPosition() == -1) {
                sim_logger->writeOutputMessage("****** Spawning Mario in new level ******\n");
                std::cout << "Spawning Mario in new Level " << i << std::endl;
                world[i]->spawnMario(sim_mario);
            }

            std::cout << "Moving Mario..." << std::endl;
            world[i]->moveMarioRandomly(sim_mario,sim_logger);
            std::cout << "Mario moved to (" << sim_mario->getXPosition() << ", " << sim_mario->getYPosition() << ")\n" << std::endl;

            if (world[i] == nullptr) {
                std::cerr << "ERROR: world[" << i << "] is NULL before generating level map!\n";
                exit(1);
            }

            std::string values = sim_logger->getValues(sim_mario, world[i], i);
            std::string map = sim_logger->makeLevelMap(world[i]);

            std::cout << "Values generated. Writing output to file...\n" << std::endl;
            sim_logger->writeOutputAll(values, map);
            std::cout << "Finished writing output.\n" << std::endl;
        }

        std::cout << "Finished Level " << i << std::endl;

        if (!sim_mario->hasLives()) {
            sim_logger->writeOutputMessage("Mario has died on the current level ---- GAME OVER");
            std::cout << "Mario has died -- GAME OVER\n" << std::endl;
            break;
        }

        if (!world[i]->isFinalLevel()) {
            sim_logger->writeOutputMessage("Mario has completed the level\n");
            sim_logger->writeOutputMessage("Final Mario Output " + sim_logger->getValues(sim_mario, world[i], i));
        } else {
            sim_logger->writeOutputMessage("Mario has beaten the game and saved the princess!\n");
            sim_logger->writeOutputMessage("Final Mario Output " + sim_logger->getValues(sim_mario, world[i], i));
        }

        sim_mario->setPosition(-1, -1); // Reset Mario's position for the next level
    }

    std::cout << "Finished playGame()" << std::endl;
}


// Default Deconstructor
Simulation::~Simulation() {
    std::cout << "Destroying Simulation...\n"<< std::endl;
    if (world) {
        for (int i = 0; i < number_of_levels; i++) {
            if (world[i]) {
                std::cerr << "DELETING Level " << i << " in Simulation::~Simulation()";
                delete world[i];  
                world[i] = nullptr;
            }
        }
        delete[] world;
        world = nullptr;
    }
    std::cout << "Simulation deleted successfully.\n"<< std::endl;
}







