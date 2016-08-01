#pragma once

#include <Entity/Include/Event.h>

struct TestEvent : public Magma::Event
{
	TestEvent()
		: Magma::Event(1)
		, myBool(true)
		, myInt(321)
	{}

	bool myBool;
	int myInt;
};