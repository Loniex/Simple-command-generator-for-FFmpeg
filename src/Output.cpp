#include <string>
#include "Output.hpp"
#include "Input.hpp"

void commandStrings::resetCommands(){
    // Resets inputs for later reuse in the future versions, where multiple ffmpeg commands could be created
      std::string name = "";
      std::string outputName = "";
      std::string extensionString = "";
      std::string resolutionString= "";
      std::string bitrateString= "";
      std::string soundString = "";
      std::string eTime = "";
      std::string sTime = ""; 
}


void commandStrings::intToStr(Input& In){
 // Changes exteinsion to string for later use in ffmpeg
 switch(In.IN){
     case 1:
     extensionString=".mp4";
     break;
 
     case 2:
     extensionString=".mkv";
     break;
 
     case 3: 
     extensionString=".webm";
     break;
    }

 // Changes resolution setting to string for later use in ffmpeg     
   switch(In.resolution){
    case 1:
     resolutionString = "";
    break;

    case 2:
     resolutionString = " -vf scale=-1:2160 ";
    break;

   case 3:
     resolutionString = " -vf scale=-1:1440 ";
    break; 

   case 4:
    resolutionString = " -vf scale=-1:1080 ";
   break; 

   case 5:
    resolutionString = " -vf scale=-1:720 ";
   break; 
   
   }
   
  // Changes bitrate to string
  bitrateString = std::to_string(In.bitrate);   

  // Changes sound to string
  switch(In.sound){
    case 1:
    soundString = " -an ";
    break;
    
    case 2:
     soundString = " -c:a libopus -b:a 96k ";
  
    break;
  }
}
