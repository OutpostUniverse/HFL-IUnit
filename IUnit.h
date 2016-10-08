//----------------------------------------------------------------------------------------
// IUnit.h
//----------------------------------------------------------------------------------------
// Defines a new Unit structure that adds extra capabilities to the Units
//
// Eddy productions 2004/2005
// Modifications by ZigZagJoe for use with HFL
//----------------------------------------------------------------------------------------

#ifndef IUnit_H
#define IUnit_H
#include <HFL.h>
#ifdef IUNIT_CPP

#pragma pack(push,1) // From UnitEx.cpp
// OP2Unit
// Can't use bit fields on the 'char' types since the compiler will still pad to word-size
struct OP2Unit
{
	void *vtbl;
	int isLive;
	void *prevUnit;
	void *nextUnit;
	int id;
	int pixelX;
	int pixelY;
	char unknown0;
	char ownerCreator; // lower 4 bits: owner ID, upper 4 bits: creator ID
	short damage;
	char boolNewAction;
	char curCmd;
	char curAction;
	char lastAction;
	short weaponCargo; // trucks: lowest 4 bits, cargo type; next 4 bits, cargo amount
	short unknown1;
	int unknown2;
	short instanceNum;
	short unknown3;
	int unknown4;
	void *destWaypoints; // missileDestX
	int missileDestY;
	int timer;
	int unknown5;
	unsigned int flags;
	char bayWeaponCargo[6];
	char unknown6;
	char unknownCargo;
	int unknown7;
	short timerStickyfoam;
	short timerEMP;
	short timerESG;
	short unknown8;
	int unknown9;
	char unknown10;
	char bayItem[6];
	char unknown11;
	int unknown12;
	short unknown13;
	int objectOnPad;
	short unknown14;
	int unknown15;
};

struct cmdBuild // Type: (0x06) "ctMoBuild"
{
	char numUnits;
	short unitId;
	short numWayPoints;
	int pts; 
	// ... variable number of units
	// ... variable number of waypoints
	// Build area
	short topLeftTileX;
	short topLeftTileY;
	short bottomRightTileX;
	short bottomRightTileY;
	short unknown;				// **TODO** figure this out - Set to -1
								// probably a ScStub callback ID
};
#pragma pack(pop)
#endif


/* compatability defines */

#define command_type CommandType

class IUnit : public UnitEx
{
// functions (some functions can only be done by a certain unit type):
public:
	void Doze(MAP_RECT region);		// use with RoboDozer only
	void Dock();							// to be used when a unit in on a docking pad
	void DockGarage();					// to be used when a unit in on a docking pad of a garage
	void Produce(enum map_id itemToProduce,enum map_id weaponType);
	void TransferCargo(short bay);	// to be used when a unit in on a docking pad
	void LoadCargo();						// to be used when a unit in on a docking pad
	void UnloadCargo();					// to be used when a unit in on a docking pad
	void DumpCargo();
	void Research(short techID,short numScientists);	// use only with labs
	void TrainScientists(short numTrained);				// use only with university
	void Salvage(MAP_RECT region,Unit gorf);
	void Poof();
	void Repair(Unit target);			// use with convec or repait vehicle
	void Reprogram(Unit target);		// use with spider only
	void Dismantle(Unit target);		// use with convec

	command_type GetBusy();				// returns what this unit is doing (0=not busy)
	void GetFactoryCargo(int bay, enum map_id &unitType, enum map_id &weaponType);
	void GetCargo(map_id &cargoType,map_id &weaponType);	// works for convecs
	int GetTruckCargo(Truck_Cargo &cargoType);				// returns amount of cargo
	
	//int GetDamage();						// 0=no damage
	/* already in HFL! */

	bool IsInRect(MAP_RECT rect);		// returns true if the unit is in the rect

	/////////////////////////////////////

	void Build(LOCATION location);	// use when there's a kit inside a convec, or when this is a miner/geocon
	/* ^^^ NOT IMPLEMENTED ^^^ */
	void DoDeploy(int tileX, int tileY, int x1, int y1, int x2, int y2); 
	/* this provides similar function ^ */
};

struct OP2Unit;
extern OP2Unit **unitArray;

#endif	// IUnit_H
