//Handles time inputs
#pragma once

class Input;
class commandStrings;

class timeHandler{
    private:
    void handleTime(int* timeArray, std::string (&timeString)[4]); // Changes int values to strings

    public:
    void timeToString(Input& In, commandStrings& cS, int requestFromYTDL); // Changes tome time commands
};