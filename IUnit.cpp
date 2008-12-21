#include <HFL.h>
#include "Outpost2DLL.h"

#define IUNIT_CPP

#include <IUnit.h>

void IUnit::Doze(MAP_RECT region)		// use with RoboDozer only
{
	DoDoze(region);
}

void IUnit::Dock()							// to be used when a unit in on a docking pad
{
	DoDock(Location());
}

void IUnit::DockGarage()					// to be used when a unit in on a docking pad of a garage
{
	DoDockAtGarage(Location());
}

void IUnit::Build(LOCATION location)	// use when there's a kit inside a convec, or when this is a miner/geocon
{
	// not implemented!

	// I have the code for this, however it needs some 
	// extra info which a location alone will not provide!
}

void IUnit::DoDeploy(int tileX, int tileY, int x1, int y1, int x2, int y2)
{
	
	if (!IsLive())
		return;

	CommandPacket packet;
	cmdBuild *data = (cmdBuild*)packet.dataBuff;

	packet.type = 0x06;
	packet.dataLength = sizeof(cmdBuild);

	data->numUnits = 1;
	data->unitId = unitID;

	data->numWayPoints = 1;

	data->pts = ((tileX*32 + 16) & 0x7FFF) | (((tileY*32 + 16) & 0x3FFF) << 15);

	data->topLeftTileX = x1;
	data->topLeftTileY = y1;
	data->bottomRightTileX = x2;
	data->bottomRightTileY = y2;
	data->unknown = -1;

	ExtPlayer[OwnerID()].ProcessCommandPacket(&packet);
}

void IUnit::Produce(enum map_id itemToProduce,enum map_id weaponType)
{
	DoProduce(itemToProduce,weaponType);
}

void IUnit::TransferCargo(short bay)	// to be used when a unit in on a docking pad
{
	DoTransferCargo(bay);
}

void IUnit::LoadCargo()						// to be used when a unit in on a docking pad
{
	DoLoadCargo();
}

void IUnit::UnloadCargo()					// to be used when a unit in on a docking pad
{
	DoUnloadCargo();
}

void IUnit::DumpCargo()
{
	DoDumpCargo();
}

void IUnit::Research(short techID,short numScientists)	// use only with labs
{
	DoResearch(techID,numScientists);
}

void IUnit::TrainScientists(short numTrained)				// use only with university
{
	DoTrainScientists(numTrained);
}

void IUnit::Salvage(MAP_RECT region,Unit gorf)
{
	DoSalvage(region,gorf);
}
void IUnit::Poof()
{
	DoPoof();
}
void IUnit::Repair(Unit target)			// use with convec or repait vehicle
{
	DoRepair(target);
}
void IUnit::Reprogram(Unit target)		// use with spider only
{
	DoReprogram(target);
}
void IUnit::Dismantle(Unit target)		// use with convec
{
	DoDismantle(target);
}

command_type IUnit::GetBusy()				// returns what this unit is doing (0=not busy)
{
	return GetLastCommand();
}

void IUnit::GetFactoryCargo(int bay, enum map_id &unitType, enum map_id &weaponType)
{
	unitType = UnitEx::GetFactoryCargo(bay);
	weaponType = GetFactoryCargoWeapon(bay);
}

void IUnit::GetCargo(map_id &cargoType,map_id &weaponType)	// works for convecs
{

	if (!isInited)
		return;

	if (!IsLive())
		return;

	cargoType = UnitEx::GetCargo();
	weaponType = (map_id)(*unitArray)[unitID].weaponCargo; // .... not sure how to get this?
}

int IUnit::GetTruckCargo(Truck_Cargo &cargoType)				// returns amount of cargo
{
	cargoType = (Truck_Cargo)Unit::GetCargo(); 

	// check with hooman - one of these is not correct
	// either it returns a truck cargo (and op2sdk is defined wrong),
	// or it returns a map_id and truck_cargo is wrong

	return GetCargoAmount();
}

//int IUnit::GetDamage()						// 0=no damage 
/* already in unitex */

bool IUnit::IsInRect(MAP_RECT rect)		// returns true if the unit is in the rect
{
	return rect.Check(Location());
}
