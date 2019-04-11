#include "Engine.h"

#include <iostream>
#include <chrono>

#include <iostream>
#include <fstream>
#include <cstring>
#include <AL/al.h>
#include <AL/alc.h>

bool isBigEndian()
{
	int a = 1;
	return !((char*)&a)[0];
}

int convertToInt(char* buffer, int len)
{
	int a = 0;
	if (!isBigEndian())
		for (int i = 0; i < len; i++)
			((char*)&a)[i] = buffer[i];
	else
		for (int i = 0; i < len; i++)
			((char*)&a)[3 - i] = buffer[i];
	return a;
}

char* loadWAV(const char* path, int* channels, int* samplerate, int* bps, int* size, unsigned* alformat)
{
	char buffer[4];
	std::ifstream in(path, std::ios::binary);
	in.read(buffer, 4);
	if (strncmp(buffer, "RIFF", 4) != 0)
	{
		std::cout << path << " Is not a valid WAVE File" << std::endl;
		return nullptr;
	}
	in.read(buffer, 4);
	in.read(buffer, 4); 
	in.read(buffer, 4); 
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	*channels = convertToInt(buffer, 2);
	in.read(buffer, 4);
	*samplerate = convertToInt(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	*bps = convertToInt(buffer, 2);
	in.read(buffer, 4);
	in.read(buffer, 4);
	*size = convertToInt(buffer, 4);
	char* data = new char[*size];
	in.read(data, *size);

	if (*channels == 1)
		*alformat = (*bps == 8 ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16);	
	else
		*alformat = (*bps == 8 ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16);	

	return data;
}

#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
static void dispatch_main(void* fp)
{
	std::function<void()>* func = (std::function<void()>*)fp;
	(*func)();
}
#endif

Engine::Engine()
	:m_nPreviousMouseX(0), m_nPreviousMouseY(0), m_nMouseOffsetX(0), m_nMouseOffsetY(0)
{
	p_Window = new Window(960, 540, "GLWindow");
	p_Renderer = new SimpleRenderer(p_Window);
}

Engine::~Engine()
{
	delete p_Renderer;
	delete p_Window;
}

void Engine::Start()
{
	int nCount = 0;

	m_nPreviousMouseX = GetMouseX();
	m_nPreviousMouseY = GetMouseY();

	float fTime = 0.f, fFrames = 0.f, fDeltaTime = 0.f, fHighestDelta = 0.f;
	auto previousTime = std::chrono::high_resolution_clock::now(), currentTime = previousTime;
//----------------------------------------------------------------------------------------------------------------------------------------------------------
	// Device Setup
	ALCdevice* device = alcOpenDevice(NULL);
	if (device == NULL)	
		std::cout << "cannot open sound card" << std::endl;		
	
	ALCcontext* context = alcCreateContext(device, NULL);
	if (context == NULL)	
		std::cout << "cannot open context" << std::endl;		
	
	alcMakeContextCurrent(context);

	// Loading WAV
	int channel, sampleRate, bps, size;
	unsigned format;
	char* data = loadWAV("Resources/Sounds/sound.wav", &channel, &sampleRate, &bps, &size, &format);

	// Create Buffers
	unsigned bufferid;
	alGenBuffers(1, &bufferid);
	alBufferData(bufferid, format, data, size, sampleRate);

	// Set up Listener
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	alListener3f(AL_POSITION, 0, 0, 0);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerfv(AL_ORIENTATION, listenerOri);

	// Create Source
	unsigned sourceid;
	alGenSources(1, &sourceid);
	alSourcei(sourceid, AL_BUFFER, bufferid); // Bind Buffer
	alSourcei(sourceid, AL_LOOPING, AL_TRUE);
	alSourcef(sourceid, AL_PITCH, 1);
	alSourcef(sourceid, AL_GAIN, 1);
	alSource3f(sourceid, AL_POSITION, 0, 0, -100);
	alSource3f(sourceid, AL_VELOCITY, 0, 0, 0);

	// Distance Model
	alDistanceModel(AL_EXPONENT_DISTANCE);
	alSourcef(sourceid, AL_ROLLOFF_FACTOR, 1.f);
	alSourcef(sourceid, AL_REFERENCE_DISTANCE, 70.f);
	alSourcef(sourceid, AL_MAX_DISTANCE, 500.f);

	alSourcePlay(sourceid);
	alSourcePause(sourceid);
	alSourcePlay(sourceid);
	alSourceStop(sourceid);
	alSourcePlay(sourceid);
//----------------------------------------------------------------------------------------------------------------------------------------------------------
	Begin();
#ifdef EMSCRIPTEN
	std::function<void()> mainLoop = [&]()
#else
	while (p_Window->Open())
#endif 
	{
		currentTime = std::chrono::high_resolution_clock::now();
		p_Window->PollEvents();
		p_Renderer->Clear();
			   
		m_nMouseOffsetX = GetMouseX() - m_nPreviousMouseX;
		m_nMouseOffsetY = GetMouseY() - m_nPreviousMouseY;

		m_nPreviousMouseX = GetMouseX();
		m_nPreviousMouseY = GetMouseY();

		alListener3f(AL_POSITION, p_Renderer->GetCamera3D()->GetPosition().x, p_Renderer->GetCamera3D()->GetPosition().y, p_Renderer->GetCamera3D()->GetPosition().z);
		listenerOri[0] = -(p_Renderer->GetCamera3D()->m_Direction.x);
		listenerOri[1] = -(p_Renderer->GetCamera3D()->m_Direction.y);
		listenerOri[2] = -(p_Renderer->GetCamera3D()->m_Direction.z);
		listenerOri[3] = p_Renderer->GetCamera3D()->m_WorldUp.x;
		listenerOri[4] = p_Renderer->GetCamera3D()->m_WorldUp.y;
		listenerOri[5] = p_Renderer->GetCamera3D()->m_WorldUp.z;
		alListenerfv(AL_ORIENTATION, listenerOri);
		//std::cout << p_Renderer->GetCamera3D()->m_WorldUp.x << p_Renderer->GetCamera3D()->m_WorldUp.y << p_Renderer->GetCamera3D()->m_WorldUp.z << std::endl;
		//std::cout << p_Renderer->GetCamera3D()->m_Direction.x << p_Renderer->GetCamera3D()->m_Direction.y << p_Renderer->GetCamera3D()->m_Direction.z << std::endl;
		

		Tick(fDeltaTime);

		p_Renderer->Draw();
		p_Window->SwapBuffers();

		fTime += fDeltaTime;
		fFrames += fDeltaTime;
		++nCount;
		
		if (fDeltaTime > fHighestDelta)
			fHighestDelta = fDeltaTime;

		if (fTime > 1000.f)
		{
			//std::cout << "FPS: " << (int)(1000.f/(fFrames/(float)nCount)) << "  Lowest: " << (int)(1000.f/ fHighestDelta) << "\n";
			fTime -= 1000.f;
			nCount = 0;
			fFrames = 0.f;
			fHighestDelta = 0.f;
		}
		fDeltaTime = std::chrono::duration<float, std::milli>(currentTime - previousTime).count();
		previousTime = currentTime;
	}
#ifdef EMSCRIPTEN
	; emscripten_set_main_loop_arg(dispatch_main, &mainLoop, 0, 1);
#endif

	alDeleteSources(1, &sourceid);
	alDeleteBuffers(1, &bufferid);
	device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
	delete[] data;

}
