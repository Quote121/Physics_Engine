#pragma once

#include "customDataTypes.hpp"

// Handles all user inputs, mapping keypresses, mouse movements to 
// functions.
//
// Keys will be placed on a queue and then read off it


constexpr int maxKeypressesPerFrame = 8;

class Input
{
private:
    ThreadSafe::Queue<unsigned int> inputQueue;

public:
    Input(int maxInputs = maxKeypressesPerFrame)
    {
        inputQueue.SetQueueLimit(maxInputs);
    }

    void ReadInputs(void);

    void ProcessInputs(void);

};
