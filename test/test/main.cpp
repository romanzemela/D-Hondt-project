//
//  main.cpp
//  test
//
//  Created by Mateusz Piwowarski on 01.11.2017.
//  Copyright © 2017 Penta Co. All rights reserved.
//

#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
    cout << "argc: " << argc << endl;
    for(int i = 0; i < argc; i++)
    {
        cout <<"argv[" << i << "] = " << argv[i] << endl;
    }
    return 0;
}
