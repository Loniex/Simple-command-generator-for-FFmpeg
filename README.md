# Simple command generator for FFmpeg
## Overview
The point of this program is to make ffmpeg a bit more user friendly by generating commands from input

Works with .mp4, .mkv and .webm files
## Usage 
### Windows
Execute the program, input parameters, execute the resulting file to start FFmpeg
### Linux
Set the program as executable: ``` chmod +x encoder ```, input parameters, make the resulting file executable as well: ``` chmod +x commands.sh ```, execute the file to start FFmpeg

## Installation
### Prerequisites
- CMake 3.10
- FFmpeg accessible from terminal
- .mp4/.mkv/.webm video file in the same folder with the program 

### Building
```bash
cd build 
cmake ..
make
cd ../bin
```
