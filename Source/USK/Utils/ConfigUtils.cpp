// Created by Henry Jooste

#include "ConfigUtils.h"

#include "Misc/ConfigCacheIni.h"
#include "USK/Logger/Log.h"

/**
 * @brief Extract a config value from a given config file
 * @param Filename The name of the config file
 * @param Section The section in the config file
 * @param Key The key in the config file
 * @param DefaultValue The default value to return if the config file can't be read
 * @return The value extracted from the config file
 */
FString UConfigUtils::GetConfigValue(const FString Filename, const FString Section,
                                     const FString Key, FString DefaultValue)
{
	if (GConfig == nullptr)
	{
		USK_LOG_ERROR("GConfig is nullptr. Returning default value");
		return DefaultValue;
	}

	FString Value;
	GConfig->GetString(*Section, *Key, Value, Filename);
	return Value;
}

/**
 * @brief Extract a config value from the default game config file
 * @param Section The section in the config file
 * @param Key The key in the config file
 * @param DefaultValue The default value to return if the config file can't be read
 * @return The value extracted from the config file
 */
FString UConfigUtils::GetGameConfigValue(const FString Section, const FString Key, const FString DefaultValue)
{
	return GetConfigValue(GGameIni, Section, Key, DefaultValue);
}