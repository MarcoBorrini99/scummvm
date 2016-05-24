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

#include "titanic/true_talk/tt_concept_node.h"
#include "titanic/true_talk/script_handler.h"
#include "titanic/titanic.h"

namespace Titanic {

TTconceptNode::TTconceptNode() : _concept0P(nullptr), 
		_concept1P(nullptr), _concept2P(nullptr), _concept3P(nullptr),
		_concept4P(nullptr), _concept5P(nullptr), _field18(0),
		_field1C(0), _nextP(nullptr), _status(0) {
}

TTconceptNode::TTconceptNode(const TTconceptNode &src) : _concept0P(nullptr),
		_concept1P(nullptr), _concept2P(nullptr), _concept3P(nullptr),
		_concept4P(nullptr), _concept5P(nullptr), _field18(0),
		_field1C(0), _nextP(nullptr), _status(0) {
	if (src._status) {
		_status = SS_5;
	} else {
		// TODO
	}
}


void TTconceptNode::deleteSiblings() {
	// Iterate through the linked chain of nodes, deleting each in turn
	for (TTconceptNode *curP = _nextP, *nextP = nullptr; nextP; curP = nextP) {
		nextP = curP->_nextP;
		delete curP;
	}

	_nextP = nullptr;
}

TTconcept **TTconceptNode::setConcept(int conceptIndex, TTconcept *src) {
	TTconcept **conceptPP = nullptr;
	switch (conceptIndex) {
	case 1:
		conceptPP = &_concept1P;
		break;
	case 2:
		conceptPP = &_concept2P;
		break;
	case 3:
		conceptPP = &_concept3P;
		break;
	case 4:
		conceptPP = &_concept4P;
		break;
	case 5:
		conceptPP = &_concept5P;
		break;
	default:
		break;
	}

	bool isPronoun = false;
	StringArray &pronouns = g_vm->_scriptHandler->_parser._pronouns;
	for (uint idx = 0; idx < pronouns.size() && !isPronoun; ++idx) {
		isPronoun = pronouns[idx] == src->getText();
	}

	CScriptHandler &scrHandler = *g_vm->_exeResources._owner;
	if (!isPronoun) {
		switch (conceptIndex) {
		case 0:
			delete scrHandler._concept2P;
			scrHandler._concept2P = new TTconcept(*src);
			break;

		case 1:
			delete scrHandler._concept4P;
			scrHandler._concept4P = new TTconcept(*src);
			break;

		case 2:
			delete scrHandler._concept1P;
			scrHandler._concept1P = new TTconcept(*src);
			break;

		default:
			break;
		}
	}

	return conceptPP;
}

int TTconceptNode::changeConcept(int mode, TTconcept **conceptPP, int conceptIndex) {
	TTconcept **newConceptPP = setConcept(conceptIndex, *conceptPP);

	if (mode == 0 || (mode == 1 && !*newConceptPP)) {
		if (!*conceptPP)
			return SS_5;

		delete *newConceptPP;
		*newConceptPP = new TTconcept(**conceptPP);
		return SS_VALID;
	} else {
		return SS_1;
	}
}

} // End of namespace Titanic
