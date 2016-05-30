// Pipe.cpp: implementation of the CPipe class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Pipe.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPipe::CPipe()
{
	m_SoundIn.DataFromSoundIn = DataFromSoundIn;	// assign pointer to callback function
	m_SoundIn.m_pOwner = this;
	m_SoundOut.GetDataToSoundOut = GetDataToSoundOut;  // assign pointer to callback function
	m_SoundOut.m_pOwner = this;
	m_pFile = NULL;
}


void CPipe::WaveBufferProcess(CBuffer* buf)
{

}


CPipe::~CPipe()
{
// 	DWORD dwStatus = STILL_ACTIVE;
// 	m_SoundIn.PostThreadMessage(WM_QUIT, 0, 0);
// 	while(1)
// 	{
// 		VERIFY(::GetExitCodeThread(m_SoundIn.m_hThread, &dwStatus));
// 		
// 		if (dwStatus == STILL_ACTIVE)
// 			m_SoundIn.PostThreadMessage(WM_QUIT, 0, 0);
// 		else
// 			break;
// 	}
// 	
// 	dwStatus = STILL_ACTIVE;  
// 	m_SoundOut.PostThreadMessage(WM_QUIT, 0, 0);
// 	while(1)
// 	{
// 		VERIFY(::GetExitCodeThread(m_SoundOut.m_hThread, &dwStatus));
// 		
// 		if (dwStatus == STILL_ACTIVE)
// 			m_SoundOut.PostThreadMessage(WM_QUIT, 0, 0);
// 		else
// 			break;
// 	}
}

void CPipe::DataFromSoundIn(CBuffer* buffer, void* Owner)
{
	//((CPipe*) Owner)->WriteSoundDataToFile(buffer);
	if(buffer->ByteLen > 0)
	{
		((CPipe*) Owner)->WaveBufferProcess(buffer);
	}
}

void CPipe::WriteSoundDataToFile(CBuffer* buffer)
{
	if(m_pFile)
	{
		if(!m_pFile->Write(buffer))
		{
			m_SoundIn.Stop();
			AfxMessageBox("Unable to write to file");
		}
	}
}

void CPipe::GetDataToSoundOut(CBuffer* buffer, void* Owner)
{
	((CPipe*) Owner)->ReadSoundDataFromFile(buffer);	
	if(buffer->ByteLen > 0)
	{
		((CPipe*) Owner)->WaveBufferProcess(buffer);
	}
}

void CPipe::ReadSoundDataFromFile(CBuffer* buffer)
{
	if(m_pFile)
	{
		if(!m_pFile->Read(buffer))
		{
			// enf of file -> tell the GUI
			OnEndOfPlayingFile();
			delete m_pFile;
			m_pFile = NULL;
		}
	}
}

void CPipe::StartRecording( WAVEFORMATEX* format)
{
	//m_pFile = new CSoundFile("sound1.wav", m_SoundIn.GetFormat());
	//if(m_pFile && m_pFile->IsOK())
	m_SoundIn.Start(format);
}

void CPipe::StopRecording()
{
	m_SoundIn.Stop();
	// close output file
	//if(m_pFile)
	//	delete m_pFile;
	//StopPlayingFromFile();
}

void CPipe::StartPlayingFromFile( CString fileName/*="sound1.wav"*/ )
{
	if (fileName)
	{
		m_pFile = new CSoundFile(fileName,NULL);
	}
	else
		m_pFile = new CSoundFile("sound1.wav",NULL);
	if(m_pFile && m_pFile->IsOK())
	{
		m_format=*m_pFile->GetFormat();
		m_SoundOut.Start(m_pFile->GetFormat());
	}
	else
		ErrorMsg("Unable to open file");
}

void CPipe::StopPlayingFromFile()
{
	m_SoundOut.Stop();
	// close output file
	if(m_pFile)
	{
		delete m_pFile;
		m_pFile = NULL;
	}
}

void CPipe::OnEndOfPlayingFile()
{
	// implement this function in the GUI to change things when EOF is reached
}


void CPipe::WriteMemDataToFile( CBuffer* buffer,CString fileName,const char *RecWord )
{
	CSoundFile csfile(fileName,m_SoundIn.GetFormat());
	if (!csfile.Write(buffer))
	{
		ErrorMsg("Memory wave data write failed!");
	}
}


void CPipe::StartPlayingFromMem()
{

}
