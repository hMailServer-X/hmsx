/* This example shows how a connection to a hMailServer X remote 
 * instance can be done using the Microsoft C# Programming language
 * Please check also the build instructions at the end of file.  
 */

using System;
using System.Reflection;

class Program
{
    static void Main()
    {
        try
        {
            Type type = Type.GetTypeFromProgID("hmailxcomLib.clientapi");
            dynamic obj = Activator.CreateInstance(type);

            // Rufe die Methode auf
            obj.sayhello();
        }
        catch (Exception ex)
        {
            Console.WriteLine("An error occurred: " + ex.Message);
        }
    }
}

// Build instructions: 
// 1) Make sure hmailxcom.dll is registred (if not, type in regsvr32 hmailxcom.dll)
// 2) Compile with on Visual Studio Command prompt with "csc hmsx_c#.net_remote_call.cs"
// 3) Run the compiled exe by typing in: hmsx_c#.net_remote_call.exe
