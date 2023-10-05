/* This example shows how a connection to a hMailServer X remote  instance   can be done 
 * using the Embacadero CBuilder C/C++ Compiler by using the hMailServer X Native Client 
 * Library (DLL on Windows), this example doesn't use COM/DCOM at all. 
 * Please check also the build instructions at the end of file.
 */

#include <windows.h>
#include <stdio.h>

typedef int (*AddNumbersFunc)(int, int);

int main()
{
    HINSTANCE hDLL = LoadLibrary("hmxlib.dll"); // Provide the hMailServer X native Client Library (*.dll not COM)

    if (hDLL != NULL)
    {
        AddNumbersFunc addFunc = (AddNumbersFunc)GetProcAddress(hDLL, "AddNumbers");

        if (addFunc != NULL)
        {
            int result = addFunc(10, 20);
            // Execute the function in the DLL


            printf("Result: %d result\n");
            FreeLibrary(hDLL); //set the DLL free after the operation finishes.
        }
        else
        {
                  printf("Error loading DLL\n");
        }
    }
    else  {
        printf("DLL could not be loaded\n");

    }

    getchar();
    return 0;
}

//Build:
// 1) Create a new CBuilder project
// 2) Add this source file to the projec
// 3) Add the hmxlib.dll in your EXE folder
// 4) Compile and run
