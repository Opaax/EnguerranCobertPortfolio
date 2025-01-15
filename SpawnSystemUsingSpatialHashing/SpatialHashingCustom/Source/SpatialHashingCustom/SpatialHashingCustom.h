// Copyright 2025 Enguerran COBERT. all right reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FSpatialHashingCustomModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
