// Residual - Virtual machine to run LucasArts' 3D adventure games
// Copyright (C) 2003-2006 The ScummVM-Residual Team (www.scummvm.org)
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA

#ifndef DRIVER_SDL_H
#define DRIVER_SDL_H

#include "bits.h"
#include "vector3d.h"
#include "color.h"
#include "model.h"
#include "colormap.h"
#include "bitmap.h"
#include "driver.h"

#include <SDL.h>

// NOTE: This is not a complete driver, it needs to be subclassed
//       to provide rendering functionality.

class DriverSDL : public Driver {
public:
	DriverSDL() : _samplesPerSec(22050) { ; }
	virtual ~DriverSDL() { ; }

	uint32 getMillis();
	void delayMillis(uint msecs);
	void setTimerCallback(TimerProc callback, int interval);

	bool setSoundCallback(SoundProc proc, void *param);
	void clearSoundCallback();
	int getOutputSampleRate() const;

private:
	int _samplesPerSec;
};

#endif
