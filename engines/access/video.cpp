/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "access/video.h"
#include "access/access.h"

namespace Access {

VideoPlayer::VideoPlayer(AccessEngine *vm) : Manager(vm) {
	_vidSurface = nullptr;
	_videoFrame = 0;
	_soundFlag = false;
	_soundFrame = 0;
	_videoData = nullptr;
}

VideoPlayer::~VideoPlayer() {
	closeVideo();
}


void VideoPlayer::setVideo(ASurface *vidSurface, const Common::Point &pt, const FileIdent &videoFile, int rate) {
	_vidSurface = vidSurface;
	vidSurface->_orgX1 = pt.x;
	vidSurface->_orgY1 = pt.y;
	_vm->_timers[31]._timer = rate;
	_vm->_timers[31]._initTm = rate;

	// Open up video stream
	_videoData = _vm->_files->loadFile(videoFile);

	// Load in header
	_header._frameCount = _videoData->_stream->readUint16LE();
	_header._width = _videoData->_stream->readUint16LE();
	_header._height = _videoData->_stream->readUint16LE();
	_videoData->_stream->skip(1);
	_header._flags = (VideoFlags)_videoData->_stream->readByte();
	
	_startCoord = (byte *)vidSurface->getBasePtr(pt.x, pt.y);
	_frameCount = _header._frameCount - 2;
	_xCount = _header._width;
	_scanCount = _header._height;
	_videoFrame = 0;

	getFrame();

	if (_header._flags == VIDEOFLAG_BG) {
		// Draw the background
		for (int y = 0; y < _scanCount; ++y) {
			byte *pDest = (byte *)vidSurface->getBasePtr(pt.x, pt.y + y);
			_videoData->_stream->read(pDest, _xCount);
		}

		if (vidSurface == _vm->_screen)
			_vm->_newRects.push_back(Common::Rect(pt.x, pt.y, pt.x + _xCount, pt.y + _scanCount));
		
		getFrame();
	}

	_videoEnd = false;
}

void VideoPlayer::closeVideo() {
	delete _videoData;
	_videoData = nullptr;
}

void VideoPlayer::getFrame() {
	_frameSize = _videoData->_stream->readUint16LE();
}

void VideoPlayer::playVideo() {
	if (_vm->_timers[31]._flag)
		return;
	++_vm->_timers[31]._flag;

	byte *pDest = _startCoord;
	byte *pLine = _startCoord;
	uint32 frameEnd = _videoData->_stream->pos() + _frameSize;

	while ((uint32)_videoData->_stream->pos() < frameEnd) {
		int count = _videoData->_stream->readByte();

		if (count & 0x80) {
			count &= 0x7f;

			// Skip count number of pixels
			// Loop across lines if necessary
			while (count >= (pLine + _xCount - pDest)) {
				count -= (pLine + _xCount - pDest);
				pLine += _vidSurface->pitch;
				pDest = pLine;
			}

			// Skip any remaining pixels in the new line
			pDest += count;
		} else {
			// Read count number of pixels
			
			// Load across lines if necessary
			while (count >= (pLine + _xCount - pDest)) {
				int lineCount = (pLine + _xCount - pDest);
				_videoData->_stream->read(pDest, lineCount);
				count -= lineCount;
				pLine += _vidSurface->pitch;
				pDest = pLine;
			}

			// Load remainder of pixels on line
			if (count > 0) {
				_videoData->_stream->read(pDest, count);
				pDest += count;
			}
		}
	}

	getFrame();
	if (++_videoFrame == _frameCount) {
		closeVideo();
		_videoEnd = true;
	}
}


} // End of namespace Access
