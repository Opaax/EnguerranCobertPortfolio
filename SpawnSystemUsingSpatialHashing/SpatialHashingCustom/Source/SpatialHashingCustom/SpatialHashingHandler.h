// Copyright 2025 Enguerran COBERT. all right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Spatial/PointHashGrid3.h"

struct FSpawnGridHandleBase
{
public:
	FVector3d Location;
	int32 GridIndex;

	FSpawnGridHandleBase(): Location(), GridIndex(0) {}
};

/**
 * 
 */
template<class HandleType = FSpawnGridHandleBase>
class SpatialHashingHandler
{
	/*
	 * Give compile error if HandleType do not derive from base handle
	 * assure that there is at least a location to work with as the TPointHashGrid3d is supposed to work
	*/
	static_assert(TIsDerivedFrom<HandleType, FSpawnGridHandleBase>::Value, "HandleType must be a type derived from FSpawnGridHandleBase"); 
	/*-------------------------- MEMBERS ----------------------------*/
private:
	UE::Geometry::TPointHashGrid3d<int32>* PointHash3;
	TArray<HandleType*> AllHandle;
	bool bIsClear = true;

	/*-------------------------- FUNCTION ----------------------------*/

public:
	/**
	 * Create the hash grid with the given cell size
	 * @param CellSize The size of each grid cell.
	 * @param InvalidValue The value to mark as invalid in the grid.
	 */
	void CreateGrid(int32 CellSize = 100, int32 InvalidValue = -1)
	{
		PointHash3 =  new UE::Geometry::TPointHashGrid3d<int32>(CellSize, InvalidValue);
		bIsClear = false;
	}

	/**
	 * Reserve memory space for the hash grid to optimize insertion of a given number of elements.
	 * @param Num The number of elements to reserve space for.
	 */
	void Reserve(int32 Num) const
	{
		PointHash3->Reserve(Num);
	}

	/**
	 * Get the pointer to the hash grid.
	 * @return Pointer to the TPointHashGrid3d<int32> instance.
	 */
	UE::Geometry::TPointHashGrid3d<int32>* GetGrid() const { return PointHash3;}
	/**
	 * Get a copy of all the handles stored in the Spatial Hashing Handler.
	 * @return An array of pointers to the HandleType instances.
	 */
	TArray<HandleType*> GetHandlesCopy() const { return AllHandle;}
	/**
	 * Get a const reference to the array of pointers to stored HandleType instances.
	 * @return Const reference to the array of pointers to HandleType instances.
	 */
	const TArray<HandleType*>& GetHandlesRef() const { return AllHandle;}

	/**
	 * Delete the hash grid and mark as clear if conditions are met.
	 * Deletes the TPointHashGrid3d instance if it exists and clears the state if all handles are empty.
	 */
	void DeleteGrid()
	{
		if(PointHash3 != nullptr)
		{
			delete PointHash3;
		}

		if(AllHandle.IsEmpty())
		{
			bIsClear = true;
		}
	}

	/**
	 * Reset the handles in the grid and set the clear state if the hash grid is not initialized.
	 */
	void ClearGrid()
	{
		AllHandle.Reset();
		
		if(PointHash3 == nullptr)
		{
			bIsClear = true;
		}
	}

	/**
	 * Add a handle to the Spatial Hashing Handler.
	 * @param Handle Pointer to the HandleType instance to be added.
	 * Updates the GridIndex of the handle by adding it to the list of handles and inserts its location into the point hash grid if the handle is not null.
	 */
	void AddHandle(HandleType* Handle)
	{
		if(Handle)
		{
			Handle->GridIndex = AllHandle.Add(Handle);
			PointHash3->InsertPoint(Handle->GridIndex, Handle->Location);
		}
	}

	/**
	 * Flushes the grid data by clearing all handles and deleting the grid.
	 * Clears all handles in the grid, deletes the grid instance, and sets the clear state to true.
	 */
	void FlushGrid()
	{
		ClearGrid();
		DeleteGrid();
		bIsClear = true;
	}


	SpatialHashingHandler(): PointHash3(nullptr) {}
	~SpatialHashingHandler()
	{
		ensureMsgf(bIsClear, TEXT("You should call 'FlushGrid' before deleting SpatialHashingHandler"));
	}
};
