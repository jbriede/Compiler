#ifndef Statement_h
#define Statement_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Node.h"
using namespace std;

class Statement : public Node
{
public:
    Statement (int line): Node(line)
    {
    }
private:

    
};

#endif
