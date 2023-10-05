# This example shows how a connection to a hMailServer X remote 
# instance can be done using the Microsoft Powershell scripting language
# Please check also the build instructions at the end of file.  


$obj = New-Object -ComObject hmailxcomLib.clientapi
$obj.sayhello()
$obj = $null

# Build instructions: 
# 1) Make sure that hmailxcom.dll is registered (type regsvr32 hmailxcom.dll if not)
# 2) Open a Windows Powershell command prompt
# 3) Run the script by typing: .\hmsx_powershell_remote_call.ps1



