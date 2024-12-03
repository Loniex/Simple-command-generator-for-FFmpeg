#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define SAFETYMARGIN 2  // Used for encodings with audio

// Libraries that handle commands
#include "webm.hpp"
#include "mp4.hpp"
#include "mkv.hpp"

//Own libraries
#ifdef INCLUDE_YTDL
#include "YTDL.hpp" // Commands for yt-dlp 
#endif
#include "Input.hpp" // Holds input values
#include "Output.hpp" // Holds command strings
#include "timeHandler.hpp" // Turns time to string

int calulateBitrate(Input& In); // Calculates the bitrate, to achieve the desired size
void overwriteData(std::string& fileName, std::string data);
void appendData(std::string& fileName, std::string data);

int main() {
    // Classes
    Input In; 
    commandStrings cS;
    timeHandler tH;
#ifdef INCLUDE_YTDL
    addons add;
#endif

    // Will hold the command for ffmpeg
    #ifdef _WIN32
    std::string fileName = "commands.bat";
    #elif __linux__
    std::string fileName = "commands.sh";
    #endif

    std::string ffmpegCommand = "";
#ifdef INCLUDE_YTDL
    std::string ytDlp = "";
    bool exitLoop = false;

    while(!exitLoop){
    ytDlp = add.downloadSpecs();

    std::cout << "\nWrite?\n1.Yes\n2.Overwrite\n3.Escape" << std::endl;    
    In.buffer = 0;
    In.validateInput(In.buffer, 1,3);
    switch(In.buffer){
        case 1:
        appendData(fileName, ytDlp);
        break;

        case 2:
        overwriteData(fileName, ytDlp);
        break;

        case 3:
        exitLoop = true;
        break;

        default:
        std::cout << "Continuing..." << std::endl;
        break;
    }
    
    }

#endif
    // Main logic
    In.userInterface(cS);     
    In.bitrate  = calulateBitrate(In); 
    tH.timeToString(In, cS, 0);
    cS.intToStr(In);  
      
    // Sends the input to the correct function
    switch(In.OUT){

        case 1:
        ffmpegCommand = handleMP4(&In.quality, cS.name,  cS.outputName, cS.extensionString, cS.sTime, cS.eTime, cS.resolutionString, cS.bitrateString, cS.soundString); 
        break;

        case 2:
        ffmpegCommand = handleMKV(&In.quality, cS.name,  cS.outputName, cS.extensionString, cS.sTime, cS.eTime, cS.resolutionString, cS.bitrateString, cS.soundString); 
        break;

        case 3:
        ffmpegCommand = handleWEBM(&In.quality, cS.name,  cS.outputName, cS.extensionString, cS.sTime, cS.eTime, cS.resolutionString, cS.bitrateString, cS.soundString);        
        break;

        default: 
        std::cerr << "Incorrect extension choosed... Please, use the value between 1 and 3 without any other symbols...\n" << std::endl; 
        std::cout << In.OUT << std::endl;
        break;
    }
    
   overwriteData(fileName, ffmpegCommand);
   In.buffer = 0;
   std::cout << "Launch the commands" <<
             #ifdef __WIN32
                ".bin" << 
             #elif __linux__
                ".sh" << 
             #endif
                " file?\n1.No\n2.Yes" << std::endl;  
   In.validateInput(In.buffer,1,2);

   switch(In.buffer){
   
   case 1:
   // Some future logic to make more ffmpeg commands or other options here
   In.buffer = 1; 
   break;
   
   case 2:
   #ifdef _WIN32
   system("commands.bat"); // Call the function to execute the .bat file from the program
   #elif __linux__
   system("./commands.sh");
   #endif

   In.buffer = 2; 
   break;
   } 
    return 0;
}

void overwriteData(std::string& fileName, std::string data){
    std::ofstream batFile(fileName,std::ios::trunc);
    if(!batFile){
        std::cerr << "Error creating and resetting the file " << fileName << std::endl;
    }else{

        #ifdef __linux__
        batFile << "#!/bin/bash" << std::endl;
        #endif

        batFile << data << std::endl;

        #ifdef _WIN32
        batFile << "timeout 50" << std::endl;
        #elif __linux__
        batFile << "sleep 50" << std::endl;
        #endif
    }
}

void appendData(std::string& fileName, std::string data){
    std::ofstream batFile(fileName, std::ios::app);
    if(!batFile){
    std::cout << "Error opening the file...\n" << std::endl;
    }else{
       batFile << data << std::endl;
       batFile << "timeout 50" << std::endl;
    }
}


int calulateBitrate(Input& In){
   float actualLength =((In.endTime[0] * 60 * 60) + (In.endTime[1] * 60) + In.endTime[2] + (In.endTime[3] / 1000)) - ((In.startTime[0] * 60 * 60) + (In.startTime[1] * 60) + In.startTime[2] + (In.startTime[3] / 1000));  // Calculates the length in seconds
   int bitrate = 0; 
   switch(In.sound){

   case 1: 
   bitrate = (In.desiredSize * 8000 / actualLength) - 2; // Calculate bitrate to land within the specified range
   break; 

   case 2:
   bitrate = (In.desiredSize * 8000 / actualLength) - 2 - (96 * SAFETYMARGIN); // Remove audo bitrate to land within the specified size with some safety margin
   break;
   }
    return bitrate;
   
}




