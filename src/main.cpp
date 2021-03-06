#include "../include/tweakbukconv.h"
#include <string>
#include <iostream>
#include <vector>


int main (int argc, char *argv[])
{
    string inifile = "NULL";
    inifile = "conf/test.ini";
    bool ineedroot = false;

    vector<string> args;
    for (int nArg=0; nArg < argc; nArg++)
    {
        args.push_back(argv[nArg]);
    }
    for (uint nArg=0; nArg < args.size(); nArg++)
    {
        if (args[nArg] == "-c")
        {
            if ((nArg+1) <= args.size())
            {
                inifile = args[nArg+1];
            }
        }
        if (args[nArg] == "-INeedRootPowerz")
        {
            ineedroot = true;
        }
    }
    if (getuid() == 0 && ineedroot != true)
    {
        cout << "dont start as root" << endl;
        cout << "if you really need root. start with -INeedRootPowerz" << endl;
        return 0;
    }
    else
    {
        if (inifile == "NULL")
        {
            cout << "please provide a ini file with -c <inifile>" << endl;
        }
        else
        {
            tweakbukconv *tbc = new tweakbukconv();
            tbc->Init(inifile);
            tbc->Run();
            delete tbc;
        }
        cin.get();
        return 0;
    }
    return 0;
    exit(1);
}

