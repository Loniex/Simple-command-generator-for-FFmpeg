// Holds command strings
#pragma once  // Used instead of ifdef

class Input; // Forward declaration, defined in Input.hpp

class commandStrings{
      public:
      std::string name = "";
      std::string outputName = "";
      std::string extensionString = "";
      std::string resolutionString= "";
      std::string bitrateString= "";
      std::string soundString = "";
      //Time strings
      std::string eTime = "";
      std::string sTime = ""; 
 
      void intToStr(Input& In); // Turns recieved input to command strings
      void resetCommands(); // Resets strings, for future use :
};