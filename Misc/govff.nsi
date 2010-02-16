# gOVFF NSIS Script
!define VERSION "1.9.7"

# include modern UI2
!include MUI2.nsh

Outfile "gOVFF-${VERSION}-Installer.exe"
Name "OVFFåF½¼¦ÌÂ½Ä¶¾÷"
InstallDir "$PROGRAMFILES\gOVFF"
RequestExecutionLevel admin

# MUI2 settings
!define MUI_ABORTWARNING

# Installer pages
Var SMFolder

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "COPYING.txt"
!insertmacro MUI_PAGE_DIRECTORY
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "gOVFF"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
!insertmacro MUI_PAGE_STARTMENU Application $SMFolder
!insertmacro MUI_PAGE_INSTFILES
!define MUI_FINISHPAGE_RUN "$INSTDIR\OVFFåF½¼¦ÌÂ½Ä¶¾÷.exe"
!insertmacro MUI_PAGE_FINISH

# Uninstaller pages
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

# set Languages
!insertmacro MUI_LANGUAGE "English"
 
# install section
Section
# Workaround for shortcut deletion bug on Vista/7
# See http://nsis.sourceforge.net/Shortcuts_removal_fails_on_Windows_Vista
# for more information
SetShellVarContext all
setOutPath $INSTDIR\database
File database\boshiamy.db
File database\README.txt
setOutPath $INSTDIR
File OVFFåF½¼¦ÌÂ½Ä¶¾÷.exe
File COPYING.txt
File mingwm10.dll
File libgcc_s_dw2-1.dll
File QtCore4.dll
File QtGui4.dll
File Source_Code.url

# Create uninstaller
WriteUninstaller $INSTDIR\uninstall.exe

# Create shortcuts
CreateSHortCut "$DESKTOP\OVFFåF½¼¦ÌÂ½Ä¶¾÷.lnk" \
	"$INSTDIR\OVFFåF½¼¦ÌÂ½Ä¶¾÷.exe"
!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
	CreateDirectory "$SMPROGRAMS\$SMFolder"
	CreateSHortCut "$SMPROGRAMS\$SMFolder\OVFFåF½¼¦ÌÂ½Ä¶¾÷.lnk" \
		"$INSTDIR\OVFFåF½¼¦ÌÂ½Ä¶¾÷.exe"
	CreateShortCut "$SMPROGRAMS\$SMFolder\Uninstall.lnk" \
		"$INSTDIR\Uninstall.exe"
!insertmacro MUI_STARTMENU_WRITE_END

# Write Registry
WriteRegStr HKLM \
	"Software\Microsoft\Windows\CurrentVersion\Uninstall\gOVFF" \
	"DisplayIcon" "$INSTDIR\OVFFåF½¼¦ÌÂ½Ä¶¾÷.exe"
WriteRegStr HKLM \
	"Software\Microsoft\Windows\CurrentVersion\Uninstall\gOVFF" \
	"DisplayName" "OVFFåF½¼¦ÌÂ½Ä¶¾÷"
WriteRegStr HKLM \
	"Software\Microsoft\Windows\CurrentVersion\Uninstall\gOVFF" \
	"DisplayVersion" "${VERSION}"
WriteRegStr HKLM \
	"Software\Microsoft\Windows\CurrentVersion\Uninstall\gOVFF" \
	"Publisher" "AZ (Wei-Ning Huang)"
WriteRegStr HKLM \
	"Software\Microsoft\Windows\CurrentVersion\Uninstall\gOVFF" \
	"UninstallString" "$\"$INSTDIR\uninstall.exe$\""
WriteRegStr HKLM \
	"Software\Microsoft\Windows\CurrentVersion\Uninstall\gOVFF" \
	"URLInfoAbout" "http://github.com/Aitjcize/govff"
SectionEnd

# uninstall section
Section "uninstall"
# Workaround for shortcut deletion bug on Vista/7
# See http://nsis.sourceforge.net/Shortcuts_removal_fails_on_Windows_Vista
# for more information
SetShellVarContext all

rmdir /r $INSTDIR
Delete "$DESKTOP\OVFFåF½¼¦ÌÂ½Ä¶¾÷.lnk"
!insertmacro MUI_STARTMENU_GETFOLDER Application $SMFolder
rmdir /r "$SMPROGRAMS\$SMFolder"
DeleteRegKey HKLM \
"Software\Microsoft\Windows\CurrentVersion\Uninstall\gOVFF"

DeleteRegKey /ifempty HKCU "gOVFF"
sectionEnd
