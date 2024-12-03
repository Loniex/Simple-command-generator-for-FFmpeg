// Handles imputs from the user, not fool-proof against wrong inputs yet
#pragma once // Used instead of ifdef

class commandStrings; // Forward declaration, defined in Output.hpp

class Input {
      public: 
      int buffer = 0; // Will hold some stuff like suboptions   
      int IN = 0, desiredSize = 0 ,OUT = 0,  quality = 0, resolution = 0, sound = 0, vQ = 0; // User input
      int startTime[4]; // Holds the starting point for trimming as HH:MM:SS.MS 
      int endTime[4]; // Holds the array for the end-point
      int bitrate = 0;  // Bitrate for the video

      void timeQuery(int* sTimeStamp, int* eTimeStamp, int* step); // Ask the time from the user
      void resetInputs(); // Resets variables to defaults
      void userInterface(commandStrings& cS);  // Will get the input from user
      bool validateInput(int& input, int max, int min); // Checks if the input is within speicified range
      
};