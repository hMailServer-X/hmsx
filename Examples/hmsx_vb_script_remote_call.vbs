' This example shows how a connection to a hMailServer X remote 
' instance can be done using the Visual Basic Scripting Language.
' Please check also the build instructions at the end of file.  
' This also works for Active Server Pages (ASP)

Dim obj
Set obj = CreateObject("hmailxcomLib.clientapi")

obj.sayhello

Set obj = Nothing

'Build instructions: 
' 1) Open a Windows Command prompt
' 2) Run the script by typing: cscript hmsx_vb_script_remote_call.vbs
' 3) Run the script by typing: wscript hmsx_vb_script_remote_call.vbs
' 4) Run the script by double clicking the hmsx_vb_script_remote_call.vbs file
