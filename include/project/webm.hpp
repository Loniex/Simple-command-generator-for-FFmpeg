#pragma once

// The command doesn't take advantage of the calsses because it was easier to manage ffmpeg commands that way
std::string handleWEBM(int* q, std::string& name, std::string& outputName, std::string& extensionString, std::string& sTime, std::string& eTime, std::string& resolution, std::string& bitR, std::string& soundString);