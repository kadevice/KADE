Name "KADE Loader" 

# Variables
Var PreviousVersion
Var AppDirectory

# Defines
!define REGKEY "SOFTWARE\$(^Name)"
!define VERSION 1.0
!include "nsis.tmp"
!define COMPANY KADE
!define URL http://kadevice.com/
!define BITMAP "images\banner.bmp"

# MUI defines
!define MUI_WELCOMEFINISHPAGE_BITMAP "${BITMAP}"
!define MUI_ICON "images\icons.ico"
!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_UNICON "images\icons.ico"
!define MUI_UNFINISHPAGE_NOAUTOCLOSE

# Included files
!include Sections.nsh
!include MUI.nsh
!include Library.nsh

# Installer pages
!define MUI_WELCOMEPAGE_TITLE 'Welcome to the KADE Loader Update Wizard'
!define MUI_WELCOMEPAGE_TEXT 'You will now be updated to KADE Loader v${PRODUCTVERSION}.\n\nIt is recommended that you close all other applications before continuing.\n\nClick Install to start the software update.'
!define MUI_PAGE_CUSTOMFUNCTION_PRE WelcomePageSetupLinkPre
!define MUI_PAGE_CUSTOMFUNCTION_SHOW WelcomePageSetupLinkShow
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

# Installer languages
!insertmacro MUI_LANGUAGE English

# Installer attributes
OutFile update.exe

CRCCheck on
XPStyle on
ShowInstDetails show
VIProductVersion ${PRODUCTVERSION}

;# Installer sections
Section -Main SEC0000	; Set Section properties	
  SetOverwrite on
  SetShellVarContext all

# install the files
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
SectionEnd


Section -post SEC0001
SectionEnd

# Installer functions
Function .onInit
  InitPluginsDir
		
# Check if update is necessary
  SetShellVarContext all
	FileOpen $R0 "$APPDATA\KADE Loader\version" r
  FileRead $R0 $AppDirectory
  FileRead $R0 $PreviousVersion
  FileClose $R0
  
StrCpy $INSTDIR $AppDirectory -2
	StrCmp $INSTDIR "" lbl_nodir lbl_check
	
	lbl_nodir:
  MessageBox MB_OK "The KADE Loader version information is missing from your system.  Update is not possible. You will need to perform a full install to get the updates."  /SD IDOK
  Quit
	
	lbl_check:
  StrCmp $PreviousVersion "" lbl_noprev lbl_prev

  lbl_noprev:
  MessageBox MB_OK "KADE Loader was not found on your system.  You need to perform a full install." /SD IDOK
  Quit

  lbl_prev:
  StrCmp $PreviousVersion ${PRODUCTVERSION} lbl_current lbl_older
	
	lbl_current:
  MessageBox MB_OK "No update is required.  You are currently using the latest version of KADE Loader." /SD IDOK
  Quit
	
	lbl_older:
  #go ahead and update
FunctionEnd

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
  !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Top" "108"
  !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Bottom" "117"
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