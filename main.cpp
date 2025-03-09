#include "Mario.h"
#include "Level.h"
#include "Logger.h"
#include "Simulation.h"

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
   // Error message for if the amount of command line arguments are wrong.
   if (argc < 3) {
      std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
      return 1;
   }

   std::string inputFileName = argv[1];
   std::string outputFileName = argv[2];

   Logger* main_logger = new Logger(inputFileName, outputFileName);
   Mario* main_mario = new Mario(main_logger->number_of_lives);
   
   Simulation main_simulation(main_mario, main_logger);
   
   main_simulation.playGame();

   delete main_logger;
   delete main_mario;

   return 0;
}



