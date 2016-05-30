# Microsoft Developer Studio Project File - Name="SRControl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=SRControl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SRControl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SRControl.mak" CFG="SRControl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SRControl - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "SRControl - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SRControl - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_CY_DEBUG_" /FR /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 nafxcw.lib libcmt.lib ../Release/LoadNlpGmm.obj ../Release/nlp.obj ../Release/nlpgmmRecognition.obj ../Release/vad.obj ../Release/common.obj ../Release/dspAIC.obj ../Release/realtimefrontend.obj ../Release/datadef.obj ../Release/SpeechCollectionDlg.obj ../Release/Pipe.obj ../Release/SoundIn.obj ../Release/SoundOut.obj ../Release/SoundFile.obj ../Release/SoundBase.obj ../Release/Buffer.obj ../Release/PtrFifo.obj ../Release/errorprint.obj ../Release/DeltaFeature.obj ../Release/FeatureTransform.obj ../Release/fft.obj ../Release/mfcc.obj ../Release/FeatureExtraction.obj /nologo /subsystem:console /machine:I386 /nodefaultlib:"nafxcw.lib libcmt.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "SRControl - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MT /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_CY_DEBUG_" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ../Debug/nlp.obj ../Debug/nlpgmmRecognition.obj ../Debug/LoadNlpGmm.obj ../Debug/DeltaFeature.obj ../Debug/FeatureTransform.obj ../Debug/fft.obj ../Debug/mfcc.obj ../Debug/FeatureExtraction.obj ../Debug/datadef.obj ../Debug/vad.obj ../Debug/common.obj ../Debug/dspAIC.obj ../Debug/realtimefrontend.obj ../Debug/SpeechCollectionDlg.obj ../Debug/Pipe.obj ../Debug/SoundIn.obj ../Debug/SoundOut.obj ../Debug/SoundFile.obj ../Debug/SoundBase.obj ../Debug/Buffer.obj ../Debug/PtrFifo.obj ../Debug/errorprint.obj /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"LIBCD.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "SRControl - Win32 Release"
# Name "SRControl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\SRControl.cpp
# End Source File
# Begin Source File

SOURCE=.\SRControl.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\wrapper.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SRControl.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\wrapper.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\SpeechCollection\res\SpeechCollection.ico
# End Source File
# Begin Source File

SOURCE=.\res\SpeechCollection.ico
# End Source File
# Begin Source File

SOURCE=..\SpeechCollection\res\SpeechCollection.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
