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

#include "common/system.h"

#include "mtropolis/detection.h"
#include "mtropolis/hacks.h"
#include "mtropolis/runtime.h"

namespace MTropolis {

Hacks::Hacks() {
	memset(this, 0, sizeof(*this));
}

Hacks::~Hacks() {
	if (structuralHooks)
		delete structuralHooks;
	if (modifierHooks)
		delete modifierHooks;
}

void Hacks::addStructuralHooks(uint32 guid, const Common::SharedPtr<StructuralHooks> &hooks) {
	if (!structuralHooks)
		structuralHooks = new Common::HashMap<uint32, Common::SharedPtr<StructuralHooks> >();
	(*structuralHooks)[guid] = hooks;
}

void Hacks::addModifierHooks(uint32 guid, const Common::SharedPtr<ModifierHooks> &hooks) {
	if (!modifierHooks)
		modifierHooks = new Common::HashMap<uint32, Common::SharedPtr<ModifierHooks> >();
	(*modifierHooks)[guid] = hooks;
}


namespace HackSuites {

class ObsidianInventoryWindscreenHooks : public StructuralHooks {
public:
	void onSetPosition(Structural *structural, Common::Point &pt) override;
};

void ObsidianInventoryWindscreenHooks::onSetPosition(Structural *structural, Common::Point &pt) {
	if (pt.y < 480) {
		// Set direct to screen so it draws over cinematics
		static_cast<VisualElement *>(structural)->setDirectToScreen(true);

		// Move in-bounds
		pt.y -= 60;
	}
}

void addObsidianImprovedWidescreen(const MTropolisGameDescription &desc, Hacks &hacks) {
	if ((desc.desc.flags & ADGF_DEMO) == 0 && desc.desc.language == Common::EN_ANY && desc.desc.platform == Common::kPlatformWindows) {
		const uint32 inventoryItemGUIDs[] = {
			// Bureau documents
			// 100 area (booths)
			0x4e2d9e,
			0x4de654,

			// 199 area (booths hint room)
			0x4e2555,
			0x4de654,

			// 200 area (library)
			0x4c83d2,
			0x4c5802,

			// 299 area (Cloud Ring)
			0x178d5c,
			0x178d5c,

			// 300 area (light+phone)
			0x4e0f86,
			0x4e5107,

			// 400 area (maze)
			0x4e5528,
			0x4e55cc,

			// 500 area (Immediate Action)
			0x4e2e7b,
			0x4e0710,

			// 800 area (bookshelves)
			0x9914fb,
			0x990f1f,

			// 600 (sky face), 699 (mountain), and 700 (finale) have no document elements (player loses the documents)

			// Bureau maze keycards
			0x6035f,
			0x62e24,
			0x58d7f,
			0x58212,

			// Spider metal puzzle beaker
			0x12fa7,

			// Inspiration chip
			// 100 area (Junkyard)
			0x5f02e6,

			// 200 area (Plane)
			0x9bd5fc,

			// 300 area (Piazza)
			0x5ef979,
			
			// 400 area (Church)
			0xed9a8f,

			// 500 area (Statue)
			0x5ecdee,
		};

		Common::SharedPtr<StructuralHooks> invItemHooks(new ObsidianInventoryWindscreenHooks());

		for (uint32 guid : inventoryItemGUIDs)
			hacks.addStructuralHooks(guid, invItemHooks);
	}
}

} // End of namespace HackSuites

} // End of namespace MTropolis
