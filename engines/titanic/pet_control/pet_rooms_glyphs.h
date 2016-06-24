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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef TITANIC_PET_ROOMS_GLYPHS_H
#define TITANIC_PET_ROOMS_GLYPHS_H

#include "titanic/pet_control/pet_glyphs.h"
#include "titanic/support/simple_file.h"

namespace Titanic {

enum RoomGlyphMode {
	RGM_UNASSIGNED = 0, RGM_ASSIGNED_ROOM = 1, RGM_PREV_ASSIGNED_ROOM = 2
};

class CPetRoomsGlyph : public CPetGlyph {
private:
	uint _roomFlags;
	int _field38;
	RoomGlyphMode _mode;
	CGameObject *_object0;
	CGameObject *_object1;
	CGameObject *_object2;
	CGameObject *_object3;
	CGameObject *_object4;
	CGameObject *_object5;
	CGameObject *_object6;
	CGameObject *_object7;
private:
	/**
	 * Find the selected button under the given point, based on the buttons
	 * starting at a designated top/left position
	 */
	int getSelection(const Point &topLeft, const Point &pt);

	/**
	 * Draws the objects
	 */
	void drawObjects(uint flags, const Point &pt, CScreenManager *screenManager);
public:
	CPetRoomsGlyph();
	CPetRoomsGlyph(uint flags);

	/**
	 * Setup the glyph
	 */
	virtual bool setup(CPetControl *petControl, CPetGlyphs *owner);

	/**
	 * Draw the glyph at a specified position
	 */
	virtual void drawAt(CScreenManager *screenManager, const Point &pt, bool isHighlighted);

	/**
	 * Handles any secondary drawing of the glyph
	 */
	virtual void draw2(CScreenManager *screenManager) {}

	/**
	 * 
	 */
	virtual void proc28(const Point &topLeft, const Point &pt);

	virtual int proc29(const Point &pt);

	/**
	 * Returns the tooltip text for when the glyph is selected
	 */
	virtual void getTooltip(CPetText *text);

	virtual void save2(SimpleFile *file, int indent) const;
	
	virtual int proc33();

	/**
	 * Loads flags for the glyph
	 */
	virtual void loadFlags(SimpleFile *file, int val);

	/**
	 * Set the room flags for the glyph
	 */
	void setRoomFlags(uint flags) { _roomFlags = flags; }

	/**
	 * Get the room flags for the glyph
	 */
	uint getRoomFlags() const { return _roomFlags; }

	void set38(int val) { _field38 = val; }

	/**
	 * Sets the mode of the glyph
	 */
	void setMode(RoomGlyphMode mode) { _mode = mode; }

	void changeLocation(int newClassNum);

	/**
	 * Returns true if the room is either currently or previously assigned
	 */
	bool isAssigned() const { return _mode != RGM_UNASSIGNED; }
	
	/**
	 * Returns true if the room is the one currently assigned to the player
	 */
	bool isCurrentlyAssigned() const { return _mode == RGM_ASSIGNED_ROOM; }
	
	/**
	 * Returns true if the room was previously assigned to the player
	 */
	bool isPreviouslyAssigned() const { return _mode == RGM_PREV_ASSIGNED_ROOM; }
};

class CPetRoomsGlyphs : public CPetGlyphs {
private:
public:
	/**
	 * Save the list
	 */
	void save2(SimpleFile *file, int indent) const;

	/**
	 * Returns the glyph for hte player's assigned room
	 */
	CPetRoomsGlyph *findAssignedRoom() const;

	/**
	 * Finds a glyph in the list by it's room flags
	 */
	CPetRoomsGlyph *findGlyphByFlags(uint flags) const;

	/**
	 * Returns true if there's a glyph in the list with a given room flags
	 */
	bool hasFlags(uint flags) const { return findGlyphByFlags(flags) != nullptr; }
};

} // End of namespace Titanic

#endif /* TITANIC_PET_ROOMS_GLYPHS_H */
