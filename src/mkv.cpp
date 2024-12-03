#include <string> 
#include <sstream>



std::string handleMKV(int* q, std::string& name, std::string& outputName, std::string& extensionString, std::string& sTime, std::string& eTime, std::string& resolution, std::string& bitR, std::string& soundString){

   std::string result = " "; 

   // More stringstreams because changes may be more complex than just 1 value
   std::ostringstream Best;  
   std::ostringstream Medium; 
   std::ostringstream Low; 
   // Applying recieved data to the ffmpeg commands
    switch(*q){
      case 1:
      Best <<  "ffmpeg -i \"" << name << extensionString << "\" " << sTime << eTime << resolution << "-c:v libsvtav1 -preset 2 -pix_fmt yuv420p10le -b:v " << bitR << "k -svtav1-params tune=0:irefresh-type=1 " << soundString << " \"" << outputName << ".mkv\""; 
      result = Best.str();
      break;
    
      case 2:
      Medium <<  "ffmpeg -i \"" << name << extensionString << "\" " << sTime << eTime << resolution << "-c:v libsvtav1 -preset 6 -pix_fmt yuv420p10le -b:v " << bitR << "k -svtav1-params tune=0:irefresh-type=1 " << soundString << " \"" << outputName << ".mkv\""; 
      result = Medium.str();
      break;

      case 3:
      Low <<  "ffmpeg -i \"" << name << extensionString << "\" " << sTime << eTime << resolution << "-c:v libsvtav1 -preset 10 -pix_fmt yuv420p10le -b:v " << bitR << "k -svtav1-params tune=0:irefresh-type=1 " << soundString << " \"" << outputName << ".mkv\""; 
      result = Low.str();
      break;
    }

   return result;
}