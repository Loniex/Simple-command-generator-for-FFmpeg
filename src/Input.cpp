#include <string>
#include <iostream>
#include <limits>
#include "Output.hpp"
#include "Input.hpp"

// Will try to get the correct input, may have issues with float values, something to look into in the future
bool Input::validateInput(int& input, int min, int max){
     while(true){
      std::cin >> input;

      if(std::cin.fail() || input > max || input < min){
        std::cerr << "Invalid input...\nPlease, provide an integer value without any special symbols between " << min << " and " << max << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }else {
        return true;
       }
     }  
}
      
 
 void Input::resetInputs(){
       IN = 0; OUT = 0; desiredSize = 0; quality = 0; resolution; sound = 0; bitrate = 0; 

       for(int i = 0; i < 4; i++){
         startTime[i] = 0;
         endTime[i] = 0;
       }

      }

void Input::timeQuery(int* sTimeStamp, int* eTimeStamp, int* buffer){
if(*buffer == 1){
 *buffer = 1;
    while(*buffer < 3) {
     for(int i = 0; i <= 3; i++){
         switch(i){
            case 0: 
             if(*buffer == 1){
              std::cout << "Specify starting point..." << std::endl;  
             } else {
              std::cout << "Specify ending point..." << std::endl; 
             }
             std::cout << "Hours:";  
             
             if(*buffer == 1){
              validateInput(sTimeStamp[i], 0, 99);
             }else{
              validateInput(eTimeStamp[i], 0, 99);
             }
            break; 
            
            case 1:
             std::cout << "Minutes:";
             if(*buffer == 1){
              validateInput(sTimeStamp[i], 0, 59); 
             }else{
              validateInput(eTimeStamp[i], 0, 59);  
             }
            break;
            
           case 2:
             std::cout << "Seconds:";
             if(*buffer == 1){
              validateInput(sTimeStamp[i], 0, 59);  
             }else{
              validateInput(eTimeStamp[i], 0, 59); 
             }
            break;
          
           case 3:
             std::cout << "Milliseconds:" ;
             if(*buffer == 1){
              validateInput(sTimeStamp[i], 0, 999);
             }else{
              validateInput(eTimeStamp[i], 0, 999);
             }
             std::cout << "" << std::endl;  
            break;
          
         }
        }
      *buffer+=1;
       }
    }else{
     for(int i = 0; i <= 3; i++){
         switch(i){
            case 0:
             if(*buffer == 3){
             std::cout << "Specify the timestamp of frame:" << std::endl; 
             }else{
             std::cout << "Specify video length..." << std::endl; 
             }
             std::cout << "Hours:";  
             sTimeStamp[i] = 0;
             validateInput(eTimeStamp[i], 0, 99); 
            break; 
            
            case 1:
             std::cout << "Minutes:";
             sTimeStamp[i] = 0;
             validateInput(eTimeStamp[i], 0, 59);  
            break;
            
           case 2:
             std::cout << "Seconds:";
             sTimeStamp[i] = 0;
             validateInput(eTimeStamp[i], 0, 59); 
            break;
          
           case 3:
             std::cout << "Milliseconds:";
             sTimeStamp[i] = 0; 
             validateInput(eTimeStamp[i], 0, 999); 
             std::cout << "" << std::endl;  
            break;
          
         }
        }
       }
}

void Input::userInterface(commandStrings& cS) {
    //Reset everything
    resetInputs();
    cS.resetCommands();   

    // Input read starts 

    std::cout << "\nWhich file video extension will be used for the input?\nWrite the number of the option you need...\n1.mp4\n2.mkv\n3.webm" << std::endl; 
    validateInput(IN, 1, 3);
    std::cout << "Write the name of the video file to encode:" << std::endl; 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input
    std::getline(std::cin, cS.name);
    std::cout << "\nDo you want to use the same name for the output file?\n1.Yes\n2.No" << std::endl;
    validateInput(buffer, 1, 2);
    switch(buffer){
       case 1:
       cS.outputName = cS.name;
       break;

       case 2:
       std::cout << "Specify output name: " << std::endl;
       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
       std::getline(std::cin, cS.outputName);
       break;
    }
    buffer = 0;
    std::cout << "\nDo you wish to trim the video file?\n1.Yes\n2.No" << std::endl; 
    validateInput(buffer, 1, 2);
    timeQuery(startTime, endTime, &buffer);
    
    std::cout << "\nWhat size in MB do you want?\nNote, that the output file size won't excactly match set sieze, but will be within the range of it" << std::endl; 
    validateInput(desiredSize, 0, 999999); // Just for safety 

    std::cout << "\nDo you want to change the resolution of the video?\n1.No\n2.2160p\n3.1440p\n4.1080p\n5.720p" << std::endl; 
    validateInput(resolution,1,5);

    std::cout  << "\nRemove sound?\n1.Yes\n2.No" << std::endl;   
    validateInput(sound,1,2);

    std::cout << "\nSet encoding quality:\n1.High\n2.Medium\n3.Low" << std::endl; 
    validateInput(quality,1,3);

    std::cout << "\nWhich file video extension will be used for the output?\n1.mp4(H265)\n2.mkv(AV1)\n3.webm(VP9)" << std::endl; 
    validateInput(OUT,1,3);

if(quality == 3 && OUT == 3){
      desiredSize /=2; // Due to the poor performance of the codec at "realtime" setting, the average bitrate/required size should be cut in half in order to get within the required size range, otherwise the size is doubled
    } 

}

