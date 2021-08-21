
#define MyAppName "ͼƬѹ��"
#define MyAppVerName "ͼƬѹ�� 1.5"
#define MyAppPublisher "Yong++"
#define MyAppExeName "tinypng.exe"

[Setup]
; ע: AppId��ֵΪ������ʶ��Ӧ�ó���
; ��ҪΪ������װ����ʹ����ͬ��AppIdֵ��
; (�����µ�GUID����� ����|��IDE������GUID��)
AppId={{3EB7DACF-EA48-429F-B4E6-76826000E6E4}
AppName={#MyAppName}
AppVerName={#MyAppVerName}
AppPublisher={#MyAppPublisher}
DefaultDirName={pf}\tinypng
DefaultGroupName={#MyAppName}
OutputDir=D:\workspace\qt\tinypng\
OutputBaseFilename=installer
SetupIconFile=D:\workspace\qt\tinypng\tinypng\logo.ico
Compression=lzma2/max
SolidCompression=yes
SignTool=sha1 timestamp

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "D:\workspace\qt\tinypng\Release\tinypng.exe"; DestDir: "{app}"; Flags: ignoreversion signonce
Source: "D:\workspace\qt\tinypng\Release\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; ע��: ��Ҫ���κι���ϵͳ�ļ���ʹ�á�Flags: ignoreversion��

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#MyAppName}}"; Flags: nowait postinstall skipifsilent

[Code]
procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
begin
if CurUninstallStep = usUninstall then
        RegDeleteKeyIncludingSubkeys(HKEY_CURRENT_USER, 'Software\lane')
end;
