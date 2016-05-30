// Pipe.h: interface for the CPipe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PIPE_H__71D36BFB_9EC3_4FEB_91BB_0178A52B8B7B__INCLUDED_)
#define AFX_PIPE_H__71D36BFB_9EC3_4FEB_91BB_0178A52B8B7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "soundin.h"
#include "soundout.h"
#include "soundfile.h"
#include "ptrFIFO.h"


class CPipe
{
public:
	CPipe();
	virtual ~CPipe(); 

	virtual void OnEndOfPlayingFile();

public:
	void LoadWaveFile( CString fileName);
	WAVEFORMATEX m_format;
	void StartPlayingFromMem();
	void WriteMemDataToFile(CBuffer* buffer,CString fileName,const char *RecWord);
	virtual void WaveBufferProcess(CBuffer* buf);

	void StopPlayingFromFile();
	void StartPlayingFromFile(CString fileName="sound1.wav");
	void StopRecording();
	void StartRecording(WAVEFORMATEX* format=NULL);
	void WriteSoundDataToFile(CBuffer* buffer);
	void ReadSoundDataFromFile(CBuffer* buffer);
	static void DataFromSoundIn(CBuffer* buffer, void* Owner);
	static void GetDataToSoundOut(CBuffer* buffer, void* Owner);		

private:
	CPtrFIFO m_FIFOFull;	// FIFO holding pointers to buffers with sound
	CPtrFIFO m_FIFOEmpty;	// FIFO holding pointers to empty buffers that can be reused

	CSoundFile* m_pFile;
	CSoundOut	m_SoundOut;
	CSoundIn	m_SoundIn;
};

#endif // !defined(AFX_PIPE_H__71D36BFB_9EC3_4FEB_91BB_0178A52B8B7B__INCLUDED_)
