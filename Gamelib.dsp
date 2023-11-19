# Microsoft Developer Studio Project File - Name="Gamelib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Gamelib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Gamelib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Gamelib.mak" CFG="Gamelib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Gamelib - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Gamelib - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Gamelib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /profile /machine:I386

!ELSEIF  "$(CFG)" == "Gamelib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Gamelib - Win32 Release"
# Name "Gamelib - Win32 Debug"
# Begin Group "Gamelib"

# PROP Default_Filter ""
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Graphics Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameLib\Source\Bitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\GameLib\Source\DXBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\GameLib\Source\FXPalette.cpp
# End Source File
# Begin Source File

SOURCE=.\GameLib\Source\Sprite.cpp
# End Source File
# Begin Source File

SOURCE=.\GameLib\Source\Text.cpp
# End Source File
# End Group
# Begin Group "CPU Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameLib\Source\Memory.cpp
# End Source File
# End Group
# Begin Group "WinMain Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WinMain.cpp
# End Source File
# End Group
# Begin Group "Handler Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameLib\Source\DisplayHandler2D.cpp
# End Source File
# Begin Source File

SOURCE=.\GameLib\Source\DXDisplayHandler2D.cpp
# End Source File
# Begin Source File

SOURCE=.\GameLib\Source\DXInputHandler.cpp
# End Source File
# End Group
# Begin Group "Base Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameLib\Source\Game2D.cpp
# End Source File
# Begin Source File

SOURCE=.\GameLib\Source\Timer.cpp
# End Source File
# Begin Source File

SOURCE=.\GameLib\Source\Wnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameLib\Source\WndStage.cpp
# End Source File
# End Group
# Begin Group "Control Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameLib\Source\MapCtl.cpp
# End Source File
# End Group
# Begin Group "Object Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameLib\Source\Cursor.cpp
# End Source File
# Begin Source File

SOURCE=.\GameLib\Source\Map.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\BetsStage.cpp
# End Source File
# Begin Source File

SOURCE=.\Game.cpp
# End Source File
# Begin Source File

SOURCE=.\Horse.cpp
# End Source File
# Begin Source File

SOURCE=.\GameLib\Source\Layer.cpp
# End Source File
# Begin Source File

SOURCE=.\MainStage.cpp
# End Source File
# Begin Source File

SOURCE=.\GameLib\Source\MapLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Player.cpp
# End Source File
# Begin Source File

SOURCE=.\Race.cpp
# End Source File
# Begin Source File

SOURCE=.\Scoreboard.cpp
# End Source File
# Begin Source File

SOURCE=.\ScoreLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowHorsesStage.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowTrackStage.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowWinsStage.cpp
# End Source File
# Begin Source File

SOURCE=.\SpriteLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Track.cpp
# End Source File
# Begin Source File

SOURCE=.\GameLib\Source\View.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Graphics Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameLib\Header\Bitmap.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\DXBitmap.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\FXPalette.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\Sprite.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\Text.h
# End Source File
# End Group
# Begin Group "CPU Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameLib\Header\DataTypes.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\Memory.h
# End Source File
# End Group
# Begin Group "WinMain Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WinMain.h
# End Source File
# End Group
# Begin Group "DirectX Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DirectX\Header\DDraw.h
# End Source File
# Begin Source File

SOURCE=.\DirectX\Header\Dinput.h
# End Source File
# End Group
# Begin Group "Handler Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameLib\Header\DisplayHandler2D.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\DXDisplayHandler2D.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\DXInputHandler.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\InputHandler.h
# End Source File
# End Group
# Begin Group "Input Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameLib\Header\Input.h
# End Source File
# End Group
# Begin Group "Base Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameLib\Header\DXGame2D.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\Formulas.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\Game2D.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\Stage.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\Timer.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\Transition.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\Wnd.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\WndStage.h
# End Source File
# End Group
# Begin Group "Control Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameLib\Header\MapCtl.h
# End Source File
# End Group
# Begin Group "Object Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameLib\Header\Cursor.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\Map.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\Object.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\GameLib\Header\Layer.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\MapLayer.h
# End Source File
# Begin Source File

SOURCE=.\Race.h
# End Source File
# Begin Source File

SOURCE=.\Scoreboard.h
# End Source File
# Begin Source File

SOURCE=.\ScoreLayer.h
# End Source File
# Begin Source File

SOURCE=.\ShowHorsesStage.h
# End Source File
# Begin Source File

SOURCE=.\ShowTrackStage.h
# End Source File
# Begin Source File

SOURCE=.\ShowWinsStage.h
# End Source File
# Begin Source File

SOURCE=.\GameLib\Header\View.h
# End Source File
# End Group
# Begin Group "Librarie Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DirectX\Libraries\dxguid.lib
# End Source File
# Begin Source File

SOURCE=.\DirectX\Libraries\Dinput.lib
# End Source File
# Begin Source File

SOURCE=.\DirectX\Libraries\ddraw.lib
# End Source File
# End Group
# Begin Source File

SOURCE=.\BetsStage.h
# End Source File
# Begin Source File

SOURCE=.\Game.h
# End Source File
# Begin Source File

SOURCE=.\Horse.h
# End Source File
# Begin Source File

SOURCE=.\MainStage.h
# End Source File
# Begin Source File

SOURCE=.\Player.h
# End Source File
# Begin Source File

SOURCE=.\SpriteLayer.h
# End Source File
# Begin Source File

SOURCE=.\Track.h
# End Source File
# End Group
# End Target
# End Project
