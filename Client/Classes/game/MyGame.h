#ifndef MYGAME_H
#define MYGAME_H
#pragma once

#include "GGData.h"
#include "net/Client.h"

class game{
public:
	game();
	virtual ~game();
	void init();
	void start();
};

#endif
