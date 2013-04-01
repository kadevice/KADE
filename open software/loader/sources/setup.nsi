Name "KADE Loader"

# Variables
Var StartMenuGroup

# Defines
!define URL http://kadevice.com/
!define PRODUCTNAME "KADE Loader"
!define BITMAP "images\banner.bmp"
!define REGKEY "SOFTWARE\$(^Name)"
!define VERSION 1.0
!include nsis.tmp
!define COMPANY KADE
!define PATCH 0

# MUI defines/overides
!define MUI_WELCOMEPAGE_TITLE "${PRODUCTNAME} Setup Wizard"
!define MUI_WELCOMEPAGE_TEXT "This wizard will guide you through the installation of ${PRODUCTNAME} (version ${PRODUCTVERSION}).\n\n\n\nIt is recommended that you close all other applications before continuing.\n\nClick Install to start the installation of the KADE Loader."
!define MUI_PAGE_CUSTOMFUNCTION_PRE WelcomePageSetupLinkPre
!define MUI_PAGE_CUSTOMFUNCTION_SHOW WelcomePageSetupLinkShow

!define MUI_WELCOMEFINISHPAGE_BITMAP "${BITMAP}"
!define MUI_FINISHPAGE_TEXT "KADE Loader has been successfully installed.\nYou can go ahead and start it up.\n\nGet ready for some kick ass gaming with your KADE device."
!define MUI_FINISHPAGE_SHOWREADME_NOTCHECKED
!define MUI_FINISHPAGE_RUN "$INSTDIR\loader.exe"
!define MUI_FINISHPAGE_RUN_TEXT "Start KADE Loader"
!define MUI_ICON "images\icons.ico"
!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_STARTMENUPAGE_REGISTRY_ROOT HKLM
!define MUI_STARTMENUPAGE_NODISABLE 
!define MUI_STARTMENUPAGE_REGISTRY_KEY ${REGKEY}
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME StartMenuGroup
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "$(^Name)"
!define MUI_UNICON "images\icons.ico"
!define MUI_UNFINISHPAGE_NOAUTOCLOSE

OutFile setup.exe

# Included files
!include Sections.nsh
!include MUI.nsh
!include Library.nsh
!include "LogicLib.nsh"

# Installer pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE license.txt
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_STARTMENU Application $StartMenuGroup
!insertmacro MUI_PAGE_INSTFILES
!define MUI_FINISHPAGE_TITLE "Thank you for installing \n${PRODUCTNAME}"
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

# Installer languages
!insertmacro MUI_LANGUAGE English

# Installer attributes
InstallDir "$PROGRAMFILES\KADE Loader"
CRCCheck on
XPStyle on
ShowInstDetails show
VIProductVersion ${PRODUCTVERSION}
VIAddVersionKey ProductName "$(^Name)"
VIAddVersionKey ProductVersion "${VERSION}"
VIAddVersionKey CompanyName "${COMPANY}"
VIAddVersionKey CompanyWebsite "${URL}"
VIAddVersionKey FileVersion "${VERSION}"
VIAddVersionKey FileDescription ""
VIAddVersionKey LegalCopyright ""
InstallDirRegKey HKLM "${REGKEY}" Path
ShowUninstDetails show

;# Installer sections
Section -Main SEC0000	; Set Section properties
	SetOverwrite on
  SetShellVarContext all

# Install the files
  SetOutPath $INSTDIR
	File dist\*.exe
	File dist\*.dll
	File dist\release.txt
	File dist\version.txt	
	File dist\license.txt	
		
  SetOutPath "$INSTDIR\images"
	File /r dist\images\*.*
  SetOutPath "$INSTDIR\documents"
	File /r dist\documents\*.*
  SetOutPath "$INSTDIR\templates"
	File /r dist\templates\*.*
  SetOutPath "$INSTDIR\programmer"
	File /r dist\programmer\*.*
	
# Minimus drivers (for manual install)
  SetOutPath "$INSTDIR\drivers\minimus avr"
	File /r dist\programmer\dfu\*.cat
	File /r dist\programmer\dfu\*.inf
	File /r dist\programmer\dfu\*.sys
	File /r dist\programmer\dfu\*.dll
	
# data
  SetOutPath "$APPDATA\KADE Loader"
	File dist\data
	File /r dist\templates\css
	File /r dist\templates\images
	File /r dist\templates\map\*.*
	
# create information file
  SetOutPath "$APPDATA\KADE Loader\"
 	FileOpen $0 "version" w
  FileWrite $0 $INSTDIR
	FileSeek $0 0 END
  FileWriteByte $0 "13"
  FileWriteByte $0 "10"
  FileWrite $0 ${PRODUCTVERSION}
	FileClose $0
	
# Set access rights
  AccessControl::GrantOnFile "$APPDATA\KADE Loader" "(S-1-5-32-545)" "FullAccess"
  AccessControl::GrantOnFile "$APPDATA\KADE Loader\documents" "(S-1-5-32-545)" "FullAccess"
  AccessControl::GrantOnFile "$APPDATA\KADE Loader\data" "(S-1-5-32-545)" "FullAccess"
  AccessControl::GrantOnFile "$INSTDIR" "(S-1-5-32-545)" "FullAccess"
  AccessControl::GrantOnFile "$INSTDIR\images" "(S-1-5-32-545)" "FullAccess"
  AccessControl::GrantOnFile "$INSTDIR\documents" "(S-1-5-32-545)" "FullAccess"
	AccessControl::GrantOnFile "$INSTDIR\programmer\dfu\dfu-programmer.exe" "(S-1-5-32-545)" "FullAccess"
  AccessControl::GrantOnFile "$INSTDIR\programmer\avrdude\avrdude.exe" "(S-1-5-32-545)" "FullAccess"
  AccessControl::GrantOnFile "$INSTDIR\programmer\bootloadHID\commandline\bootloadHID.exe" "(S-1-5-32-545)" "FullAccess"
		
# Install Atmel Drivers	
# create dpinst.xml file
  SetOutPath "$INSTDIR"
 	FileOpen $0 "dpinst.xml" w
  FileWrite $0 '<?xml version="1.0"?>'
	FileWrite $0 '<dpInst>'
	FileWrite $0 '<enableNotListedLanguages/>'
;	FileWrite $0 '<language code="0x0409">'
	FileWrite $0 '<dpinstTitle>KADE Driver Installation</dpinstTitle>'
	FileWrite $0 '<welcomeTitle>Welcome to the KADE Driver Installation Wizard</welcomeTitle>'
	FileWrite $0 '<welcomeIntro>This wizard will install the system drivers required for your KADE device.</welcomeIntro>'
	FileWrite $0 '<installHeaderTitle>Installing the drivers for your KADE device...</installHeaderTitle>'
	FileWrite $0 '<finishTitle>KADE drivers are now installed.</finishTitle>'
	FileWrite $0 '<finishText>Drivers have been successfully installed for your KADE device.</finishText>'
;	FileWrite $0 '</language>'
	FileWrite $0 '<icon>$INSTDIR\images\icons.ico</icon>'
	FileWrite $0 '<watermarkPath>$INSTDIR\images\banner.bmp</watermarkPath>'
	FileWrite $0 '</dpInst>'
	FileClose $0

  IfFileExists $WINDIR\SYSWOW64\*.* Is64bit Is32bit
  Is32bit:
    ExecWait 'dpinst /F /LM /PATH "$INSTDIR\programmer\dfu"'
		Goto Endbit
  Is64bit:
    ExecWait 'dpinst64 /F /LM /PATH "$INSTDIR\programmer\dfu"'
	Endbit:

SectionEnd

######################################################################

Function WelcomePageSetupLinkPre
  SetOutPath "$TEMP"
  File "dist\release.txt"

  !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Settings" "Numfields" "4" ; increase counter
  !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 3" "Bottom" "107" ; limit size of the upper label
  !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Type" "Link"
  !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Text" "View release notes" 
  !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "State" "file:///$TEMP/release.txt"
  !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Left" "118"
  !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Right" "315"
  !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Top" "128"
  !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Bottom" "137"
FunctionEnd
 
Function WelcomePageSetupLinkShow
  Push $0
 
  GetDlgItem $0 $MUI_HWND 1203
  SetCtlColors $0 "0000FF" "FFFFFF"
  ; underline font
  CreateFont $1 "$(^Font)" "$(^FontSize)" "400" /UNDERLINE 
  SendMessage $0 ${WM_SETFONT} $1 1 
  Pop $0
FunctionEnd

######################################################################


Section -Dependencies
SectionEnd

Section -post SEC0001
    WriteRegStr HKLM "${REGKEY}" Path $INSTDIR
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
    !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    SetOutPath $INSTDIR
		SetShellVarContext current
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\KADE Loader.lnk" $INSTDIR\loader.exe
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\Uninstall.lnk" $INSTDIR\uninstall.exe
		SetShellVarContext all
    !insertmacro MUI_STARTMENU_WRITE_END

    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayName "$(^Name)"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayVersion "${VERSION}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" Publisher "${COMPANY}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" URLInfoAbout "${URL}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayIcon $INSTDIR\uninstall.exe
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" UninstallString $INSTDIR\uninstall.exe
    WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" NoModify 1
    WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" NoRepair 1

    SetOutPath $INSTDIR
    CreateShortCut "$DESKTOP\KADE Loader.lnk" "$INSTDIR\loader.exe" ""
		
SectionEnd

# Macro for selecting uninstaller sections
!macro SELECT_UNSECTION SECTION_NAME UNSECTION_ID
    Push $R0
    ReadRegStr $R0 HKLM "${REGKEY}\Components" "${SECTION_NAME}"
    StrCmp $R0 1 0 next${UNSECTION_ID}
    !insertmacro SelectSection "${UNSECTION_ID}"
    GoTo done${UNSECTION_ID}
next${UNSECTION_ID}:
    !insertmacro UnselectSection "${UNSECTION_ID}"
done${UNSECTION_ID}:
    Pop $R0
!macroend

# Uninstaller sections
Section /o -un.Main UNSEC0000   
SectionEnd

Section -un.post UNSEC0001
    SetShellVarContext all
    		
		# remove the application
    RmDir /r "$APPDATA\KADE Loader"
    RmDir /r /REBOOTOK "$APPDATA\KADE Loader"
    RmDir /r /REBOOTOK "$INSTDIR\images"
    RmDir /r /REBOOTOK "$INSTDIR\documents"
    RmDir /r /REBOOTOK "$INSTDIR\programmer"
    RmDir /r /REBOOTOK "$INSTDIR"

		DeleteRegValue HKLM "${REGKEY}\Components" Main
    DeleteRegValue HKLM "Software\Microsoft\Windows\CurrentVersion\Run" "KADE Loader"

    DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)"
		
		SetShellVarContext current
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\Uninstall.lnk"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\KADE Loader.lnk"
		Delete /REBOOTOK "$DESKTOP\KADE Loader.lnk"
		
	  SetShellVarContext all		
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\Uninstall.lnk"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\KADE Loader.lnk"
		Delete /REBOOTOK "$DESKTOP\KADE Loader.lnk"

		Delete /REBOOTOK $INSTDIR\uninstall.exe
    DeleteRegValue HKLM "${REGKEY}" StartMenuGroup
    DeleteRegValue HKLM "${REGKEY}" Path
    DeleteRegKey /IfEmpty HKLM "${REGKEY}\Components"
    DeleteRegKey /IfEmpty HKLM "${REGKEY}"
		SetShellVarContext current
    RmDir /REBOOTOK $SMPROGRAMS\$StartMenuGroup
		SetShellVarContext all
    RmDir /REBOOTOK $SMPROGRAMS\$StartMenuGroup
    RmDir /REBOOTOK $INSTDIR
SectionEnd

# Installer functions
Function .onInit
	  SetShellVarContext all
		
    InitPluginsDir
		#Check if install is valid
  	IfFileExists "$APPDATA\KADE Loader\version" 0 +3		
      MessageBox MB_OK "KADE Loader is already installed on your system.  Please check for updates in KADE Loader help menu." /SD IDOK
      Quit			


FunctionEnd

# Uninstaller functions
Function un.onInit
    ReadRegStr $INSTDIR HKLM "${REGKEY}" Path
    !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuGroup
    !insertmacro SELECT_UNSECTION Main ${UNSEC0000}
FunctionEnd