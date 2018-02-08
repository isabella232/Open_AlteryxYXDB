#pragma once

#pragma warning( push, 0 )
#include <napi.h>
#pragma warning( pop )

#include <thread>

class NApiSandbox : public Napi::ObjectWrap<NApiSandbox>
{
public:
	static void
	Initialize(Napi::Env&, Napi::Object&);

	NApiSandbox(const Napi::CallbackInfo&);
	~NApiSandbox();

#ifndef CALLBACKMETHOD
	void
	Greet(const Napi::CallbackInfo&);
#endif

#ifdef CALLBACKMETHOD
	void
	Greet(const Napi::CallbackInfo&);
#endif

private:
	Napi::ObjectReference _greeterName;

	std::thread executor;
};
