#include <string> 
#include <sstream>



std::string handleMP4(int* q, std::string& name, std::string& outputName, std::string& extensionString, std::string& sTime, std::string& eTime, std::string& resolution, std::string& bitR, std::string& soundString){

   std::string result = " "; 

   // More stringstreams because changes may be more complex than just 1 value
   std::ostringstream Best;  
   std::ostringstream Medium; 
   std::ostringstream Low; 
   // Applying recieved data to the ffmpeg commands
    switch(*q){
      case 1:
      Best << "ffmpeg -i \"" << name << extensionString << "\" " << sTime << eTime << resolution << " -c:v libx265 -preset slower  -b:v " << bitR << "k -pix_fmt yuv420p10le -movflags +faststart -x265-params pass=1:no-slow-firstpass=1 -an "
       #ifdef _WIN32
        "-f null NUL && ^ \n" << 
       #elif __linux__
        "-f webm /dev/null && \n" <<
       #endif
      "ffmpeg -i \"" << name << extensionString << "\" " << sTime << eTime << resolution << " -c:v libx265 -preset slower  -b:v " << bitR << "k -pix_fmt yuv420p10le -threads 8  "<< soundString << " -map_metadata -1 -movflags +faststart -x265-params pass=2  \"" << outputName <<".mp4\"";

      result = Best.str();
      break;
    
      case 2:

      Medium << "ffmpeg -i \"" << name << extensionString << "\" " << sTime << eTime << resolution << " -c:v libx265 -preset medium  -b:v " << bitR << "k -pix_fmt yuv420p10le -movflags +faststart -x265-params pass=1:no-slow-firstpass=1 -an "
       #ifdef _WIN32
        "-f null NUL && ^ \n" << 
       #elif __linux__
        "-f webm /dev/null && \n" <<
       #endif
        "ffmpeg -i \"" << name << extensionString << "\" " << sTime << eTime << resolution << " -c:v libx265 -preset medium  -b:v " << bitR << "k -pix_fmt yuv420p10le -threads 8  "<< soundString << " -map_metadata -1  -movflags +faststart -x265-params pass=2  \"" << outputName <<".mp4\"";
      result = Medium.str();
      break;

      case 3:
      Low << "ffmpeg -i \"" << name << extensionString << "\" " << sTime << eTime << resolution << " -c:v libx265 -preset superfast  -b:v " << bitR << "k -pix_fmt yuv420p10le -movflags +faststart -x265-params pass=1:no-slow-firstpass=1 -an "
       #ifdef _WIN32
        "-f null NUL && ^ \n" << 
       #elif __linux__
        "-f webm /dev/null && \n" <<
       #endif
        "ffmpeg -i \"" << name << extensionString << "\" " << sTime << eTime << resolution << " -c:v libx265 -preset superfast  -b:v " << bitR << "k -pix_fmt yuv420p10le -threads 8  "<< soundString << " -map_metadata -1 -movflags +faststart -x265-params pass=2  \"" << outputName <<".mp4\"";
      result = Low.str();
      break;
    }

   return result;
}
