#pragma once

UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EPathFindingNodeFlags : uint8
{
	None = 0,
	Walkable = 1 << 1,
	Unwalkable = 1 << 2,
};
ENUM_CLASS_FLAGS(EPathFindingNodeFlags)