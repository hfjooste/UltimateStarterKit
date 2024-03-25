// Created by Henry Jooste

#include "ProjectUtils.h"
#include "ConfigUtils.h"

/**
 * @brief Get the project ID from the game config file
 * @return The project ID
 */
FString UProjectUtils::GetProjectId()
{
	return UConfigUtils::GetGameConfigValue("/Script/EngineSettings.GeneralProjectSettings", "ProjectID", "");
}

/**
 * @brief Get the project name from the game config file
 * @return The project name
 */
FString UProjectUtils::GetProjectName()
{
	return UConfigUtils::GetGameConfigValue("/Script/EngineSettings.GeneralProjectSettings", "ProjectName", "");
}

/**
 * @brief Get the project description from the game config file
 * @return The project description
 */
FString UProjectUtils::GetProjectDescription()
{
	return UConfigUtils::GetGameConfigValue("/Script/EngineSettings.GeneralProjectSettings", "Description", "");
}

/**
 * @brief Get the project version from the game config file
 * @return The project version
 */
FString UProjectUtils::GetProjectVersion() 
{
	return UConfigUtils::GetGameConfigValue("/Script/EngineSettings.GeneralProjectSettings", "ProjectVersion", "");
}

/**
 * @brief Get the project company name from the game config file
 * @return The project company name
 */
FString UProjectUtils::GetProjectCompanyName()
{
	return UConfigUtils::GetGameConfigValue("/Script/EngineSettings.GeneralProjectSettings", "CompanyName", "");
}

/**
 * @brief Get the project copyright notice from the game config file
 * @return The project copyright notice
 */
FString UProjectUtils::GetProjectCopyrightNotice()
{
	return UConfigUtils::GetGameConfigValue("/Script/EngineSettings.GeneralProjectSettings", "CopyrightNotice", "");
}

/**
 * @brief Get the project licensing terms from the game config file
 * @return The project licensing terms
 */
FString UProjectUtils::GetProjectLicensingTerms()
{
	return UConfigUtils::GetGameConfigValue("/Script/EngineSettings.GeneralProjectSettings", "LicensingTerms", "");
}

/**
 * @brief Get the project homepage from the game config file
 * @return The project homepage
 */
FString UProjectUtils::GetProjectHomepage()
{
	return UConfigUtils::GetGameConfigValue("/Script/EngineSettings.GeneralProjectSettings", "Homepage", "");
}
