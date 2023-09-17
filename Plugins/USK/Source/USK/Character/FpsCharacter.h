// Created by Henry Jooste

#pragma once

#include "USKCharacter.h"
#include "FpsCharacter.generated.h"

/**
 * @brief Base character that can be used for first person shooter (FPS) games
 */
UCLASS()
class USK_API AFpsCharacter : public AUSKCharacter
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the AFpsCharacter actor
	 */
	AFpsCharacter();	
};
