/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "mm/mm1/views/businesses/business.h"
#include "mm/mm1/globals.h"

namespace MM {
namespace MM1 {
namespace Views {
namespace Businesses {

Business::Business(const Common::String &name) : TextView(name) {
	_bounds = getLineBounds(17, 24);
}

void Business::drawInitial() {
	clearSurface();
	writeString(0, 0, g_globals->_currCharacter->_name);
	newLine();
	writeString(STRING["dialogs.business.gold"]);
	writeNumber(g_globals->_currCharacter->_gold);
	newLine();
	newLine();
	writeString(_modeString);
	writeString(0, 6, STRING["dialogs.misc.go_back"]);
}

void Business::newLine() {
	_textPos.x = 0;
	if (++_textPos.y >= 24)
		_textPos.y = 0;
}

} // namespace Businesses
} // namespace Views
} // namespace MM1
} // namespace MM
