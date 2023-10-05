program hmsx_delphi_remote_call;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  System.SysUtils,
  hmailxcomLib_TLB in '..\22.0\Imports\hmailxcomLib_TLB.pas';

var
  obj: Iclientapi;

begin

  try

     obj := Coclientapi.Create;
     obj.sayhello;

  except
    on E: Exception do
      Writeln(E.ClassName, ': ', E.Message);
  end;
end.
