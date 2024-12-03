#include <string>
#include <sstream>

#include "Output.hpp"
#include "Input.hpp"
#include "timeHandler.hpp"

void timeHandler::handleTime(int* timeArray, std::string (&timeString)[4]){
      if(timeArray[0] <= 0){
        timeString[0] = "00"; 
    
      } else if(timeArray[0] >= 1 && timeArray[0] <= 9){
        std::ostringstream hString;     
    
        hString << "0" << timeArray[0]; 
        timeString[0] = hString.str(); 
    
      } else if(timeArray[0] >= 10){
         timeString[0] = std::to_string(timeArray[0]);
    
      }
       
    
    
       if(timeArray[1] <= 0){
        timeString[1] = "00"; 
    
      } else if(timeArray[1] >= 1 && timeArray[1] <= 9){
        std::ostringstream mString;     
        mString << "0" << timeArray[1]; 
        timeString[1] = mString.str(); 
     
      } else if(timeArray[1] >= 10){
         timeString[1] = std::to_string(timeArray[1]);
      }
    
    
    
       if(timeArray[2] <= 0){
        timeString[2] = "00"; 
    
       }else if(timeArray[2] >= 1 && timeArray[2] <= 9){
        std::ostringstream sString;     
        sString << "0" << timeArray[2]; 
        timeString[2] = sString.str(); 
    
       }else if(timeArray[2] >= 10){
         timeString[2] = std::to_string(timeArray[2]);
        
       }
    
    
      if(timeArray[3] <= 0){
         timeString[3] = "000"; 
      } else if(timeArray[3] >= 1 && timeArray[3] <= 9){
         std::ostringstream msString;
         msString << "00" << timeArray[3];   
         timeString[3] = msString.str();
    
      }else if(timeArray[3] >= 10 && timeArray[3] <= 99){
           std::ostringstream msString;
           msString << "0" << timeArray[3];   
           timeString[3] = msString.str();
       
      }else if(timeArray[3] >=100){
           timeString[3] = std::to_string(timeArray[3]);
      }
    
    }

// Changes time to an actual command for ffmpeg
void timeHandler::timeToString(Input& In, commandStrings& cS, int requestFromYTDL){
      std::string sTimeBuffer[4]; 
      std::string eTimeBuffer[4];
    
    
      // Check if a trim should take place
      if(requestFromYTDL == 0 && In.startTime[0] == 0 && In.startTime[1] == 0 && In.startTime[2] == 0 && In.startTime[3] == 0){
          cS.sTime = ""; // Make sure  that both are empty, because trim isn't used     
          cS.eTime = "";
    
        }else if(requestFromYTDL == 0){
         handleTime(In.endTime, eTimeBuffer);
         std::ostringstream ETimeString;
         ETimeString << " -to " << eTimeBuffer[0] << ":" << eTimeBuffer[1] << ":" << eTimeBuffer[2] << "." << eTimeBuffer[3];
         cS.eTime= ETimeString.str();
     
         handleTime(In.startTime, sTimeBuffer);
         std::ostringstream STimeString;
         STimeString << " -ss " << sTimeBuffer[0] << ":" << sTimeBuffer[1] << ":" << sTimeBuffer[2] << "." << sTimeBuffer[3];
         cS.sTime = STimeString.str();
    
        }else if(requestFromYTDL == 1){
         handleTime(In.endTime, eTimeBuffer);
         std::ostringstream ETimeStringY;
         ETimeStringY << "-" << eTimeBuffer[0] << ":" << eTimeBuffer[1] << ":" << eTimeBuffer[2] << "." << eTimeBuffer[3] << "\"";
         cS.eTime = ETimeStringY.str();
     
         handleTime(In.startTime, sTimeBuffer);
         std::ostringstream STimeStringY;
         STimeStringY << "\"*" << sTimeBuffer[0] << ":" << sTimeBuffer[1] << ":" << sTimeBuffer[2] << "." << sTimeBuffer[3];
         cS.sTime = STimeStringY.str();

        }else if(requestFromYTDL == 2){
         handleTime(In.endTime, eTimeBuffer);
         std::ostringstream ETimeStringY;
         ETimeStringY << "\"*" << eTimeBuffer[0] << ":" << eTimeBuffer[1] << ":" << eTimeBuffer[2] << "." << eTimeBuffer[3] << "-";
         cS.eTime = ETimeStringY.str();
     
         In.endTime[3]+=1;
         handleTime(In.endTime, sTimeBuffer);
         std::ostringstream STimeStringY;
         STimeStringY << sTimeBuffer[0] << ":" << sTimeBuffer[1] << ":" << sTimeBuffer[2] << "." << sTimeBuffer[3] << "\"";
         cS.sTime = STimeStringY.str();

        }

         
    }