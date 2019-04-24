#ifndef Statement_h
#define Statement_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Node.h"
#include "Writer.h"
using namespace std;

class Statement : public Node
{
public:
    Statement (int line): Node(line)
    {
    }
    void generate(Writer* writer)
    {
        writer->append_main("default generator... probably shouldnt be writing this");
    }
private:

    
};

#endif
