@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by DEMIST ANALYSER.HPJ. >"hlp\DEMIST Analyser.hm"
echo. >>"hlp\DEMIST Analyser.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\DEMIST Analyser.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\DEMIST Analyser.hm"
echo. >>"hlp\DEMIST Analyser.hm"
echo // Prompts (IDP_*) >>"hlp\DEMIST Analyser.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\DEMIST Analyser.hm"
echo. >>"hlp\DEMIST Analyser.hm"
echo // Resources (IDR_*) >>"hlp\DEMIST Analyser.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\DEMIST Analyser.hm"
echo. >>"hlp\DEMIST Analyser.hm"
echo // Dialogs (IDD_*) >>"hlp\DEMIST Analyser.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\DEMIST Analyser.hm"
echo. >>"hlp\DEMIST Analyser.hm"
echo // Frame Controls (IDW_*) >>"hlp\DEMIST Analyser.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\DEMIST Analyser.hm"
REM -- Make help for Project DEMIST ANALYSER


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\DEMIST Analyser.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\DEMIST Analyser.hlp" goto :Error
if not exist "hlp\DEMIST Analyser.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\DEMIST Analyser.hlp" Debug
if exist Debug\nul copy "hlp\DEMIST Analyser.cnt" Debug
if exist Release\nul copy "hlp\DEMIST Analyser.hlp" Release
if exist Release\nul copy "hlp\DEMIST Analyser.cnt" Release
echo.
goto :done

:Error
echo hlp\DEMIST Analyser.hpj(1) : error: Problem encountered creating help file

:done
echo.
