// Created by Henry Jooste

#pragma once

#include "Engine/DecalActor.h"
#include "ShadowDecal.generated.h"

/**
 * @brief Decal used to draw a shadow beneath a character when the character is in the air
 */
UCLASS()
class USK_API AShadowDecal : public ADecalActor
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the AShadowDecal actor
	 */
	AShadowDecal();

	/**
	 * @brief Initialize the shadow decal
	 * @param OwnerCharacter The character owning this shadow decal
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Shadow Decal")
	void Initialize(ACharacter* OwnerCharacter);

protected:
	/**
	 * @brief Event called every frame, if ticking is enabled
	 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
	 */
	virtual void Tick(float DeltaSeconds) override;

private:
	/**
	 * @brief Reference to the character owning this shadow decal
	 */
	UPROPERTY()
	ACharacter* Character;
};
