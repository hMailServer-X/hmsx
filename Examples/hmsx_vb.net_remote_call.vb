' This example shows how a connection to a hMailServer X Remote instance
' can be done using Microsoft Visual Basic.NET by using the "vbc" VB Compiler
' Please check the build instructions at the end of file.  

Imports System
Imports System.Reflection

Module Program
    Sub Main()
        Try
            Dim type As Type = Type.GetTypeFromProgID("hmailxcomLib.clientapi")
            Dim obj As Object = Activator.CreateInstance(type)

            ' Rufe die Methode auf
            obj.sayhello()
        Catch ex As Exception
            Console.WriteLine("An error occurred: " & ex.Message)
        End Try
    End Sub
End Module

' Compile with: 
' vbc /out:hmsx_api_call_cia_vb.net.exe hmsx_api_call_cia_vb.net.vb
