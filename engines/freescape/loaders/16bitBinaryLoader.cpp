//
//  16bitBinaryLoader.cpp
//  Phantasma
//
//  Created by Thomas Harte on 17/12/2013.
//  Copyright (c) 2013 Thomas Harte. All rights reserved.
//


//#include "freescape/language/parser.h"

#include "common/debug.h"
#include "common/array.h"
#include "common/file.h"

#include "freescape/area.h"
#include "freescape/objects/object.h"
#include "freescape/objects/geometricobject.h"
#include "freescape/loaders/16bitBinaryLoader.h"
#include "freescape/language/16bitDetokeniser.h"
#include "freescape/language/instruction.h"

class StreamLoader
{
	private:

		Common::Array<uint8>::size_type bytePointer;
		Common::Array<uint8> binary;
		uint8 readMaskByte1;
		uint8 readMaskByte2;

	public:
		StreamLoader(Common::Array <uint8> &_binary)
		{
			binary = _binary;
			bytePointer = 0;
			readMaskByte1 = 0;
			readMaskByte2 = 0;
		}

		uint8 get8()
		{
			if(!eof())
			{
				uint8 sourceByte = binary[bytePointer];
				
				if(bytePointer&1)
					sourceByte ^= readMaskByte2;
				else
					sourceByte ^= readMaskByte1;

				bytePointer++;
				return sourceByte;
			} else
				error("eof");

			return 0;
		}

		uint16 get16()
		{
			uint16 result = (uint16)(get8() << 8);
			result |= get8();
			return result;
		}

		uint32 get32()
		{
			uint32 result = (uint32)(get16() << 16);
			result |= get16();
			return result;
		}

		bool eof()
		{
			return bytePointer >= binary.size();
		}
		
		void alignPointer()
		{
			if(bytePointer&1) bytePointer++;
		}
		
		void skipBytes(Common::Array<uint8>::size_type numberOfBytes)
		{
			bytePointer += numberOfBytes;
		}

		Common::Array<uint8> *nextBytes(Common::Array<uint8>::size_type numberOfBytes)
		{
			Common::Array<uint8> *returnBuffer(new Common::Array<uint8>);
			debug("give me the next %d bytes", numberOfBytes);

			while(numberOfBytes--)
				returnBuffer->push_back(get8());

			return returnBuffer;
		}

		Common::Array<uint8>::size_type getFileOffset()
		{
			return bytePointer;
		}

		void setFileOffset(Common::Array<uint8>::size_type newOffset)
		{
			bytePointer = newOffset;
		}
		
		void setReadMask(uint8 byte1, uint8 byte2)
		{
			readMaskByte1 = byte1;
			readMaskByte2 = byte2;
		}
};


static Object *loadObject(StreamLoader &stream)
{
	// get object flags and type
	uint8 objectFlags = stream.get8();
	Object::Type objectType = (Object::Type)stream.get8();

	/*
		Notes to self:
		
			0 = no flags
			128 = Movable, Animated
			134 = Movable, Animated, Default invis, invis
			6 = Default invis, Invis
			32 = collided
	*/

	// get unknown value
	uint16 skippedShort = stream.get16();
	debug("skippedShort: %d", skippedShort);

	// grab location, size
	Vector3d position, size;
	position.x		= stream.get16();
	position.y		= stream.get16();
	position.z		= stream.get16();
	size.x			= stream.get16();
	size.y			= stream.get16();
	size.z			= stream.get16();

	// object ID
	uint16 objectID = stream.get16();

	// size of object on disk; we've accounted for 20 bytes
	// already so we can subtract that to get the remaining
	// length beyond here
	uint32 byteSizeOfObject = (uint32)(stream.get16() << 1) - 20;

	debug("Object %d ; type %d ; flags %d ; size %d" , objectID , (int)objectType, (int)objectFlags, byteSizeOfObject);

	switch(objectType)
	{
		default:
		{
			// read the appropriate number of colours
			int numberOfColours = GeometricObject::numberOfColoursForObjectOfType(objectType);
			Common::Array<uint8> *colours = new Common::Array<uint8>;
			for(uint8 colour = 0; colour < numberOfColours; colour++)
			{
				colours->push_back(stream.get8());
				byteSizeOfObject--;
			}

			// read extra vertices if required...
			int numberOfOrdinates = GeometricObject::numberOfOrdinatesForType(objectType);
			debug("number of ordinates %d", numberOfOrdinates);
			Common::Array<uint16> *ordinates = nullptr;

			if(numberOfOrdinates)
			{
				ordinates = new Common::Array<uint16>;

				for(int ordinate = 0; ordinate < numberOfOrdinates; ordinate++)
				{
					ordinates->push_back(stream.get16());
					byteSizeOfObject -= 2;
				}
			}

			// grab the object condition, if there is one
			FCLInstructionVector instructions;
			if(byteSizeOfObject)
			{
				Common::Array<uint8> *conditionData = stream.nextBytes(byteSizeOfObject);

				Common::String *conditionSource = detokenise16bitCondition(*conditionData);
				instructions = nullptr; //getInstructions(conditionSource.get());
			}
			byteSizeOfObject = 0;

			// create an object
			return
				new GeometricObject(
					objectType,
					objectID,
					position,
					size,
					colours,
					ordinates,
					instructions);
		}
		break;

		case Object::Entrance:
		case Object::Sensor:
		case Object::Group:
		break;
	}

	// skip whatever we didn't understand
	//cout << "bytes we don't understand:" << endl;
	//int i = 0;
	//int j = 0;
	//for (i = 0; i < byteSizeOfObject/2; i++)
	//	cout << i << stream.get16() << endl;
	stream.skipBytes(byteSizeOfObject);

	return nullptr;
	
}

Area *loadArea(StreamLoader &stream)
{
	// the lowest bit of this value seems to indicate
	// horizon on or off; this is as much as I currently know
	uint16 skippedValue		= stream.get16();
	uint16 numberOfObjects	= stream.get16();
	uint16 areaNumber			= stream.get16();

	debug("Area %d", areaNumber);
	debug("Skipped value %d", skippedValue);
	debug("Objects: %d", numberOfObjects);

	// I've yet to decipher this fully
	uint16 horizonColour	= stream.get16();
	debug("Horizon colour %x", (int)horizonColour);

	// this is just a complete guess
	for(int paletteEntry = 0; paletteEntry < 22; paletteEntry++)
	{
		uint8 paletteColour		= stream.get8();
		debug("Palette colour (?) %x", (int)paletteColour);
	}

	// we'll need to collate all objects and entrances; it's likely a
	// plain C array would do but maps are safer and the total application
	// cost is going to be negligible regardless
	ObjectMap *objectsByID = new ObjectMap;
	ObjectMap *entrancesByID = new ObjectMap;

	// get the objects or whatever; entrances use a unique numbering
	// system and have the high bit of their IDs set in the original file
	for(uint16 object = 0; object < numberOfObjects; object++)
	{
		Object *newObject = loadObject(stream);

		if(newObject)
		{
			if(newObject->getType() == Object::Entrance)
			{
				(*entrancesByID)[newObject->getObjectID() & 0x7fff] = newObject;
			}
			else
			{
				(*objectsByID)[newObject->getObjectID()] = newObject;
			}
		}
	}

	return (new Area(areaNumber, objectsByID, entrancesByID));
}

Game *load16bitBinary(Common::String filename)
{
	Common::File *file = new Common::File();

    if (!file->open(filename)) {
        delete file;
    	return NULL;
    }

	const uint32 fileSize = file->size();
	byte *buf = (byte *)malloc(fileSize);
	file->read(buf, fileSize);

	Common::Array <uint8> binary;

	uint32 i = 0;
	while (i < fileSize) {
		binary.push_back(buf[i]);
		i++;
	}

	StreamLoader streamLoader(binary);

	Common::Array<uint8>::size_type baseOffset = 0;

	// check whether this looks like an Amiga game; if so it'll start with AM
	// XOR'd with the repeating byte pattern 0x71, 0xc1 or with the pattern
	// 0x88 0x2c if it's on the ST (though the signature will still be AM)
	uint16 platformID = streamLoader.get16();
	debug("%d", platformID);

	if(
//		(platformID != 0x4120) && (platformID != 0x5043)
		(platformID == 12428) || (platformID == 51553)
	)
	{
		// TODO: record original platform type, so we can decode the palette
		// and possibly the border properly
		//cout << "AMIGA" << endl;

		streamLoader.setReadMask((platformID >> 8) ^ 'A', (platformID & 0xff) ^ 'M');
	}
	else
	{
		debug("DOS");
		// find DOS end of file and consume it
		while(!streamLoader.eof()) {
			uint8 b = streamLoader.get8();
			if (b == 0x1a)
			   break;
		}
		streamLoader.get8();

		// advance to the next two-byte boundary if necessary
		streamLoader.alignPointer();

		// skip bytes with meaning unknown
		streamLoader.get16();

		// this brings us to the beginning of the embedded
		// .KIT file, so we'll grab the base offset for
		// finding areas later
		baseOffset = streamLoader.getFileOffset();

		// check that the next two bytes are "PC", then
		// skip the number that comes after
		if(streamLoader.get8() != 'C' || streamLoader.get8() != 'P') return nullptr;
	}

	
	// skip an unknown meaning
	streamLoader.get16();

	// start grabbing some of the basics...

	uint16 numberOfAreas = streamLoader.get16();
	streamLoader.get16(); // meaning unknown

	debug("Number of areas: %d", numberOfAreas);

	uint16 windowCentreX	= streamLoader.get16();
	uint16 windowCentreY	= streamLoader.get16();
	uint16 windowWidth	= streamLoader.get16();
	uint16 windowHeight	= streamLoader.get16();

	
	debug("Window centre: (%d, %d)", windowCentreX, windowCentreY);
	debug("Window size: (%d, %d)", windowWidth,  windowHeight);

	uint16 scaleX	= streamLoader.get16();
	uint16 scaleY	= streamLoader.get16();
	uint16 scaleZ	= streamLoader.get16();

	debug("Scale %d, %d, %d", scaleX, scaleY, scaleZ);
	uint16 timerReload	= streamLoader.get16();

	debug("Timer: every %d 50Hz frames", timerReload);

	uint16 maximumActivationDistance	= streamLoader.get16();
	uint16 maximumFallDistance		= streamLoader.get16();
	uint16 maximumClimbDistance		= streamLoader.get16();

	debug("Maximum activation distance: %d", maximumActivationDistance);
	debug("Maximum fall distance: %d",  maximumFallDistance);
	debug("Maximum climb distance: %d", maximumClimbDistance);

	uint16 startArea					= streamLoader.get16();
	uint16 startEntrance				= streamLoader.get16();

	debug("Start at entrance %d in area %d", startEntrance, startArea);

	uint16 playerHeight				= streamLoader.get16();
	uint16 playerStep				= streamLoader.get16();
	uint16 playerAngle				= streamLoader.get16();

	debug("Height %d, step %d, angle %d)", playerHeight, playerStep, playerAngle);

	uint16 startVehicle				= streamLoader.get16();
	uint16 executeGlobalCondition	= streamLoader.get16();

	debug("Start vehicle %d, execute global condition %d", startVehicle, executeGlobalCondition);

	// I haven't figured out what the next 106
	// bytes mean, so we'll skip them — global objects
	// maybe? Likely not 106 bytes in every file.
	//
	// ADDED: having rediscovered my source for the 8bit
	// file format, could this be shading information by
	// analogy with that?
	/*cout << "global unknown:";
	int i; 
	int j;
	for (i = 0; i < 106/2; i++)
		cout << streamLoader.get16() << endl;*/

	streamLoader.skipBytes(106);

	// at this point I should properly load the border/key/mouse
	// bindings, but I'm not worried about it for now.
	//
	// Format is:
	//		(left x, top y, right x, bottom y) - all 16 bit
	//		keyboard key as an ASCII character (or zero for none)
	//		mouse button masl; 00 = both, 01 = left, 02 = right
	//
	// So, 10 bytes per binding. Bindings are listed in the order:
	//
	//	move forwards, move backwards, move right, move left, rise,
	//	fall, turn left, turn right, look up, look down, tilt left,
	//	tilt right, face forward, u-turn, change vehicle type,
	//	select this vehicle, quit game, fire, activate object,
	//	centre cursor on/off, save game position, load game position
	//
	// So 35 total. Which means this area takes up 350 bytes.
	//cout << "more global unknown:";
	//for (i = 0; i < 350/2; i++)
	//	cout << streamLoader.get16() << endl;

	streamLoader.skipBytes(350);

	// there are then file pointers for every area — these are
	// the number of shorts from the 'PC' tag, so multiply by
	// two for bytes. Each is four bytes
	uint32 *fileOffsetForArea = new uint32[numberOfAreas];
	for(uint16 area = 0; area < numberOfAreas; area++)
		fileOffsetForArea[area] = (uint32)streamLoader.get32() << 1;

	// now come the global conditions
	uint16 numberOfGlobalConditions = streamLoader.get16();
	for(uint16 globalCondition = 0; globalCondition < numberOfGlobalConditions; globalCondition++)
	{
		// 12 bytes for the name of the condition;
		// we don't care
		streamLoader.skipBytes(12);

		// get the length and the data itself, converting from
		// shorts to bytes
		uint32 lengthOfCondition = (uint32)streamLoader.get16() << 1;

		// get the condition
		Common::Array<uint8> *conditionData = streamLoader.nextBytes(lengthOfCondition);

		debug("Global condition %d", globalCondition+1);
		debug("%s", detokenise16bitCondition(*conditionData)->c_str());
	}

	// grab the areas
	AreaMap *areaMap = new AreaMap;
	for(uint16 area = 0; area < numberOfAreas; area++)
	{
		debug("Area offset %d", fileOffsetForArea[area]);

		streamLoader.setFileOffset(fileOffsetForArea[area] + baseOffset);
		Area *newArea = loadArea(streamLoader);
		
		if(newArea)
		{
			(*areaMap)[newArea->getAreaID()] = newArea;
		}

	}
	streamLoader.setFileOffset(fileOffsetForArea[numberOfAreas-1] + baseOffset);

	delete[] fileOffsetForArea;
	return new Game(areaMap);
}
