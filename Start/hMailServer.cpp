#include "pch.h"
#include <iostream>
#include <string>
#include "../Common/Util/Utilities.h"
#include "../Common/Util/runtime_variables.h"

using namespace std;

void InitializeApplication(HM::String inifile)
{    
    HM::String sErrorMessage;
    if (HM::Application::Instance()->InitInstance(sErrorMessage))
    {
        HM::Application::Instance()->HmsBinFolder = inifile;
        HM::Application::Instance()->StartServers();
    }
    else
    {
        std::cout << "Failed to initialize: Did you specify a correct INI path?";
    }
}

/* hMailServer main function */
int main(int argc, char* argv[])
{

    cout << "\nStarting hMailServer X \n\n";
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " --setinifile=<string>" << std::endl;
        return 1;
    }

    std::string arg = argv[1];

    // Check if parameter "--setinifile=" is set first
    if (arg.find("--setinifile=") == 0)
    {
        // Extract the path after "=" char
        size_t equalSignPos = arg.find('=');
        if (equalSignPos != std::string::npos)
        {
            std::string value = arg.substr(equalSignPos + 1);            
            std::cout << "\n[Status] - Load IniFile from path: " << value << "\n" << std::endl;

            writeIniPath(value);  // pass args via a safe mutex variable


 /*           int status = ares_library_init(ARES_LIB_INIT_ALL);
            if (status != ARES_SUCCESS)
            {
                printf("C-ARES initialized.\n");                
            }*/

            InitializeApplication(value);     
            return 1;
        }
        else
        {
            std::cerr << "The --setinifile param is not set correctly: Usage: --setinifile=<string>" << std::endl;
        }
    }
    else {
        std::cerr << "No hMailServer ini file specified. Usage: --setinifile=<string>\n" << std::endl;
      
        return 1;
    }
       
   
    return 0;
}
