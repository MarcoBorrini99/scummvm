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
 *
 * Based on the original sources
 *   Faery Tale II -- The Halls of the Dead
 *   (c) 1993-1996 The Wyrmkeep Entertainment Co.
 */

#include "saga2/std.h"
#include "saga2/gdraw.h"
#include "saga2/objects.h"
#include "saga2/grabinfo.h"
#include "saga2/contain.h"
#include "saga2/motion.h"
#include "saga2/player.h"
#include "saga2/script.h"
#include "saga2/document.h"
#include "saga2/magic.h"
#include "saga2/weapons.h"
#include "saga2/spellbuk.h"
#include "saga2/combat.h"

#include "saga2/methods.r"
#include "saga2/pclass.r"

namespace Saga2 {

extern SpellStuff   spellBook[];
extern uint8        identityColors[256];

#ifdef __WATCOMC__
#pragma off (unreferenced);
#endif

extern PlayerActor playerList[];    //  Master list of all PlayerActors

extern ObjectSoundFXs   *objectSoundFXTable;    // the global object sound effects table

extern TilePoint incDirTable[];

#if DEBUG
extern bool     massAndBulkCount;
#endif

/* ===================================================================== *
   Functions
 * ===================================================================== */

ObjectID ProtoObj::placeObject(void) {
	return 2;
}

//  Check if item can be contained by this object
bool ProtoObj::canContain(ObjectID dObj, ObjectID item) {
	return FALSE;
}

//  Determine if the object can contain another object at the specified
//  slot
bool ProtoObj::canContainAt(
    ObjectID        dObj,
    ObjectID        item,
    const TilePoint &where) {
	return FALSE;
}

//  Determine if this type of object is two handed
bool ProtoObj::isTwoHanded(ObjectID) {
	return FALSE;
}

//  Determine if this type of object is a missile
bool ProtoObj::isMissile(void) {
	return FALSE;
}

//Create Container Window
// ContainerWindow *ProtoObj::makeWindow( GameObject *Obj ) { return NULL; }


//  generic actions

//  Simple use command
bool ProtoObj::use(ObjectID dObj, ObjectID enactor) {
	assert(dObj != Nothing);

	int16   scriptResult;

	//  Setup use cursor, if necessary
	if (setUseCursor(dObj)) return TRUE;

	//  Handle object script in a standard fashion
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onUse,
	                        dObj, enactor, Nothing))
	        !=  actionResultNotDone)
		return scriptResult == actionResultSuccess;

	return useAction(dObj, enactor);
}

//  The default action is not to set up a use cursor
bool ProtoObj::setUseCursor(ObjectID dObj) {
	return FALSE;
}

//  The virtual use action command
bool ProtoObj::useAction(ObjectID dObj, ObjectID enactor) {
	return FALSE;
}

//  UseOn object command
bool ProtoObj::useOn(ObjectID dObj, ObjectID enactor, ObjectID item) {
	assert(dObj != Nothing);
	assert(item != Nothing);

	int16   scriptResult;

	//  Handle object script in a standard fashion
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onUseOn,
	                        dObj, enactor, item))
	        !=  actionResultNotDone)
		return scriptResult == actionResultSuccess;

	//  If script has not aborted action call virtual useOnAction
	//  function
	return useOnAction(dObj, enactor, item);
}

//  Perform the use on action
bool ProtoObj::useOnAction(ObjectID dObj, ObjectID enactor, ObjectID item) {
	return FALSE;
}

//  UseOn active item command
bool ProtoObj::useOn(ObjectID dObj, ObjectID enactor, ActiveItem *item) {
	assert(dObj != Nothing);
	assert(item != NULL);

	int16   scrResult;

	scriptCallFrame scf;
	scriptResult    sResult;

	scf.invokedObject   = dObj;
	scf.enactor         = enactor;
	scf.directObject    = dObj;
	scf.indirectTAI     = item->thisID();
	scf.value           = 0;

	//  Call the SAGA script, if there is one.
	sResult = runObjectMethod(dObj, Method_GameObject_onUseOnTAI, scf);

	//  If the script actually ran, and it didn't return a code
	//  telling us to abort the action...
	if (sResult == scriptResultFinished)
		scrResult = scf.returnVal;
	else
		scrResult = actionResultNotDone;
	if (scrResult != actionResultNotDone)
		return scrResult == actionResultSuccess;

	return useOnAction(dObj, enactor, item);

}

//  Perform the use on action
bool ProtoObj::useOnAction(ObjectID dObj, ObjectID enactor, ActiveItem *item) {
	return FALSE;
}

//  UseOn location command
bool ProtoObj::useOn(ObjectID dObj, ObjectID enactor, const Location &loc) {
	assert(dObj != Nothing);
	assert(loc != Nowhere && loc.context != Nothing);

	/*  int16   scrResult;

	    scriptCallFrame scf;
	    scriptResult    sResult=(scriptResult) actionResultNotDone;

	    scf.invokedObject   = dObj;
	    scf.enactor         = enactor;
	    scf.directObject    = dObj;
	    //scf.indirectTAI       = item->thisID();
	//  scf.indirectObject  = indirectObj;
	    scf.value           = 0;

	        //  Call the SAGA script, if there is one.
	//  sResult = runObjectMethod( dObj, Method_GameObject_onUseOnTAI, scf );

	        //  If the script actually ran, and it didn't return a code
	        //  telling us to abort the action...
	    if ( sResult == scriptResultFinished )
	        scrResult=scf.returnVal;
	    else
	        scrResult=actionResultNotDone;
	*//*
        //  Handle object script in a standard fashion
    if (    ( scriptResult =    stdActionScript(
                                    Method_GameObject_useOnTAI,
                                    dObj, enactor, item->thisID() ) )
                !=  actionResultNotDone )
        return scriptResult == actionResultSuccess;

        //  If script has not aborted action call virtual useOnAction
        //  function
*//*
    if ( scrResult != actionResultNotDone )
        return scrResult == actionResultSuccess;
*/
	return useOnAction(dObj, enactor, loc);
}

//  Perform the use on action
bool ProtoObj::useOnAction(ObjectID dObj, ObjectID enactor, const Location &loc) {
	return FALSE;
}

//-----------------------------------------------------------------------
//	Returns TRUE if object in continuous use.

bool ProtoObj::isObjectBeingUsed(GameObject *) {
	return FALSE;
}

//-----------------------------------------------------------------------
//	Determine if the specified object's 'use' slot is available within the
//	specified actor

bool ProtoObj::useSlotAvailable(GameObject *, Actor *) {
	return FALSE;
}

//  Open this object
bool ProtoObj::open(ObjectID dObj, ObjectID enactor) {
	assert(dObj != Nothing);

	int16   scriptResult;

	if (!canOpen(dObj, enactor)) return FALSE;

	//  Handle object script in a standard fashion
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onOpen,
	                        dObj, enactor, Nothing))
	        != actionResultNotDone)
		return scriptResult == actionResultSuccess;

	return openAction(dObj, enactor);
}

//  Virtual function to determine if this object can be opened
bool ProtoObj::canOpen(ObjectID, ObjectID) {
	return FALSE;
}

//  Virtual function to actually open the object
bool ProtoObj::openAction(ObjectID, ObjectID) {
	return FALSE;
}

//  Close this object
bool ProtoObj::close(ObjectID dObj, ObjectID enactor) {
	assert(dObj != Nothing);

	int16           scriptResult;
	GameObject      *dObjPtr = GameObject::objectAddress(dObj);

	if (!dObjPtr->isOpen()) return FALSE;

	//  Handle object script in a standard fashion
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onClose,
	                        dObj, enactor, Nothing))
	        != actionResultNotDone)
		return scriptResult == actionResultSuccess;

	return closeAction(dObj, enactor);
}

//  Virtual function to actually close the object
bool ProtoObj::closeAction(ObjectID, ObjectID) {
	return FALSE;
}

//  Take this object
bool ProtoObj::take(ObjectID dObj, ObjectID enactor, int16 num) {
	assert(dObj != Nothing);
	assert(mouseInfo.getObjectId() == Nothing);

	// >>> this needs to be dynamic!
	if (mass > 200 || bulk > 200) return FALSE;

	int16           scriptResult;

	//  Handle object script in a standard fashion
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onTake,
	                        dObj, enactor, Nothing))
	        != actionResultNotDone)
		return scriptResult == actionResultSuccess;

	return takeAction(dObj, enactor, num);
}

//  Virtual function to take the object
bool ProtoObj::takeAction(ObjectID, ObjectID) {
	return FALSE;
}

//  Virtual function to take the object
bool ProtoObj::takeAction(ObjectID, ObjectID, int16 num) {
	return FALSE;
}


//  Drop this object at the specified location
bool ProtoObj::drop(ObjectID dObj, ObjectID enactor, const Location &loc, int16 num) {
	assert(dObj != Nothing);

	if (!canDropAt(dObj, enactor, loc)) return FALSE;

	//  Handle object script in a non-standard fashion
	scriptCallFrame scf;
	scriptResult    sResult;

	scf.invokedObject   = dObj;
	scf.enactor         = enactor;
	scf.directObject    = dObj;
	scf.indirectObject  = loc.context;
	scf.coords          = loc;
	scf.value           = 0;

	//  Call the SAGA script, if there is one.
	sResult = runObjectMethod(dObj, Method_GameObject_onDrop, scf);

	//  If the script actually ran, and it didn't return a code
	//  telling us to abort the action...
	if (sResult == scriptResultFinished
	        &&  scf.returnVal != actionResultNotDone)
		return scf.returnVal == actionResultSuccess;

	return dropAction(dObj, enactor, loc, num);
}

//  Virtual function to determine if this object can be dropped at the
//  specified location
bool ProtoObj::canDropAt(ObjectID, ObjectID, const Location &) {
	return FALSE;
}

//  Virtual function to drop the object
bool ProtoObj::dropAction(ObjectID, ObjectID, const Location &, int16) {
	return FALSE;
}

//  drop an object onto another object and handle the result.
bool ProtoObj::dropOn(ObjectID dObj, ObjectID enactor, ObjectID target, int16 count) {
	assert(dObj != Nothing);

	// this prevents objects from being dropped on themselves
	if (target == dObj) return TRUE;

	int16       scriptResult;

	//  Handle object script in a standard fashion
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onDropOn,
	                        dObj, enactor, target, count))
	        !=  actionResultNotDone) {
		return scriptResult == actionResultSuccess;
	}

	//  At this point we should probably _split_ the object...

	return dropOnAction(dObj, enactor, target, count);
}

//  Do the actual drop
bool ProtoObj::dropOnAction(ObjectID dObj, ObjectID enactor, ObjectID target, int count) {
	ProtoObj        *targetProto = GameObject::protoAddress(target);

	//  For now, we just re-send the drop message to the object
	//  being dropped on...

	return targetProto->acceptDrop(target, enactor, dObj, count);
}

//  drop this object onto a TAG
bool ProtoObj::dropOn(
    ObjectID        dObj,
    ObjectID        enactor,
    ActiveItem      *target,
    const Location  &loc,
    int16           num) {
	assert(dObj != Nothing);
	assert(target != NULL);
	assert(isWorld(loc.context));

	int16       scriptResult;
	/*
	        //  Handle object script in a standard fashion
	    if (    ( scriptResult =    stdActionScript(
	                                    Method_GameObject_onDropOnTAG,
	                                    dObj, enactor, target ) )
	                != actionResultNotDone )
	        return scriptResult == actionResultSuccess;
	*/
	return dropOnAction(dObj, enactor, target, loc, num);
}

//  Virtual function to drop an object on a TAG
bool ProtoObj::dropOnAction(
    ObjectID,
    ObjectID,
    ActiveItem *,
    const Location &,
    int16) {
	return FALSE;
}

//  Strike another object with this object
bool ProtoObj::strike(ObjectID dObj, ObjectID enactor, ObjectID item) {
	assert(isObject(dObj) || isActor(dObj));
	assert(isObject(item) || isActor(item));

	int16   scriptResult;

	//  Handle object script in a standard fashion
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onStrike,
	                        dObj, enactor, item))
	        !=  actionResultNotDone)
		return scriptResult == actionResultSuccess;

	return strikeAction(dObj, enactor, item);
}

//  Virtual function to strike another object with this object
bool ProtoObj::strikeAction(ObjectID, ObjectID, ObjectID) {
	return FALSE;
}

//  Damage another object with this object
bool ProtoObj::damage(ObjectID dObj, ObjectID enactor, ObjectID target) {
	assert(isObject(dObj) || isActor(dObj));
	assert(isObject(target) || isActor(target));

	int16   scriptResult;

	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onDamage,
	                        dObj, enactor, target))
	        !=  actionResultNotDone)
		return scriptResult == actionResultSuccess;

	return damageAction(dObj, enactor, target);
}

//  Virtual function to damage another object with this object
bool ProtoObj::damageAction(ObjectID, ObjectID, ObjectID) {
	return FALSE;
}

//  Eat this object
bool ProtoObj::eat(ObjectID dObj, ObjectID enactor) {
	assert(dObj != Nothing);

	int16           scriptResult;

	//  Handle object script in a standard fashion
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onEat,
	                        dObj, enactor, Nothing))
	        != actionResultNotDone)
		return scriptResult == actionResultSuccess;

	return eatAction(dObj, enactor);
}

//  Virtual function to eat this object
bool ProtoObj::eatAction(ObjectID, ObjectID) {
	return FALSE;
}

//  Insert this object into another object
bool ProtoObj::insert(ObjectID dObj, ObjectID enactor, ObjectID item) {
	assert(dObj != Nothing);
	assert(item != Nothing);

	int16   scriptResult;

	//  Handle object script in a standard fashion
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onInsert,
	                        dObj, enactor, item))
	        !=  actionResultNotDone)
		return scriptResult == actionResultSuccess;

	return insertAction(dObj, enactor, item);
}

//  Virtual function to insert this object into another object
bool ProtoObj::insertAction(ObjectID, ObjectID, ObjectID) {
	return FALSE;
}

//  Remove this object from the object it is in
bool ProtoObj::remove(ObjectID dObj, ObjectID enactor) {
	assert(dObj != Nothing);

	int16           scriptResult;

	//  Handle object script in a standard fashion
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onRemove,
	                        dObj, enactor, Nothing))
	        != actionResultNotDone)
		return scriptResult == actionResultSuccess;

	return removeAction(dObj, enactor);
}

//  Virtual function to remove this object from the object it is in
bool ProtoObj::removeAction(ObjectID, ObjectID) {
	return FALSE;
}

//  Handle the effects of an object being dropped on this object
bool ProtoObj::acceptDrop(
    ObjectID dObj,
    ObjectID enactor,
    ObjectID droppedObj,
    int count) {
	assert(dObj != Nothing);
	assert(droppedObj != Nothing);

	int16   scriptResult;

	//  Handle object script in a standard fashion
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onAcceptDrop,
	                        dObj, enactor, droppedObj, count))
	        !=  actionResultNotDone)
		return scriptResult == actionResultSuccess;

	return acceptDropAction(dObj, enactor, droppedObj, count);
}

//  Virtual function to handle the effects of an object being dropped
//  on this object
bool ProtoObj::acceptDropAction(ObjectID dObj, ObjectID enactor, ObjectID droppedObj, int count) {
	return acceptInsertion(dObj, enactor, droppedObj, count);
}


bool ProtoObj::acceptDamage(
    ObjectID            dObj,
    ObjectID            enactor,
    int8                absDamage,
    effectDamageTypes   dType,
    int8                dice,
    uint8               sides,
    int8                perDieMod) {
	int16   scriptResult;

	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onAcceptDamage,
	                        dObj, enactor, Nothing))
	        != actionResultNotDone)
		return scriptResult == actionResultSuccess;

	return  acceptDamageAction(
	            dObj,
	            enactor,
	            absDamage,
	            dType,
	            dice,
	            sides,
	            perDieMod);
}


//  Virtual function to damage this object directly
bool ProtoObj::acceptDamageAction(
    ObjectID,
    ObjectID,
    int8,
    effectDamageTypes,
    int8,
    uint8,
    int8) {
	return TRUE;
}

bool ProtoObj::acceptHealing(
    ObjectID    dObj,
    ObjectID    enactor,
    int8        absDamage,
    int8        dice,
    uint8       sides,
    int8        perDieMod) {
	int8 pdm = perDieMod;
	int16 damage = 0;
	int16           scriptResult;
	assert(dObj != Nothing);
	damage = absDamage;
	if (dice)
		for (int d = 0; d < abs(dice); d++)
			damage += (g_vm->_rnd->getRandomNumber(sides - 1) + pdm + 1) * (dice > 0 ? 1 : -1);
#if 0
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onAcceptDamage,
	                        dObj, enactor, Nothing))
	        != actionResultNotDone)
		return scriptResult == actionResultSuccess;
#endif
	return acceptHealingAction(dObj, enactor, damage);
}


//  Virtual function to damage this object directly
bool ProtoObj::acceptHealingAction(ObjectID, ObjectID, int8) {
	return FALSE;
}

//  Accept strike from another object (allows this object to cause
//  damage to the striking object).
bool ProtoObj::acceptStrike(
    ObjectID            dObj,
    ObjectID            enactor,
    ObjectID            strikingObj,
    uint8               skillIndex) {
	assert(dObj != Nothing);
	assert(strikingObj != Nothing);

	int16   scriptResult;

	//  Handle object script in a standard fashion
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onAcceptStrike,
	                        dObj, enactor, strikingObj))
	        !=  actionResultNotDone)
		return scriptResult == actionResultSuccess;

	return  acceptStrikeAction(
	            dObj,
	            enactor,
	            strikingObj,
	            skillIndex);
}

//  Virtual function to handle the effects of a strike on this object
bool ProtoObj::acceptStrikeAction(
    ObjectID,
    ObjectID,
    ObjectID,
    uint8) {
	return TRUE;
}

//  Unlock or lock this object with a key.
bool ProtoObj::acceptLockToggle(
    ObjectID    dObj,
    ObjectID    enactor,
    uint8       keyCode) {
	assert(dObj != Nothing);

	int16       scriptResult;

	if (!canToggleLock(dObj, enactor, keyCode)) return FALSE;

	//  Handle object script in a standard fashion
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onAcceptLockToggle,
	                        dObj, enactor, Nothing))
	        != actionResultNotDone)
		return scriptResult == actionResultSuccess;

	return acceptLockToggleAction(dObj, enactor, keyCode);
}

//  Virtual function to determine if the lock can be toggled
bool ProtoObj::canToggleLock(ObjectID, ObjectID, uint8) {
	return FALSE;
}

//  Virtual function to actually toggle the lock
bool ProtoObj::acceptLockToggleAction(ObjectID, ObjectID, uint8) {
	return FALSE;
}

//  Mix this object with another.
bool ProtoObj::acceptMix(ObjectID dObj, ObjectID enactor, ObjectID mixObj) {
	assert(dObj != Nothing);
	assert(mixObj != Nothing);

	int16   scriptResult;

	//  Handle object script in a standard fashion
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onAcceptMix,
	                        dObj, enactor, mixObj))
	        !=  actionResultNotDone)
		return scriptResult == actionResultSuccess;

	return acceptMixAction(dObj, enactor, mixObj);
}

//  Virtual function to mix this object with another
bool ProtoObj::acceptMixAction(ObjectID, ObjectID, ObjectID) {
	return FALSE;
}

//  Insert another object into this object.
bool ProtoObj::acceptInsertion(
    ObjectID dObj,
    ObjectID enactor,
    ObjectID item,
    int16 count) {
	assert(dObj != Nothing);
	assert(item != Nothing);

	if (!canContain(dObj, item)) return FALSE;

	int16           scriptResult;

	//  Handle object script in a standard fashion
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onAcceptInsertion,
	                        dObj, enactor, item, count))
	        != actionResultNotDone)
		return scriptResult == actionResultSuccess;

	return acceptInsertionAction(dObj, enactor, item, count);
}

//  Virtual function to insert an object into this object
bool ProtoObj::acceptInsertionAction(ObjectID, ObjectID, ObjectID, int16) {
	return FALSE;
}

//  Insert another object into this object at a specified slot
bool ProtoObj::acceptInsertionAt(
    ObjectID        dObj,
    ObjectID        enactor,
    ObjectID        item,
    const TilePoint &where,
    int16           num) {
	assert(dObj != Nothing);
	assert(item != Nothing);

	if (!canContainAt(dObj, item, where)) return FALSE;

	int16           scriptResult;

	//  Handle object script in a standard fashion
	if ((scriptResult = stdActionScript(
	                        Method_GameObject_onAcceptInsertion,
	                        dObj, enactor, item))
	        != actionResultNotDone)
		return scriptResult == actionResultSuccess;

	return acceptInsertionAtAction(dObj, enactor, item, where, num);
}

//  Virtual function to insert another object into this object at a
//  specified slot
bool ProtoObj::acceptInsertionAtAction(
    ObjectID, ObjectID, ObjectID, const TilePoint &, int16) {
	return FALSE;
}



//  Creates a color translation table for this object
void ProtoObj::getColorTranslation(ColorTable map) {
	buildColorTable(map, colorMap, elementsof(colorMap));
}

uint16  ProtoObj::containmentSet(void) {
	return 0; // the prototye object is not contained in anything
}

//  return the sprite data
ObjectSpriteInfo ProtoObj::getSprite(GameObject *obj, enum spriteTypes spr, int16 count) {
	ObjectSpriteInfo    sprInfo = { NULL, static_cast<bool>((flags & objPropFlipped) != 0) };
	int16               openOffset = ((flags & objPropVisOpen) && obj->isOpen()) ? 1 : 0;

	switch (spr) {
	case objOnGround:

		//  If the object is a moving missile return the correct missile
		//  sprite
		if (obj->isMoving()
		        &&  obj->isMissile()
		        &&  obj->missileFacing < 16) {
			int16   sprIndex;

			if (obj->missileFacing < 8)
				sprIndex = obj->missileFacing;
			else {
				sprIndex = 16 - obj->missileFacing;
				sprInfo.flipped = TRUE;
			}

			sprInfo.sp = missileSprites->sprite(sprIndex);
		} else {
			sprInfo.sp = objectSprites->sprite(groundSprite + openOffset + obj->getSprOffset(count));
			sprInfo.flipped =
			    (flags & ResourceObjectPrototype::objPropFlipped) != 0;
		}

		break;

	case objInContainerView:
	case objAsMousePtr:

		sprInfo.sp = objectSprites->sprite(iconSprite + openOffset + obj->getSprOffset(count));
		sprInfo.flipped =
		    (flags & ResourceObjectPrototype::objPropFlipped) != 0;
		break;
	}
	return sprInfo;
}

//  return the address of the sprite when held in hand
Sprite *ProtoObj::getOrientedSprite(GameObject *obj, int16 offset) {
	return NULL;
}

int16 ProtoObj::stdActionScript(
    int             method,
    ObjectID        dObj,
    ObjectID        enactor,
    ObjectID        indirectObj) {
	scriptCallFrame scf;
	scriptResult    sResult;

	scf.invokedObject   = dObj;
	scf.enactor         = enactor;
	scf.directObject    = dObj;
	scf.indirectObject  = indirectObj;
	scf.value           = 0;

	//  Call the SAGA script, if there is one.
	sResult = runObjectMethod(dObj, method, scf);

	//  If the script actually ran, and it didn't return a code
	//  telling us to abort the action...
	if (sResult == scriptResultFinished)
		return scf.returnVal;

	return actionResultNotDone;
}

int16 ProtoObj::stdActionScript(
    int             method,
    ObjectID        dObj,
    ObjectID        enactor,
    ObjectID        indirectObj,
    int16           value) {
	scriptCallFrame scf;
	scriptResult    sResult;

	scf.invokedObject   = dObj;
	scf.enactor         = enactor;
	scf.directObject    = dObj;
	scf.indirectObject  = indirectObj;
	scf.value           = value;

	//  Call the SAGA script, if there is one.
	sResult = runObjectMethod(dObj, method, scf);

	//  If the script actually ran, and it didn't return a code
	//  telling us to abort the action...
	if (sResult == scriptResultFinished)
		return scf.returnVal;

	return actionResultNotDone;
}

//  Initiate an attack using this type of object
void ProtoObj::initiateAttack(ObjectID, ObjectID) {}

//  Initiate a defense using this type of object
void ProtoObj::initiateDefense(ObjectID, ObjectID, ObjectID) {}

//  Get projectile for missile weapons
GameObject *ProtoObj::getProjectile(ObjectID, ObjectID) {
	return NULL;
}

//  Get spell from a magic object
GameObject *ProtoObj::getSpell(ObjectID) {
	return NULL;
}

//  Determine if this type of object can block an attack
bool ProtoObj::canBlock(void) {
	return FALSE;
}

//  Return a mask of bits indicating the directions relative to the
//  wielders facing in which this object can defend
uint8 ProtoObj::defenseDirMask(void) {
	return 0;
}

// ------------------------------------------------------------------------
//	Compute how much damage this defensive object will absorb

uint8 ProtoObj::adjustDamage(uint8 damage) {
	return damage;
}

// ------------------------------------------------------------------------
//	Return the fight stance approriate to this weapon

int16 ProtoObj::fightStanceAction(ObjectID actor) {
	return actionStand;
}

// ------------------------------------------------------------------------
//	Get the value of the user's skill which applies to this  object

uint8 ProtoObj::getSkillValue(ObjectID) {
	return 0;
}

// ------------------------------------------------------------------------
//	Cause the user's associated skill to grow

void ProtoObj::applySkillGrowth(ObjectID, uint8) {}

// ------------------------------------------------------------------------
//	Given an object sound effect record, which sound should be made
//	when this object is damaged

uint8 ProtoObj::getDamageSound(const ObjectSoundFXs &) {
	//  Default is no sound
	return 0;
}

// ------------------------------------------------------------------------
//	Background update function, called once every few seconds

void ProtoObj::doBackgroundUpdate(GameObject *obj) {
	TilePoint   location = obj->getLocation();
	GameWorld   *w = obj->world();

	if (w == NULL
	        ||  !w->getSector(
	            location.u >> sectorShift,
	            location.v >> sectorShift)->isActivated())
		obj->deactivate();
}

// ------------------------------------------------------------------------

bool ProtoObj::canFitBulkwise(GameObject *, GameObject *) {
	return FALSE;
}

// ------------------------------------------------------------------------

bool ProtoObj::canFitMasswise(GameObject *, GameObject *) {
	return FALSE;
}

// ------------------------------------------------------------------------
//	Return the maximum mass capacity for the specified container

uint16 ProtoObj::massCapacity(GameObject *) {
	return 0;
}

// ------------------------------------------------------------------------
//	Return the maximum bulk capacity for the specified container

uint16 ProtoObj::bulkCapacity(GameObject *) {
	return 0;
}

/* ==================================================================== *
   InventoryProto class
 * ==================================================================== */

uint16 InventoryProto::containmentSet(void) {
	return isTangible;
}

bool InventoryProto::takeAction(ObjectID dObj, ObjectID enactor, int16 num) {
	mouseInfo.copyObject(dObj, GrabInfo::Drop, num);
	return TRUE;
}

bool InventoryProto::canDropAt(
    ObjectID,
    ObjectID        enactor,
    const Location  &loc) {
	assert(enactor != Nothing);

	//  If we're not dropping it onto a world, we're okay
	if (!isWorld(loc.context)) return TRUE;

	GameObject      *enactorPtr = GameObject::objectAddress(enactor);

	//  If we're trying to drop it into a different world or if
	//  we're dropping it more than 4 metatile widths away from the
	//  enactor, fail
	if (enactorPtr->IDParent() != loc.context
	        || (loc - enactorPtr->getLocation()).quickHDistance()
	        >   tileUVSize * platformWidth * 4)
		return FALSE;

	return TRUE;
}

bool InventoryProto::dropAction(
    ObjectID        dObj,
    ObjectID        enactor,
    const Location  &loc,
    int16           num) {
	assert(loc.context != Nothing);
	assert(dObj != Nothing);
	assert(enactor != Nothing);

	GameObject  *dObjPtr = GameObject::objectAddress(dObj);
	Actor       *enactorPtr = (Actor *)GameObject::objectAddress(enactor);

	/*      //  Determine if we're dropping an object from the actor's hands.
	    if ( enactor != loc.context )
	    {
	        if ( dObj == enactorPtr->rightHandObject )
	            enactorPtr->rightHandObject = Nothing;
	        if ( dObj == enactorPtr->leftHandObject )
	            enactorPtr->leftHandObject = Nothing;
	    }
	*/
	//  If this object is on a TAG release it
	if (dObjPtr->currentTAG != NoActiveItem) {
		ActiveItem::activeItemAddress(dObjPtr->currentTAG)->release(
		    enactor, dObj);
		dObjPtr->currentTAG = NoActiveItem;
	}

	if (isWorld(loc.context)) {
		ProtoObj            *enactorProto = enactorPtr->proto();
		TilePoint           enactorLoc(enactorPtr->getLocation());
		TilePoint           vector = loc - enactorLoc;
		StandingTileInfo    sti;
		GameObject          *extractedObj = NULL;

		//  Split the merged object if needed.
		if (dObjPtr->isMergeable()           //  If mergeable
		        &&  num < dObjPtr->getExtra()) {    //  And not dropping whole pile
			if (num == 0) return FALSE;         //  If mergeing zero, then do nothing

			extractedObj = dObjPtr->extractMerged(dObjPtr->getExtra() - num);
			if (extractedObj == NULL)
				return FALSE;

			extractedObj->move(
			    Location(dObjPtr->getLocation(), dObjPtr->IDParent()));
		}

		if (enactorPtr->inReach(loc)) {
			dObjPtr->move(loc);

			//  Make sure the game engine knows that it may scavenge this
			//  object if necessary
			if (!dObjPtr->isImportant())
				dObjPtr->setScavengable(TRUE);
		} else {
			int16       offsetDist = enactorProto->crossSection + crossSection;
			Direction   vectorDir = vector.quickDir();
			int16       mapNum = enactorPtr->getMapNum();
			TilePoint   startPt = Nowhere;
			int         i;

			static const int8 dirOffsetTable[] = { 0, 1, -1, 2, -2, 3, -3 };

			for (i = 0; i < elementsof(dirOffsetTable); i++) {
				TilePoint       testPt;
				Direction       testDir;

				testDir = (vectorDir + dirOffsetTable[ i ]) & 0x7;
				testPt = enactorLoc + incDirTable[ testDir ] * offsetDist;
				testPt.z += enactorProto->height >> 1;
				if (checkBlocked(dObjPtr, mapNum, testPt) == blockageNone) {
					startPt = testPt;
					break;
				}
			}

			if (startPt == Nowhere) {
				if (extractedObj != NULL)
					GameObject::mergeWith(extractedObj, dObjPtr, extractedObj->getExtra());
				return FALSE;
			}

			dObjPtr->move(Location(startPt, loc.context));

			//  Make sure the game engine knows that it may scavenge this
			//  object if necessary
			if (!dObjPtr->isImportant())
				dObjPtr->setScavengable(TRUE);

			MotionTask::throwObjectTo(*dObjPtr, loc);
		}
	} else {
		GameObject  *targetObj = GameObject::objectAddress(loc.context);

		return targetObj->acceptInsertionAt(enactor, dObj, loc, num);
	}

	return TRUE;
}

bool InventoryProto::dropOnAction(
    ObjectID        dObj,
    ObjectID        enactor,
    ActiveItem      *target,
    const Location  &loc,
    int16           num) {
	assert(dObj != Nothing);
	assert(target != NULL);
	assert(isWorld(loc.context));

	if (drop(dObj, enactor, loc, num)) {
		GameObject  *dObjPtr = GameObject::objectAddress(dObj);

		//  If we weren't thrown, try triggering the TAG
		if (!dObjPtr->isMoving() && target->trigger(enactor, dObj))
			dObjPtr->currentTAG = target->thisID();

		return TRUE;
	}

	return FALSE;
}

//  Virtual function to handle the effects of an object being dropped
//  on this object
bool InventoryProto::acceptDropAction(
    ObjectID dObj,
    ObjectID enactor,
    ObjectID droppedObj,
    int count) {
	GameObject  *dropObject     = GameObject::objectAddress(droppedObj);
	GameObject  *targetObject   = GameObject::objectAddress(dObj);
	int         mergeState      = GameObject::canStackOrMerge(dropObject, targetObject);

	if (mergeState == canMerge)
		return targetObject->merge(enactor, droppedObj, count);
	else if (mergeState == canStack)
		return targetObject->stack(enactor, droppedObj);

	return ProtoObj::acceptDropAction(dObj, enactor, droppedObj, count);
}

bool InventoryProto::acceptStrikeAction(
    ObjectID            dObj,
    ObjectID            enactor,
    ObjectID            strikingObj,
    uint8) {
	assert(isObject(dObj) || isActor(dObj));
	assert(isActor(enactor));
	assert(isObject(strikingObj) || isActor(strikingObj));

	GameObject      *weapon = GameObject::objectAddress(strikingObj);

	return weapon->damage(enactor, dObj);
}

/* ==================================================================== *
   PhysicalContainerProto class
 * ==================================================================== */

//void PhysicalContainerProto::setTotalRows(ContainerView *cv)
//{
//	cv->totalRows =
//
//	};

uint16 PhysicalContainerProto::containmentSet(void) {
	return InventoryProto::containmentSet() | isContainer;
}

bool PhysicalContainerProto::canContain(ObjectID dObj, ObjectID item) {
	GameObject *itemPtr = GameObject::objectAddress(item);
	GameObject *pPtr;

	//  Add recursive check: Make sure that the container isn't already
	//  inside of "item". Do this by looking at all of the ancestors of
	//  dObj and make sure that none of them equal "item".
	for (pPtr = GameObject::objectAddress(dObj); pPtr; pPtr = pPtr->parent()) {
		if (pPtr == itemPtr) return FALSE;
	}

	return      dObj != item
	            && (itemPtr->containmentSet() & ProtoObj::isTangible);
}

bool PhysicalContainerProto::canContainAt(
    ObjectID dObj,
    ObjectID item,
    const TilePoint &where) {
	if (canContain(dObj, item) == FALSE) return FALSE;
	return TRUE;
}

bool PhysicalContainerProto::useAction(ObjectID dObj, ObjectID enactor) {
	bool          result;
	GameObject    *dObjPtr = GameObject::objectAddress(dObj);

	if (dObjPtr->objectFlags & objectOpen)
		result = close(dObj, enactor);
	else
		result = open(dObj, enactor);

	return result;
}

//  Determine if this object can be opened
bool PhysicalContainerProto::canOpen(ObjectID dObj, ObjectID) {
	GameObject *dObjPtr = GameObject::objectAddress(dObj);

	return !dObjPtr->isLocked() && !dObjPtr->isOpen();
}

//  Open a physical container
bool PhysicalContainerProto::openAction(ObjectID dObj, ObjectID) {
	ContainerNode   *cn;

	GameObject *dObjPtr = GameObject::objectAddress(dObj);

	assert(!dObjPtr->isOpen() && !dObjPtr->isLocked());

	cn = CreateContainerNode(dObj, FALSE);
	cn->markForShow();                                      //  Deferred open
	dObjPtr->objectFlags |= objectOpen;         //  Set open bit;
	globalContainerList.setUpdate(dObjPtr->IDParent());
	return TRUE;
}

bool PhysicalContainerProto::closeAction(ObjectID dObj, ObjectID) {
	GameObject      *dObjPtr = GameObject::objectAddress(dObj);
	ContainerNode   *cn = globalContainerList.find(dObj, ContainerNode::physicalType);

	assert(dObjPtr->isOpen());
	assert(cn);

	//  Delete the container (lazy delete)
	cn->markForDelete();

	//  Clear open bit
	dObjPtr->objectFlags &= ~objectOpen;
	globalContainerList.setUpdate(dObjPtr->IDParent());
	return TRUE;
}

//  Determine if this object's lock can be toggled
bool PhysicalContainerProto::canToggleLock(
    ObjectID    dObj,
    ObjectID    enactor,
    uint8       keyCode) {
	GameObject *dObjPtr = GameObject::objectAddress(dObj);

	return keyCode == lockType && !dObjPtr->isOpen();
}

//  Unlock or lock the physical container
bool PhysicalContainerProto::acceptLockToggleAction(
    ObjectID    dObj,
    ObjectID    enactor) {
	GameObject *dObjPtr = GameObject::objectAddress(dObj);

	//  Toggle locked bit
	dObjPtr->objectFlags ^= objectLocked;

	return TRUE;
}

//  Insert another object into this object
bool PhysicalContainerProto::acceptInsertionAction(
    ObjectID dObj,
    ObjectID enactor,
    ObjectID item,
    int16 num) {
	assert(isObject(dObj));
	assert(isObject(item));

	GameObject  *dObjPtr = GameObject::objectAddress(dObj);
	GameObject  *itemPtr = GameObject::objectAddress(item);

	//  Place the object in the container (if possible)
	if ((dObjPtr->objectFlags & objectLocked)
	        ||  !dObjPtr->placeObject(enactor, item, TRUE, num)) {
		if (isWorld(dObjPtr->IDParent()))
			dObjPtr->dropInventoryObject(itemPtr, num);
		else {
			if (!itemPtr->dropOn(enactor, dObjPtr->IDParent(), num))
				return FALSE;
		}
	}

	//  If we extracted the dropped objects from a pile, then make sure
	//  the old pile gets redrawn. PlaceObject already takes care of
	//  redrawing the target container; But because extractMerged creates
	//  the extracted portion inside of "Nothing" the source container might
	//  not be redrawn in this case.
//	if (prevItemPtr) globalContainerList.setUpdate( prevItemPtr->IDParent() );

	return TRUE;
}

//  Insert another object into this object at the specified slot
bool PhysicalContainerProto::acceptInsertionAtAction(
    ObjectID        dObj,
    ObjectID,
    ObjectID        item,
    const TilePoint &where,
    int16           num) {
	assert(isObject(dObj));
	assert(isObject(item));

	GameObject  *dObjPtr = GameObject::objectAddress(dObj);
	GameObject  *itemPtr = GameObject::objectAddress(item);
	GameObject  *extractedObj = NULL;
	Location    oldLoc(itemPtr->getLocation(), itemPtr->IDParent());

	//  Split the merged object if needed.
	if (itemPtr->isMergeable()           //  If mergeable
	        &&  num < itemPtr->getExtra()) {    //  And not dropping whole pile
		if (num == 0) return FALSE;         //  If mergeing zero, then do nothing

		extractedObj = itemPtr->extractMerged(itemPtr->getExtra() - num);
		if (extractedObj == NULL)
			return FALSE;

		extractedObj->move(oldLoc);
	}

	itemPtr->move(Location(0, 0, 0, ImportantLimbo));
	if (dObjPtr->canFitBulkwise(itemPtr)
	        &&  dObjPtr->canFitMasswise(itemPtr)) {
		itemPtr->move(Location(where, dObj));
		return TRUE;
	}
	itemPtr->move(oldLoc);
	if (extractedObj != NULL)
		GameObject::mergeWith(extractedObj, itemPtr, extractedObj->getExtra());

	return FALSE;
}

// ------------------------------------------------------------------------
//	Determine if the specified object can fit within the specified container
//	based upon bulk

bool PhysicalContainerProto::canFitBulkwise(GameObject *container, GameObject *obj) {
#if DEBUG
	if (massAndBulkCount)
#endif
	{
		uint16                  maxBulk = container->bulkCapacity();
		uint16                  totalBulk = container->totalContainedBulk();

		return totalBulk + obj->totalBulk() <= maxBulk;
	}

#if DEBUG
	return TRUE;
#endif
}

// ------------------------------------------------------------------------
//	Determine if the specified object can fit within the specified container
//	based upon mass

bool PhysicalContainerProto::canFitMasswise(GameObject *container, GameObject *obj) {
#if DEBUG
	if (massAndBulkCount)
#endif
	{
		if (!isWorld(container->IDParent()))
			return container->parent()->canFitMasswise(obj);

		return TRUE;
	}

#if DEBUG
	return TRUE;
#endif
}

// ------------------------------------------------------------------------
//	Return the maximum mass capacity for the specified container

uint16 PhysicalContainerProto::massCapacity(GameObject *container) {
	if (!isWorld(container->IDParent()))
		return container->parent()->massCapacity();

	return unlimitedCapacity;
}

// ------------------------------------------------------------------------
//	Return the maximum bulk capacity for the specified container

uint16 PhysicalContainerProto::bulkCapacity(GameObject *) {
	return bulk * 4;
}

/* ==================================================================== *
   KeyProto class
 * ==================================================================== */

//  Put key into mouse with intention to use
bool KeyProto::setUseCursor(ObjectID dObj) {
	assert(mouseInfo.getObjectId() == Nothing);
	mouseInfo.copyObject(GameObject::objectAddress(dObj), GrabInfo::Use);
	return TRUE;
}

//  Send acceptLockToggle message to container
bool KeyProto::useOnAction(ObjectID dObj, ObjectID enactor, ObjectID withObj) {
	GameObject *container = GameObject::objectAddress(withObj),
	            *thisKey   = GameObject::objectAddress(dObj);

	int16 keyID = thisKey->massCount > 0 ? thisKey->massCount : lockType;

	if (!container->acceptLockToggle(enactor, lockType)) {
//		WriteStatusF( 3, "%s doesn't work", thisKey->objName() );
		return FALSE;
	}

	return TRUE;
}

//  Send acceptLockToggle message to active terrain
bool KeyProto::useOnAction(ObjectID dObj, ObjectID enactor, ActiveItem *withTAI) {
	GameObject *thisKey   = GameObject::objectAddress(dObj);

	int16 keyID = thisKey->massCount > 0 ? thisKey->massCount : lockType;

	if (!withTAI->acceptLockToggle(enactor, keyID)) {
//		WriteStatusF( 3, "%s doesn't work", thisKey->objName() );
		return FALSE;
	}

	return TRUE;
}

/* ==================================================================== *
   BottleProto class
 * ==================================================================== */

uint16 BottleProto::containmentSet(void) {
	return InventoryProto::containmentSet() | isBottle;
}

bool BottleProto::useAction(ObjectID dObj, ObjectID enactor) {
	//Set Up Empty Bottle Sprite

	return TRUE;
}

/* ==================================================================== *
   FoodProto class
 * ==================================================================== */

uint16 FoodProto::containmentSet(void) {
	return InventoryProto::containmentSet() | isFood;
}

bool FoodProto::useAction(ObjectID dObj, ObjectID enactor) {
	return TRUE;
}

/* ==================================================================== *
   WearableProto class
 * ==================================================================== */

uint16 WearableProto::containmentSet(void) {
	return InventoryProto::containmentSet() | isWearable;
}

/* ==================================================================== *
   WeaponProto class
 * ==================================================================== */

weaponID WeaponProto::getWeaponID(void) {
	return weaponDamage;
}

uint16 WeaponProto::containmentSet(void) {
	return InventoryProto::containmentSet() | isWeapon;
}

//  return the address of the sprite when held in hand
Sprite *WeaponProto::getOrientedSprite(GameObject *obj, int16 offset) {
	return weaponSprites[ heldSpriteBase ]->sprite(offset);
}

//-----------------------------------------------------------------------
//	Returns TRUE if object in continuous use.

bool WeaponProto::isObjectBeingUsed(GameObject *obj) {
	ObjectID        wielder = obj->possessor();

	if (wielder != Nothing) {
		Actor *a = (Actor *)GameObject::objectAddress(wielder);

		if (a->rightHandObject == obj->thisID()
		        ||  a->leftHandObject == obj->thisID())
			return TRUE;
	}
	return FALSE;
}

/* ==================================================================== *
   MeleeWeaponProto
 * ==================================================================== */

//  Place weapon into right hand
bool MeleeWeaponProto::useAction(ObjectID dObj, ObjectID enactor) {
	assert(isObject(dObj));
	assert(isActor(enactor));

	GameObject  *dObjPtr = GameObject::objectAddress(dObj);
	Actor       *a = (Actor *)GameObject::objectAddress(enactor);

	if (enactor != dObjPtr->IDParent()) return FALSE;

	if (dObj == a->rightHandObject)
		a->holdInRightHand(Nothing);
	else {
		GameObject      *leftHandObjectPtr;
		ProtoObj        *leftHandProto;

		leftHandObjectPtr = a->leftHandObject != Nothing
		                    ?   GameObject::objectAddress(a->leftHandObject)
		                    :   NULL;

		if (dObjPtr->proto()->isTwoHanded(enactor)
		        || (leftHandObjectPtr != NULL
		            &&  leftHandObjectPtr->proto()->isTwoHanded(enactor)))
			a->holdInLeftHand(Nothing);

		a->holdInRightHand(dObj);
	}

	return TRUE;
}

bool MeleeWeaponProto::useOnAction(
    ObjectID dObj,
    ObjectID enactor,
    ObjectID item) {
	if (item == enactor)   //If Trying To Hurt Oneself Stop It!!!
		return FALSE;


	return strike(dObj, enactor, item);
}

bool MeleeWeaponProto::strikeAction(
    ObjectID dObj,
    ObjectID enactor,
    ObjectID item) {
	assert(isObject(dObj));
	assert(isActor(enactor));
	assert(isObject(item) || isActor(item));

	GameObject      *itemPtr = GameObject::objectAddress(item);
	ObjectSoundFXs  *soundFXs;
	Actor           *a = (Actor *)GameObject::objectAddress(enactor);
	Location        ol = Location(a->getWorldLocation(), a->IDParent());

	if (itemPtr->acceptStrike(enactor, dObj, getSkillValue(enactor)))
		return TRUE;

	soundFXs = &objectSoundFXTable[ soundFXClass ];

	makeCombatSound(soundFXs->soundFXMissed, ol);
	return FALSE;
}

bool MeleeWeaponProto::damageAction(
    ObjectID dObj,
    ObjectID enactor,
    ObjectID target) {
	assert(isObject(dObj));
	assert(isActor(enactor));
	assert(isObject(target) || isActor(target));

	Actor           *a = (Actor *)GameObject::objectAddress(enactor);
	ActorAttributes *effStats = a->getStats();
	WeaponStuff     *ws = &getWeapon(getWeaponID());
	GameObject      *targetPtr = GameObject::objectAddress(target);
	uint8           damageSoundID;
	Location        ol = Location(a->getWorldLocation(), a->IDParent());

	damageSoundID = targetPtr->proto()->getDamageSound(
	                    objectSoundFXTable[ soundFXClass ]);

	if (damageSoundID != 0)
		makeCombatSound(damageSoundID, ol);

	ws->implement(
	    a,
	    targetPtr,
	    GameObject::objectAddress(dObj),
	    effStats->getSkillLevel(skillIDBrawn));

	return TRUE;
}

bool MeleeWeaponProto::acceptDamageAction(
    ObjectID,
    ObjectID,
    int8,
    effectDamageTypes   dType,
    int8,
    uint8,
    int8) {
	return TRUE;
}

//  Determine if this type of weapon must be wielded with two hands
//  for the specified actor
bool MeleeWeaponProto::isTwoHanded(ObjectID attackerID) {
	assert(isActor(attackerID));

	Actor       *attackerPtr = (Actor *)GameObject::objectAddress(attackerID);
	ActorProto  *attackerProto = (ActorProto *)attackerPtr->proto();

	//  This weapon must be wielded in two hands if its bulk is greater
	//  than a quarter of the bulk of the wielder or if the actor does not
	//  have one handed fighing animation.
	return      !attackerPtr->isActionAvailable(actionSwingHigh)
	            ||  bulk > attackerProto->bulk / 4;
}

//  Initiate a melee weapon attack motion
void MeleeWeaponProto::initiateAttack(ObjectID attacker, ObjectID target) {
	assert(isActor(attacker));
	assert(isObject(target) || isActor(target));

	Actor       *attackerPtr = (Actor *)GameObject::objectAddress(attacker);
	GameObject  *targetPtr = GameObject::objectAddress(target);

	//  Start the attack motion
	if (isTwoHanded(attacker))
		MotionTask::twoHandedSwing(*attackerPtr, *targetPtr);
	else
		MotionTask::oneHandedSwing(*attackerPtr, *targetPtr);
}

//  Initiate a melee weapon parry motion
void MeleeWeaponProto::initiateDefense(
    ObjectID defensiveObj,
    ObjectID defender,
    ObjectID attacker) {
	assert(isObject(defensiveObj));
	assert(isActor(defender));
	assert(isActor(attacker));

	GameObject  *weapon = GameObject::objectAddress(defensiveObj);
	Actor       *defenderPtr = (Actor *)GameObject::objectAddress(defender),
	             *attackerPtr = (Actor *)GameObject::objectAddress(attacker);

	if (isTwoHanded(defender))
		MotionTask::twoHandedParry(*defenderPtr, *weapon, *attackerPtr);
	else
		MotionTask::oneHandedParry(*defenderPtr, *weapon, *attackerPtr);
}

//  Melee weapons can block an attack
bool MeleeWeaponProto::canBlock(void) {
	return TRUE;
}

//  Return a mask of bits indicating the directions relative to the
//  wielders facing in which this object can defend
uint8 MeleeWeaponProto::defenseDirMask(void) {
	return 1 << dirUp;
}

//-----------------------------------------------------------------------
//	Rate this weapon's goodness for a specified attack situation

uint8 MeleeWeaponProto::weaponRating(
    ObjectID weaponID,
    ObjectID wielderID,
    ObjectID targetID) {
	assert(isActor(wielderID));
	assert(isObject(targetID) || isActor(targetID));

	Actor       *wielder = (Actor *)GameObject::objectAddress(wielderID);

	//  If the wielder is on screen yet does not have the attack frames
	//  for this weapon then this weapon is useless
	if (wielder->appearance != NULL
	        &&  !wielder->isActionAvailable(fightStanceAction(wielderID)))
		return 0;

	GameObject  *target = GameObject::objectAddress(targetID);
	int16       dist = (target->getLocation() - wielder->getLocation()).quickHDistance();
	uint8       rating = 0;

	if (dist < maximumRange) rating += inRangeRatingBonus;
	//  Add in the value of the appropriate skill1
	rating += getSkillValue(wielderID);

	return rating;
}

// ------------------------------------------------------------------------
//	Return the fight stance approriate to this weapon

int16 MeleeWeaponProto::fightStanceAction(ObjectID actor) {
	return isTwoHanded(actor) ? actionTwoHandSwingHigh : actionSwingHigh;
}

// ------------------------------------------------------------------------
//	Given an object sound effect record, which sound should be made
//	when this object is damaged

uint8 MeleeWeaponProto::getDamageSound(const ObjectSoundFXs &soundFXs) {
	return soundFXs.soundFXParried;
}

//-----------------------------------------------------------------------
//	Determine if the specified object's 'use' slot is available within the
//	specified actor

bool MeleeWeaponProto::useSlotAvailable(GameObject *obj, Actor *a) {
	assert(isObject(obj) && obj->proto() == this);
	assert(isActor(a));

	if (a->rightHandObject == Nothing) {
		if (a->leftHandObject != Nothing) {
			assert(isObject(a->leftHandObject));

			GameObject      *leftHandObjectPtr;

			leftHandObjectPtr = GameObject::objectAddress(a->leftHandObject);
			return      !isTwoHanded(a->thisID())
			            &&  !leftHandObjectPtr->proto()->isTwoHanded(a->thisID());
		}
		return TRUE;
	}
	assert(isObject(a->rightHandObject));

	return FALSE;
}

/* ==================================================================== *
   BludgeoningWeaponProto
 * ==================================================================== */

//-----------------------------------------------------------------------
//	Get the value of the wielder's skill which applies to this weapon

uint8 BludgeoningWeaponProto::getSkillValue(ObjectID enactor) {
	assert(isActor(enactor));

	Actor               *a;
	ActorAttributes     *effStats;

	a = (Actor *)GameObject::objectAddress(enactor);
	effStats = a->getStats();

	return effStats->getSkillLevel(skillIDBludgeon);
}

// ------------------------------------------------------------------------
//	Cause the user's associated skill to grow

void BludgeoningWeaponProto::applySkillGrowth(ObjectID enactor, uint8 points) {
	assert(isActor(enactor));

	PlayerActorID       playerID;

	if (actorIDToPlayerID(enactor, playerID)) {
		PlayerActor     *player = getPlayerActorAddress(playerID);

		player->skillAdvance(skillIDBludgeon, points);

		if (g_vm->_rnd->getRandomNumber(65534) & 1)
			player->skillAdvance(skillIDBrawn, points);
	}
}

/* ==================================================================== *
   SlashingWeaponProto
 * ==================================================================== */

//-----------------------------------------------------------------------
//	Get the value of the wielder's skill which applies to this weapon

uint8 SlashingWeaponProto::getSkillValue(ObjectID enactor) {
	assert(isActor(enactor));

	Actor               *a;
	ActorAttributes     *effStats;

	a = (Actor *)GameObject::objectAddress(enactor);
	effStats = a->getStats();

	return effStats->getSkillLevel(skillIDSwordcraft);
}

// ------------------------------------------------------------------------
//	Cause the user's associated skill to grow

void SlashingWeaponProto::applySkillGrowth(ObjectID enactor, uint8 points) {
	assert(isActor(enactor));

	PlayerActorID       playerID;

	if (actorIDToPlayerID(enactor, playerID)) {
		PlayerActor     *player = getPlayerActorAddress(playerID);

		player->skillAdvance(skillIDSwordcraft, points);

		if (g_vm->_rnd->getRandomNumber(65534) & 1)
			player->skillAdvance(skillIDBrawn, points);
	}
}

/* ==================================================================== *
   BowProto
 * ==================================================================== */

bool BowProto::useAction(ObjectID dObj, ObjectID enactor) {
	assert(isObject(dObj));
	assert(isActor(enactor));

	GameObject  *dObjPtr = GameObject::objectAddress(dObj);
	Actor       *a = (Actor *)GameObject::objectAddress(enactor);

	if (enactor != dObjPtr->IDParent()) return FALSE;

	//  If this object is in the enactor's left hand remove it else
	//  place it into his left hand
	if (a->leftHandObject == dObj)
		a->holdInLeftHand(Nothing);
	else {
		a->holdInRightHand(Nothing);
		a->holdInLeftHand(dObj);
	}

	return TRUE;
}

//  Bows are two handed
bool BowProto::isTwoHanded(ObjectID) {
	return TRUE;
}

//  Initiate the bow firing motion
void BowProto::initiateAttack(ObjectID attacker, ObjectID target) {
	assert(isActor(attacker));
	assert(isObject(target) || isActor(target));

	Actor       *attackerPtr = (Actor *)GameObject::objectAddress(attacker);
	GameObject  *targetPtr = GameObject::objectAddress(target);

	MotionTask::fireBow(*attackerPtr, *targetPtr);
}

//  Grab an arrow from the actor's inventory
GameObject *BowProto::getProjectile(ObjectID weapon, ObjectID enactor) {
	assert(isObject(weapon));
	assert(isActor(enactor));

	GameObject          *obj,
	                    *arrow = NULL;
	Actor               *a = (Actor *)GameObject::objectAddress(enactor);
	TilePoint           bestSlot(maxint16, maxint16, 0);
	ContainerIterator   iter(a);

	while (iter.next(&obj) != Nothing) {
		//  Look for objects which are arrows
		if (obj->proto()->classType == protoClassArrow) {
			TilePoint   objSlot = obj->getLocation();

			if (objSlot.u < bestSlot.u
			        || (objSlot.u == bestSlot.u
			            &&  objSlot.v < bestSlot.v)) {
				bestSlot = objSlot;
				arrow = obj;
			}
		}
	}

	return arrow;
}

//-----------------------------------------------------------------------
//	Determine if the specified object's 'use' slot is available within the
//	specified actor

bool BowProto::useSlotAvailable(GameObject *obj, Actor *a) {
	assert(isObject(obj) && obj->proto() == this);
	assert(isActor(a));

	return a->leftHandObject == Nothing && a->rightHandObject == Nothing;
}

//-----------------------------------------------------------------------
//	Rate this weapon's goodness for a specified attack situation

uint8 BowProto::weaponRating(
    ObjectID weaponID,
    ObjectID wielderID,
    ObjectID targetID) {
	assert(isActor(wielderID));
	assert(isObject(targetID) || isActor(targetID));

	if (getProjectile(weaponID, wielderID) == NULL) return 0;

	Actor       *wielder = (Actor *)GameObject::objectAddress(wielderID);

	//  If the wielder is on screen yet does not have the attack frames
	//  for this weapon then this weapon is useless
	if (wielder->appearance != NULL
	        &&  !wielder->isActionAvailable(fightStanceAction(wielderID)))
		return 0;

	GameObject  *target = GameObject::objectAddress(targetID);
	int16       dist = (target->getLocation() - wielder->getLocation()).quickHDistance();
	uint8       rating = 0;

	if (dist < maximumRange && !wielder->inReach(target->getLocation()))
		rating += inRangeRatingBonus;
	rating += wielder->getStats()->getSkillLevel(skillIDArchery);

	return rating;
}

// ------------------------------------------------------------------------
//	Return the fight stance approriate to this weapon

int16 BowProto::fightStanceAction(ObjectID actor) {
	return actionFireBow;
}

/* ==================================================================== *
   WeaponWandProto
 * ==================================================================== */

bool WeaponWandProto::useAction(ObjectID dObj, ObjectID enactor) {
	assert(isObject(dObj));
	assert(isActor(enactor));

	GameObject  *dObjPtr = GameObject::objectAddress(dObj);
	Actor       *a = (Actor *)GameObject::objectAddress(enactor);

	if (enactor != dObjPtr->IDParent()) return FALSE;

	//  If this object is in the enactor's left hand remove it else
	//  place it into his left hand
	if (a->leftHandObject == dObj)
		a->holdInLeftHand(Nothing);
	else {
		a->holdInRightHand(Nothing);
		a->holdInLeftHand(dObj);
	}

	return TRUE;
}

//  Wands are two handed
bool WeaponWandProto::isTwoHanded(ObjectID) {
	return TRUE;
}

//  Initiate the use wand motion
void WeaponWandProto::initiateAttack(ObjectID attacker, ObjectID target) {
	assert(isActor(attacker));
	assert(isObject(target) || isActor(target));

	Actor       *attackerPtr = (Actor *)GameObject::objectAddress(attacker);
	GameObject  *targetPtr = GameObject::objectAddress(target);

	MotionTask::useWand(*attackerPtr, *targetPtr);
}

//-----------------------------------------------------------------------
//	Determine if the specified object's 'use' slot is available within the
//	specified actor

bool WeaponWandProto::useSlotAvailable(GameObject *obj, Actor *a) {
	assert(isObject(obj) && obj->proto() == this);
	assert(isActor(a));

	return a->leftHandObject == Nothing && a->rightHandObject == Nothing;
}

//-----------------------------------------------------------------------
//	Rate this weapon's goodness for a specified attack situation

uint8 WeaponWandProto::weaponRating(
    ObjectID weaponID,
    ObjectID wielderID,
    ObjectID targetID) {
	assert(isObject(weaponID) || isActor(weaponID));
	assert(isActor(wielderID));
	assert(isObject(targetID) || isActor(targetID));

	Actor       *wielder = (Actor *)GameObject::objectAddress(wielderID);

	//  If the wielder is on screen yet does not have the attack frames
	//  for this weapon then this weapon is useless
	if (wielder->appearance != NULL
	        &&  !wielder->isActionAvailable(fightStanceAction(wielderID)))
		return 0;

	GameObject  *weapon = GameObject::objectAddress(weaponID),
	             *target = GameObject::objectAddress(targetID);
	int16       dist = (target->getLocation() - wielder->getLocation()).quickHDistance();
	uint8       rating = 0;

	if (weapon->IDChild() != Nothing) {
		SkillProto  *spellProto = (SkillProto *)GameObject::protoAddress(weapon->IDChild());
		SpellStuff  *spellStuff = &spellBook[ spellProto->getSpellID() ];
		ActorManaID manaType = (ActorManaID)spellStuff->getManaType();
		uint16      manaAmount = spellStuff->getManaAmt();

		if (!weapon->hasCharge(manaType, manaAmount)) return 0;
	} else
		return 0;

	if (dist < maximumRange && !wielder->inReach(target->getLocation()))
		rating += inRangeRatingBonus;
	rating += wielder->getStats()->getSkillLevel(skillIDSpellcraft);

	return rating;
}

// ------------------------------------------------------------------------
//	Return the fight stance approriate to this weapon

int16 WeaponWandProto::fightStanceAction(ObjectID actor) {
	return actionUseWand;
}

/* ==================================================================== *
   ProjectileProto class
 * ==================================================================== */

//-----------------------------------------------------------------------
//	return the address of the sprite when held in hand

Sprite *ProjectileProto::getOrientedSprite(GameObject *, int16) {
	return NULL;
}

//-----------------------------------------------------------------------
//	Returns TRUE if object in continuous use.

bool ProjectileProto::isObjectBeingUsed(GameObject *) {
	return FALSE;
}

//-----------------------------------------------------------------------
//	Rate this weapon's goodness for a specified attack situation

uint8 ProjectileProto::weaponRating(
    ObjectID weaponID,
    ObjectID wielderID,
    ObjectID targetID) {
	//  Projectiles are worthless as far as wieldable weapons
	return 0;
}

//  Projectiles are missiles
bool ProjectileProto::isMissile(void) {
	return TRUE;
}

/* ==================================================================== *
   ArrowProto class
 * ==================================================================== */

bool ArrowProto::useOnAction(ObjectID dObj, ObjectID enactor, ObjectID item) {
	//  Reuse the MeleeWeaponProto's useOnAction() function.
	return ((MeleeWeaponProto *)this)->MeleeWeaponProto::useOnAction(
	           dObj, enactor, item);
}

bool ArrowProto::strikeAction(
    ObjectID dObj,
    ObjectID enactor,
    ObjectID item) {
	assert(isObject(dObj));
	assert(isActor(enactor));
	assert(isObject(item) || isActor(item));

	Actor           *a = (Actor *)GameObject::objectAddress(enactor);
	GameObject      *itemPtr = GameObject::objectAddress(item);

	return  itemPtr->acceptStrike(
	            enactor,
	            dObj,
	            a->getStats()->getSkillLevel(skillIDArchery));
}

bool ArrowProto::damageAction(
    ObjectID dObj,
    ObjectID enactor,
    ObjectID target) {
	assert(isObject(dObj));
	assert(isActor(enactor));
	assert(isObject(target) || isActor(target));

	Actor           *a = (Actor *)GameObject::objectAddress(enactor);
	ActorAttributes *effStats = a->getStats();
	WeaponStuff     *ws = &getWeapon(getWeaponID());
	GameObject      *targetPtr = GameObject::objectAddress(target);
	uint8           damageSoundID;
	Location        al = Location(a->getLocation(), a->IDParent());

	damageSoundID = targetPtr->proto()->getDamageSound(
	                    objectSoundFXTable[ soundFXClass ]);

	if (damageSoundID != 0)
		makeCombatSound(damageSoundID, al);

	ws->implement(
	    a,
	    GameObject::objectAddress(target),
	    GameObject::objectAddress(dObj),
	    effStats->getSkillLevel(skillIDBrawn));

	return TRUE;
}

// ------------------------------------------------------------------------
//	Cause the user's associated skill to grow

void ArrowProto::applySkillGrowth(ObjectID enactor, uint8 points) {
	assert(isActor(enactor));

	PlayerActorID       playerID;

	if (actorIDToPlayerID(enactor, playerID)) {
		PlayerActor     *player = getPlayerActorAddress(playerID);

		player->skillAdvance(skillIDArchery, points);

		if (g_vm->_rnd->getRandomNumber(65534) & 1)
			player->skillAdvance(skillIDBrawn, points);
	}
}

/* ==================================================================== *
   ArmorProto class
 * ==================================================================== */

uint16 ArmorProto::containmentSet(void) {
	return InventoryProto::containmentSet() | isWearable | isArmor;
}

//  Compute how much damage this defensive object will absorb
uint8 ArmorProto::adjustDamage(uint8 damage) {
	//  Apply damage divider
	if (damageDivider != 0) damage /= damageDivider;

	//  Apply damage absorbtion
	if (damageAbsorbtion < damage)
		damage -= damageAbsorbtion;
	else
		damage = 0;

	return damage;
}

//-----------------------------------------------------------------------
//	Returns TRUE if object in continuous use.

bool ArmorProto::isObjectBeingUsed(GameObject *obj) {
	ObjectID    aID = obj->possessor();

	if (aID != Nothing) {
		Actor       *a = (Actor *)GameObject::objectAddress(aID);
		ObjectID    id = obj->thisID();

		for (int i = 0; i < ARMOR_COUNT; i++) {
			if (a->armorObjects[ i ] == id) return TRUE;
		}
	}
	return FALSE;
}

//-----------------------------------------------------------------------
//	Determine if the specified object's 'use' slot is available within the
//	specified actor

bool ArmorProto::useSlotAvailable(GameObject *obj, Actor *a) {
	assert(isObject(obj) || obj->proto() == this);
	assert(isActor(a));

	return a->armorObjects[ whereWearable ] == Nothing;
}

//-----------------------------------------------------------------------
//	"Wear" a piece of armor.

bool ArmorProto::useAction(ObjectID dObj, ObjectID enactor) {
	assert(isObject(dObj));
	assert(isActor(enactor));
	PlayerActorID   pID;

	Actor       *a = (Actor *)GameObject::objectAddress(enactor);
	GameObject  *obj = GameObject::objectAddress(dObj);

	assert(obj->proto() == this);

	if (enactor != obj->IDParent()) return FALSE;

	int16       slot = whereWearable;

	if (a->armorObjects[ slot ] == dObj)
		a->wear(Nothing, slot);
	else
		a->wear(dObj, slot);

	globalContainerList.setUpdate(obj->IDParent());

	return TRUE;
}

/* ==================================================================== *
   ShieldProto class
 * ==================================================================== */

uint16 ShieldProto::containmentSet(void) {
	return InventoryProto::containmentSet() | isWearable | isArmor;
}

//  Place shield into left hand
bool ShieldProto::useAction(ObjectID dObj, ObjectID enactor) {
	assert(isObject(dObj));
	assert(isActor(enactor));

	GameObject  *dObjPtr = GameObject::objectAddress(dObj);
	Actor       *a = (Actor *)GameObject::objectAddress(enactor);

	if (enactor != dObjPtr->IDParent()) return FALSE;

	if (a->rightHandObject != Nothing) {
		assert(isObject(a->rightHandObject));
		GameObject  *rightHandObjectPtr =
		    GameObject::objectAddress(a->rightHandObject);

		if (rightHandObjectPtr->proto()->isTwoHanded(enactor))
			return FALSE;
	}

	a->holdInLeftHand(dObj != a->leftHandObject ? dObj : Nothing);

	return TRUE;
}

bool ShieldProto::acceptDamageAction(
    ObjectID,
    ObjectID,
    int8,
    effectDamageTypes   dType,
    int8,
    uint8,
    int8) {
	return TRUE;
}

Sprite *ShieldProto::getOrientedSprite(GameObject *obj, int16 offset) {
	return weaponSprites[heldSpriteBase]->sprite(offset);
}

//  Initiate a shield parrying motion
void ShieldProto::initiateDefense(
    ObjectID defensiveObj,
    ObjectID defender,
    ObjectID attacker) {
	assert(isObject(defensiveObj));
	assert(isActor(defender));
	assert(isActor(attacker));

	GameObject  *shield = GameObject::objectAddress(defensiveObj);
	Actor       *defenderPtr = (Actor *)GameObject::objectAddress(defender),
	             *attackerPtr = (Actor *)GameObject::objectAddress(attacker);

	MotionTask::shieldParry(*defenderPtr, *shield, *attackerPtr);
}


//  Shields can block an attack
bool ShieldProto::canBlock(void) {
	return TRUE;
}

//  Return a mask of bits indicating the directions relative to the
//  wielders facing in which this object can defend
uint8 ShieldProto::defenseDirMask(void) {
	return (1 << dirUp) | (1 << dirUpLeft);
}

//-----------------------------------------------------------------------
//	Returns TRUE if object in continuous use.

bool ShieldProto::isObjectBeingUsed(GameObject *obj) {
	ObjectID        wielder = obj->possessor();

	if (wielder != Nothing) {
		Actor *a = (Actor *)GameObject::objectAddress(wielder);

		if (a->rightHandObject == obj->thisID()
		        ||  a->leftHandObject == obj->thisID())
			return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------
//	Determine if the specified object's 'use' slot is available within the
//	specified actor

bool ShieldProto::useSlotAvailable(GameObject *obj, Actor *a) {
	assert(isObject(obj) || obj->proto() == this);
	assert(isActor(a));

	if (a->leftHandObject == Nothing) {
		if (a->rightHandObject != Nothing) {
			assert(isObject(a->rightHandObject));

			GameObject      *rightHandObjectPtr;

			rightHandObjectPtr = GameObject::objectAddress(a->rightHandObject);
			return !rightHandObjectPtr->proto()->isTwoHanded(a->thisID());
		}

		return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------
//	Get the value of the user's skill which applies to this object

uint8 ShieldProto::getSkillValue(ObjectID enactor) {
	assert(isActor(enactor));

	Actor               *a;
	ActorAttributes     *effStats;

	a = (Actor *)GameObject::objectAddress(enactor);
	effStats = a->getStats();

	return effStats->getSkillLevel(skillIDShieldcraft);
}

// ------------------------------------------------------------------------
//	Cause the user's associated skill to grow

void ShieldProto::applySkillGrowth(ObjectID enactor, uint8 points) {
	assert(isActor(enactor));

	PlayerActorID       playerID;

	if (actorIDToPlayerID(enactor, playerID)) {
		PlayerActor     *player = getPlayerActorAddress(playerID);

		player->skillAdvance(skillIDShieldcraft, points);

		if (g_vm->_rnd->getRandomNumber(65534) & 1)
			player->skillAdvance(skillIDBrawn, points);
	}
}

// ------------------------------------------------------------------------
//	Given an object sound effect record, which sound should be made
//	when this object is damaged

uint8 ShieldProto::getDamageSound(const ObjectSoundFXs &soundFXs) {
	return soundFXs.soundFXParried;
}

/* ==================================================================== *
   ToolProto class
 * ==================================================================== */

//  Put tool into mouse with intention to use
bool ToolProto::setUseCursor(ObjectID dObj) {
	assert(mouseInfo.getObjectId() == Nothing);
	mouseInfo.copyObject(GameObject::objectAddress(dObj), GrabInfo::Use);
	return TRUE;
}

bool ToolProto::useOnAction(ObjectID, ObjectID, ObjectID) {
	return TRUE;
}

/* ==================================================================== *
   DocumentProto class
 * ==================================================================== */

uint16 DocumentProto::containmentSet(void) {
	return InventoryProto::containmentSet() | isDocument;
}

/* ==================================================================== *
   BookProto class
 * ==================================================================== */

bool BookProto::useAction(ObjectID dObj, ObjectID enactor) {
	GameObject  *bookObj = GameObject::objectAddress(dObj);

	// open the modal book with text filled in with the previously run script
	switch (appearanceType) {
	case 0:
		openBook(bookObj->getExtra());
		break;
	case 1:
		openScroll(bookObj->getExtra());
		break;
	case 2:
		openParchment(bookObj->getExtra());
		break;
	}

	return TRUE;
}

/* ==================================================================== *
   ScrollProto class
 * ==================================================================== */

bool ScrollProto::useAction(ObjectID dObj, ObjectID enactor) {
	GameObject  *bookObj = GameObject::objectAddress(dObj);

	openScroll(bookObj->getExtra());     // open the modal book with text filled in with
	// the previously run script
	return TRUE;
}

/* ==================================================================== *
   AutoMapProto class
 * ==================================================================== */

bool AutoMapProto::openAction(ObjectID, ObjectID) {
	return FALSE;
}

/* ==================================================================== *
   IntangibleObjProto class
 * ==================================================================== */

uint16 IntangibleObjProto::containmentSet(void) {
	return isIntangible;
}

bool IntangibleObjProto::useAction(ObjectID dObj, ObjectID enactor) {
	assert(isObject(dObj));

	/*  GameObject *obj = GameObject::objectAddress(dObj);

	    if(obj->isAlias()) //This Tells Whether Its A Copy Or Not
	        grabTangible(dObj);//Set To Use If Its The Copy
	*/
	return FALSE;
}

bool IntangibleObjProto::takeAction(ObjectID dObj, ObjectID enactor, int16) {
	assert(isObject(dObj));
	assert(mouseInfo.getObjectId() == Nothing);

	GameObject      *dObjPtr = GameObject::objectAddress(dObj);

	if (dObjPtr->isTrueSkill())
		return FALSE;

	mouseInfo.copyObject(dObj);

	return TRUE;
}

bool IntangibleObjProto::canDropAt(
    ObjectID,
    ObjectID,
    const Location  &loc) {
	//  We can try dropping this object anywhere, except within a world
	return !isWorld(loc.context);
}

bool IntangibleObjProto::dropAction(
    ObjectID        dObj,
    ObjectID        enactor,
    const Location  &loc,
    int16) {
	assert(isObject(dObj));
	assert(loc.context != Nothing);
	assert(!isWorld(loc.context));

	GameObject  *container = GameObject::objectAddress(loc.context);

	if (container->canContain(dObj)) {
		GameObject  *dObjPtr = GameObject::objectAddress(dObj);
		ObjectID    newObj;

		if ((newObj = dObjPtr->makeAlias(Location(dObjPtr->getLocation(), dObjPtr->IDParent()))) != Nothing) {
			if (container->acceptInsertionAt(enactor, newObj, loc))
				return TRUE;
			else
				GameObject::objectAddress(newObj)->deleteObject();
		}
	}

	return FALSE;
}

bool IntangibleObjProto::acceptDropAction(
    ObjectID dObj,
    ObjectID enactor,
    ObjectID droppedObj,
    int) {
	assert(isObject(dObj));

	GameObject  *dObjPtr = GameObject::objectAddress(dObj);

	if (dObjPtr->isAlias()) {
		GameObject      *droppedObjPtr =
		    GameObject::objectAddress(droppedObj);
		Location        loc(dObjPtr->getLocation(), dObjPtr->IDParent());

		dObjPtr->deleteObject();
		return droppedObjPtr->drop(enactor, loc);
	}

	return FALSE;
}

ObjectID IntangibleObjProto::placeObject(void) {
	//return Container That It Inserted Itself Into
	return 2;
}

//  Builds an identity color translation table for intagible objects
void IntangibleObjProto::getColorTranslation(ColorTable map) {
	memcpy(map, identityColors, sizeof(ColorTable));
	/*
	    uint8 color = 0;

	    do {
	        map[ color ] = color;
	    } while ( ++color != 0 );
	*/
}

//  Return the sprite data
ObjectSpriteInfo IntangibleObjProto::getSprite(
    GameObject *obj,
    enum spriteTypes spr,
    int16) {
	ObjectSpriteInfo    sprInfo = { NULL, FALSE };

	switch (spr) {
	case objOnGround:
		sprInfo.sp = mentalSprites->sprite(groundSprite);
		break;

	case objInContainerView:
	case objAsMousePtr:
		sprInfo.sp = mentalSprites->sprite(iconSprite);
	}
	return sprInfo;
}


/* ==================================================================== *
   IdeaProto class
 * ==================================================================== */

uint16 IdeaProto::containmentSet(void) {
	//Maybe I Could Use This ID And Call IntanobjProt For Setting IsIntangible
	return isConcept | isIntangible;
}

/* ==================================================================== *
   MemoryProto class
 * ==================================================================== */

uint16 MemoryProto::containmentSet(void) {
	//Maybe I Could Use This ID And Call IntanobjProt For Setting IsIntangible
	return isConcept | isIntangible;
}

/* ==================================================================== *
   PsychProto class
 * ==================================================================== */

uint16 PsychProto::containmentSet(void) {
	//Maybe I Could Use This ID And Call IntanobjProt For Setting IsIntangible
	return isPsych | isIntangible;
}

/* ==================================================================== *
   SkillProto class
 * ==================================================================== */


uint16 SkillProto::containmentSet(void) {
	//Maybe I Could Use This ID And Call IntanobjProt For Setting IsIntangible
	return isSkill | isIntangible;
}

bool SkillProto::useAction(ObjectID dObj, ObjectID enactor) {
	//GameObject    *spellPtr = GameObject::objectAddress( dObj );
	SpellStuff &sp = spellBook[getSpellID()];

	if (nonUsable(this))
		return FALSE;

	if (nonTargeted(this)) {
		Actor   *attackerPtr = (Actor *) GameObject::objectAddress(enactor);
		return castUntargetedSpell(attackerPtr, this);
	}
	mouseInfo.copyObject(dObj, GrabInfo::Use);
	return TRUE;
}

// cast a skill at various things

bool SkillProto::useOnAction(ObjectID dObj, ObjectID enactor, ObjectID withObj) {
	Actor       *attackerPtr = (Actor *) GameObject::objectAddress(enactor);
	GameObject  *targetPtr = GameObject::objectAddress(withObj);
	//              *spellPtr = GameObject::objectAddress( dObj );
	return castSpell(attackerPtr, targetPtr, this);
}

bool SkillProto::useOnAction(ObjectID dObj, ObjectID enactor, ActiveItem *item) {
	Actor       *attackerPtr = (Actor *) GameObject::objectAddress(enactor);
	//GameObject    *spellPtr = GameObject::objectAddress( dObj );
	return castSpell(attackerPtr, item, this);
}

bool SkillProto::useOnAction(ObjectID dObj, ObjectID enactor, const Location &loc) {
	Actor       *attackerPtr = (Actor *) GameObject::objectAddress(enactor);
	Location    l = loc;
	//GameObject    *spellPtr = GameObject::objectAddress( dObj );
	return castSpell(attackerPtr, l, this);
}

bool SkillProto::canDropAt(ObjectID, ObjectID, const Location &) {
	return TRUE;
}

bool SkillProto::dropAction(ObjectID dObj,  ObjectID enactor, const Location &loc, int16 num) {
	assert(isActor(enactor));

	if (isWorld(loc.context)) {
		Actor       *enactorPtr = (Actor *)GameObject::objectAddress(enactor);

		if (validTarget(enactorPtr, NULL, NULL, this))
			return useOn(dObj, enactor, loc);

		return FALSE;
	}

	return IntangibleObjProto::dropAction(dObj, enactor, loc, num);
}

bool SkillProto::dropOnAction(ObjectID dObj, ObjectID enactor, ObjectID target, int count) {
	assert(isActor(enactor));
	assert(isObject(target) || isActor(target));

	GameObject      *targetPtr = GameObject::objectAddress(target);

	if (isWorld(targetPtr->IDParent())) {
		Actor       *enactorPtr = (Actor *)GameObject::objectAddress(enactor);

		if (validTarget(enactorPtr, targetPtr, NULL, this))
			return useOn(dObj, enactor, target);
	}

	return IntangibleObjProto::dropOnAction(dObj, enactor, target, count);
}

bool SkillProto::dropOnAction(
    ObjectID        dObj,
    ObjectID        enactor,
    ActiveItem      *target,
    const Location  &loc,
    int16           num) {
	assert(isActor(enactor));

	if (target != NULL) {
		Actor       *enactorPtr = (Actor *)GameObject::objectAddress(enactor);

		if (validTarget(enactorPtr, NULL, target, this))
			return useOn(dObj, enactor, target);
	}

	return IntangibleObjProto::dropOnAction(dObj, enactor, target, loc, num);
}

bool SkillProto::implementAction(SpellID dObj, ObjectID enactor, ObjectID withObj) {
	Actor       *attackerPtr = (Actor *) GameObject::objectAddress(enactor);
	GameObject  *targetPtr = GameObject::objectAddress(withObj);
	//              *spellPtr = GameObject::objectAddress( dObj );
	return implementSpell(attackerPtr, targetPtr, this);
}

bool SkillProto::implementAction(SpellID dObj, ObjectID enactor, ActiveItem *item) {
	Actor       *attackerPtr = (Actor *) GameObject::objectAddress(enactor);
	//GameObject    *spellPtr = GameObject::objectAddress( dObj );
	return implementSpell(attackerPtr, item, this);
}

bool SkillProto::implementAction(SpellID dObj, ObjectID enactor, Location &loc) {
	Actor       *attackerPtr = (Actor *) GameObject::objectAddress(enactor);
	//GameObject    *spellPtr = GameObject::objectAddress( dObj );
	return implementSpell(attackerPtr, loc, this);
}


/* ==================================================================== *
   EnchantmentProto class
 * ==================================================================== */

uint16 EnchantmentProto::containmentSet(void) {
	return isEnchantment;
}

// ------------------------------------------------------------------------
//	Background update function, called once every few seconds

void EnchantmentProto::doBackgroundUpdate(GameObject *obj) {
	int16       hitPoints   = obj->getHitPoints();  // get hitpoints of enchant
	GameObject  *parentObj  = obj->parent();        // get parent of enchantment

	assert(parentObj);

	// if this is a poison enchantment
	// then hurt the victim
	if (parentObj && isActor(parentObj)) {
		// get the enchantment type
		uint16 flags = obj->getExtra();
		uint16  type = getEnchantmentType(flags),
		        subType = getEnchantmentSubType(flags);

		if (type == effectOthers && subType == actorPoisoned) {
			// get the damage amount for this poison
			int16 damage = getEnchantmentAmount(flags);

			// apply the damage
			parentObj->acceptDamage(obj->thisID(), damage, damagePoison);
		}
	}

	// if the enchantment does not hemorage
	// away mana, it does'nt go away ( oh no mr.bill! )
	if (hitPoints == Forever) return;

	hitPoints -= 1;
	if (hitPoints <= 0) {
		// delete the now dead enchantment
		obj->deleteObject();

		if (parentObj) {
			parentObj->evalEnchantments();
		}
	} else {
		obj->setHitPoints(hitPoints);
	}
}

/*
ContainerWindow *EnchantmentProto::makeWindow( GameObject *Obj )
{
    ContainerWindow *window;

    uint32 contContextID = RES_ID( 'C', 'O', 'N', 'T' );

    ButtonInfoStruct    CloseInfo( entCloseBtnRect,
                                   contContextID,
                                   'E', 'C', 'L',
                                   0, 1 ),

                        ScrollInfo( entScrollBtnRect,
                                    contContextID,
                                    'E', 'S', 'L',
                                    0, 1 );

    window = new EnchContainerWindow(

                            // the obj
                        Obj,

                            // rect of the window
                        physWindowRect,

                            // start position of container hot spot section
                        entHotSpotXY,

                            // object drawing information
                        entObjectDisplayRect,

                            // gauge image information
                        gaugesImageInfo,
                        weightPieImageInfo,
                        encumPieImageInfo,

                            // button information
                        CloseInfo,
                        ScrollInfo,

                            // icon positioning
                        Point16( physIconOriginX, physIconOriginY ),
                        Point16( physIconSpaceX, physIconSpaceY ),
                        2,  //Rows
                        2,  //Cols
                        4 );//Total Rows


        // init the resource context handle
    hResContext *decRes = resFile->newContext( contContextID,
                                                "enchant container window resource" );


        // set the decorations for this window
    window->setDecorations( enchantDecorations,
                            elementsof( enchantDecorations ),
                            decRes, 'E', 'F', 'R' );


    resFile->disposeContext( decRes );
    decRes = NULL;

    return window;
}
*/


/* ======================================================================== *
   GeneratorProto
 * ======================================================================== */

uint16 GeneratorProto::containmentSet(void) {
	return isIntangible;
}

/* ======================================================================== *
   MonsterGeneratorProto
 * ======================================================================== */

/* ======================================================================== *
   EncounterGeneratorProto
 * ======================================================================== */

//  Generate an encounter at approx. 10-second intervals
void EncounterGeneratorProto::doBackgroundUpdate(GameObject *obj) {
	Actor           *centerActor = getCenterActor();
	PlayerActor     *playerActor;

	Location        generatorLoc;           //  World position of this object
	LivingPlayerActorIterator iter;

	//  REM: Add code to disable this generator if there are too many
	//  hostiles on the screen

	//  Get the world that the object is in, and the location of the object
	//  within the world.
	obj->getWorldLocation(generatorLoc);

	//  Iterate through all living player actors
	for (playerActor = iter.first(); playerActor; playerActor = iter.next()) {
		Actor       *a = playerActor->getActor();
		Location    actorLoc;

		a->getWorldLocation(actorLoc);

		//  If actor is in the same world as the generator
		if (actorLoc.context == generatorLoc.context) {
			int32   dist,
			        mtRadius = obj->getHitPoints(),// Radius in metatiles
			        ptRadius = mtRadius * tileUVSize * platformWidth,
			        prob = obj->getExtra() * (256 * 256) / 100;

			TilePoint   diff = (TilePoint)actorLoc - (TilePoint)generatorLoc;

			//  Compute the distance between the actor and the generator
			dist = diff.quickHDistance();

			//  Determine distance from center of
//			prob = (ptRadius - dist) * prob / (ptRadius * mtRadius);

			// avoid divde by zeros
			if (ptRadius == 0) {
				return;
			}

			// prevent negtive distance from generator
			if (dist > ptRadius) {
				return;
			}

			prob = (ptRadius - dist) * prob / ptRadius;

			if (a == centerActor) prob /= 2;
			else prob /= 4;

			//  Now, roll to see if we got an encounter!

			if ((g_vm->_rnd->getRandomNumber(65534) & 0x0000ffff) < prob) {
				scriptCallFrame scf;

#if DEBUG
				WriteStatusF(8, "Encounter %d Triggered!", obj->thisID());
#endif

				scf.invokedObject   = obj->thisID();
				scf.enactor         = a->thisID();
				scf.directObject    = scf.invokedObject;
				scf.indirectObject  = Nothing;
				scf.value           = dist / tileUVSize;

				//  Call the SAGA script, if there is one.
				runObjectMethod(obj->thisID(), Method_GameObject_onTrigger, scf);
				return;
			}
		}
	}
}

/* ======================================================================== *
   MissionGeneratorProto
 * ======================================================================== */

//  Generate an encounter at approx. 10-second intervals
void MissionGeneratorProto::doBackgroundUpdate(GameObject *obj) {
}

/* ==================================================================== *
   IntangibleContainerProto class
 * ==================================================================== */

bool IntangibleContainerProto::canContain(ObjectID dObj, ObjectID item) {
	assert(isObject(item));

	GameObject      *itemPtr = GameObject::objectAddress(item);

	return (itemPtr->containmentSet() & (isSkill | isConcept)) != 0;
}

bool IntangibleContainerProto::useAction(ObjectID dObj, ObjectID enactor) {
	bool          result;
	GameObject    *dObjPtr = GameObject::objectAddress(dObj);

	if (dObjPtr->objectFlags & objectOpen)
		result = close(dObj, enactor);
	else
		result = open(dObj, enactor);

	return result;
}


//  Determine if this intagible container can be opened
bool IntangibleContainerProto::canOpen(ObjectID dObj, ObjectID) {
	GameObject *dObjPtr = GameObject::objectAddress(dObj);

	return !dObjPtr->isOpen();
}

//  Open a intangible container
bool IntangibleContainerProto::openAction(ObjectID dObj, ObjectID enactor) {
	ContainerNode       *cn;
	GameObject          *dObjPtr = GameObject::objectAddress(dObj);

	//  Perform appropriate opening tasks
	cn = CreateContainerNode(enactor, FALSE);
	cn->markForShow();
//	dObjPtr->objectFlags |= GameObject::objectOpen;          //  Set open bit;

	return TRUE;
}

bool IntangibleContainerProto::closeAction(ObjectID dObj, ObjectID) {
	GameObject      *dObjPtr = GameObject::objectAddress(dObj);
	ContainerNode   *cn = globalContainerList.find(dObj, ContainerNode::mentalType);

	assert(cn);

	//  Mark container for lazy deletion
	cn->markForDelete();

	//  Clear open bit
//	dObjPtr->objectFlags &= ~GameObject::objectOpen;

	return TRUE;
}

uint16 IntangibleContainerProto::containmentSet(void) {
	return isContainer | isIntangible;
}
/* ==================================================================== *
   IdeaContainerProto class
 * ==================================================================== */

/* ==================================================================== *
   MemoryContainerProto class
 * ==================================================================== */

/* ==================================================================== *
   PsychContainerProto class
 * ==================================================================== */

/* ==================================================================== *
   SkillContainerProto class
 * ==================================================================== */

/* ==================================================================== *
   MindContainerProto class
 * ==================================================================== */

} // end of namespace Saga2
