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

#ifndef TITANIC_SCRIPT_HANDLER_H
#define TITANIC_SCRIPT_HANDLER_H

#include "titanic/true_talk/tt_npc_script.h"
#include "titanic/true_talk/tt_room_script.h"
#include "titanic/true_talk/tt_string.h"
#include "titanic/true_talk/st_vocab.h"
#include "titanic/support/file_reader.h"

namespace Titanic {

class CTitleEngine;
class CScriptHandler;

class CScriptHandlerSub1 {
public:
	int _field0;
	int _field4;
	int _field8;
	int _fieldC;
	int _field10;
public:
	CScriptHandlerSub1() : _field0(0), _field4(0), _field8(0),
		_fieldC(0), _field10(0) {}
};

class CScriptHandlerSub2 {
public:
	CScriptHandler *_owner;
	int _field4;
	int _field8;
	int _fieldC;
	int _field10;
	int _field14;
	int _field18;
public:
	CScriptHandlerSub2(CScriptHandler *owner) : _owner(owner), _field4(0), _field8(0),
		_fieldC(0), _field10(0), _field14(0), _field18(0) {}
};

class CScriptHandler {
private:
	CTitleEngine *_owner;
	TTScriptBase *_script;
	STVocab *_vocab;
	CFileReader &_reader;
	int _field10;
	CScriptHandlerSub1 _sub1;
	CScriptHandlerSub2 _sub2;
	int _inputCtr;
	int _field20;
	int _field24;
	int _field28;
	int _field2C;
	int _field30;
public:
	CScriptHandler(CTitleEngine *owner, int val1, int val2);
	~CScriptHandler();

	/**
	 * Set the character and room
	 */
	ScriptChangedResult scriptChanged(TTRoomScript *roomScript, TTNpcScript *npcScript, uint dialogueId);

	void processInput(TTRoomScript *roomScript, TTNpcScript *npcScript,
		const TTString &line);

	/**
	 * Open a resource for access
	 */
	SimpleFile *openResource(const CString &name);
};

} // End of namespace Titanic

#endif /* TITANIC_SCRIPT_HANDLER_H */
