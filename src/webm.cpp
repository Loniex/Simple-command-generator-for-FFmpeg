#include <string> 
#include <sstream>



std::string handleWEBM(int* q, std::string& name, std::string& outputName, std::string& extensionString, std::string& sTime, std::string& eTime, std::string& resolution, std::string& bitR, std::string& soundString){

   std::string result = " "; 
   
   // More stringstreams because changes may be more complex than just 1 value
   std::ostringstream Best;  
   std::ostringstream Medium; 
   std::ostringstream Low; 
   // Applying recieved data to the ffmpeg commands
    switch(*q){
      case 1:
      Best << "ffmpeg -i \"" << name << extensionString << "\" " << sTime << eTime << resolution << " -c:v libvpx-vp9 -quality best -cpu-used 4 -b:v " << bitR << "k -pix_fmt yuv420p -lag-in-frames 25  -threads 8 -row-mt 1 -auto-alt-ref 1 -enable-tpl 1 -pass 1 -an " << 
       #ifdef _WIN32
        "-f null NUL && ^ \n" << 
       #elif __linux__
        "-f webm /dev/null && \n" <<
       #endif
        "ffmpeg -i \"" << name << extensionString << "\" " << sTime << eTime << resolution << " -c:v libvpx-vp9 -quality best -cpu-used 4 -b:v " << bitR << "k -pix_fmt yuv420p -lag-in-frames 25  -threads 8 -row-mt 1 -auto-alt-ref 1 -enable-tpl 1 "<< soundString << " -map_metadata -1 -pass 2 \"" << outputName <<".webm\"";
      result = Best.str();
      break;
    
      case 2:
      Medium << "ffmpeg -i \"" << name << extensionString << "\" " << sTime << eTime << resolution << " -c:v libvpx-vp9 -quality good -cpu-used 4 -b:v " << bitR << "k -pix_fmt yuv420p -lag-in-frames 25  -threads 8 -row-mt 1 -auto-alt-ref 1 -enable-tpl 1 -pass 1 -an "  <<
       #ifdef _WIN32
        "-f null NUL && ^ \n" << 
       #elif __linux__
        "-f webm /dev/null && \n" <<
       #endif
        "ffmpeg -i \"" << name << extensionString << "\" " << sTime << eTime << resolution << " -c:v libvpx-vp9 -quality good -cpu-used 4 -b:v " << bitR << "k -pix_fmt yuv420p -lag-in-frames 25  -threads 8 -row-mt 1 -auto-alt-ref 1 -enable-tpl 1 "<< soundString << " -map_metadata -1 -pass 2 \"" << outputName <<".webm\""; 
      result = Medium.str();
      break;

      case 3:
      Low << "ffmpeg -i \"" << name << extensionString << "\" " << sTime << eTime << resolution << " -c:v libvpx-vp9 -quality realtime -cpu-used 4 -b:v " << bitR << "k -pix_fmt yuv420p -lag-in-frames 25  -threads 8 -row-mt 1 -auto-alt-ref 1 -enable-tpl 1 "<< soundString << " -map_metadata -1 \"" << outputName <<".webm\""; 
      result = Low.str();
      break;
    }

   return result;
}

