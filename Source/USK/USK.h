// Created by Henry Jooste

#pragma once

#include "Modules/ModuleManager.h"

class FUSKModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
