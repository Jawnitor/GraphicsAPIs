#ifndef INC_01_UTILITIES_HPP
#define INC_01_UTILITIES_HPP

// Indices (locations) of queue families (if they exist)
struct QueueFamilyIndices
{
    int iGraphicsFamily = -1; // Location of graphics queue families

    // check if queue families are valid
    bool isValid() { return iGraphicsFamily >= 0; }
};

#endif // INC_01_UTILITIES_HPP
