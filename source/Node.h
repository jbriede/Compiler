#ifndef Node_h
#define Node_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
using namespace std;

class Node
{
public:
    Node(int line)
    {
        _line = line;
    }
    int get_line()
    {
        return _line;
    }
protected:
    int _line;
    
};

#endif
