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

#ifndef NANCY_GRAPHICS_H
#define NANCY_GRAPHICS_H

#include "engines/nancy/nancy.h"
#include "engines/nancy/video.h"
#include "engines/nancy/datatypes.h"

#include "common/func.h"

#include "graphics/screen.h"

namespace Nancy {

typedef Common::Functor0<void> RenderFunction;

struct ZRenderStruct {
public:
    enum BltType { kNone, kNoTrans, kTrans };

    uint32 z = 0;
    RenderFunction *renderFunction = nullptr;
    Graphics::Surface *sourceSurface = nullptr;
    Common::Rect *sourceRect = nullptr;
    Common::Point *destPoint = nullptr;
    bool isActive = false;
    bool isInitialized = false;
    BltType bltType = kNone;
    Common::String name;
};

class GraphicsManager {
public:
    GraphicsManager(NancyEngine *engine);
    ~GraphicsManager();

    void init();

    void clearGenericZRenderStruct(uint id);
    ZRenderStruct *getGenericZRenderStruct(uint id);
    void initGenericZRenderStruct(uint id, char const *name, uint32 z, bool isActive, ZRenderStruct::BltType bltType, Graphics::Surface *surface = nullptr, RenderFunction *func = nullptr, Common::Rect *sourceRect = nullptr, Common::Point *destPoint = nullptr);

    void renderDisplay(uint last);
    void renderDisplay(int *idMask);

    void loadBackgroundVideo(const Common::String &filename);
    const Graphics::Surface *getBackgroundFrame(uint16 frameId);
    uint32 getBackgroundFrameCount();
    uint32 getBackgroundWidth();
    uint32 getBackgroundHeight();

    Graphics::Surface _background;
    Graphics::Surface _frameTextBox;
    Graphics::Surface _primaryFrameSurface;
    Graphics::Surface _object0Surface;
    Graphics::Surface _inventoryBoxIconsSurface;
    Graphics::Surface _inventoryCursorsSurface;

    View viewportDesc;

    static const Graphics::PixelFormat pixelFormat;
    static const uint transColor;

private:
    NancyEngine *_engine;
    ZRenderStruct _ZRender[60];
    Graphics::Screen _screen;
    AVFDecoder _videoDecoder;

    uint _startingZ = 1;
    uint _numTimesRenderedFrame = 0; // no idea why we're doing this

public:
    // custom render functions
    void renderFrame();
    void renderResTBBatSlider();
    void renderFrameInvBox();
    void renderPrimaryVideo();
    void renderSecVideo0();
    void renderSecVideo1();
    void renderSecMovie();
    void renderOrderingPuzzle();
    void renderRotatingLockPuzzle();
    void renderLeverPuzzle();
    void renderTelephone();
    void renderSliderPuzzle();
    void renderPasswordPuzzle();
};

} // End of namespace Nancy

#endif // NANCY_GRAPHICS_H