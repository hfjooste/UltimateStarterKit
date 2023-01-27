// Created by Henry Jooste

#pragma once

#include "GameUtils.generated.h"

UCLASS()
class UGameUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:	
	/**
	 * @brief Delay the execution of a function
	 * @tparam T The owner type
	 * @param Owner The owner object of type T
	 * @param InFunction The function that will be executed after the delay
	 * @param Delay The delay (in seconds)
	 */
	template<typename T> static void Delay(T* Owner, void(T::*InFunction)(), float Delay);
};

/**
 * @brief Delay the execution of a function
 * @tparam T The owner type
 * @param Owner The owner object of type T
 * @param InFunction The function that will be executed after the delay
 * @param Delay The delay (in seconds)
 */
template<typename T>
FORCEINLINE void UGameUtils::Delay(T* Owner, void(T::*InFunction)(), float Delay)
{	
	const AActor* Actor = dynamic_cast<AActor*>(Owner);
	if (Actor == nullptr)
	{
		return;
	}
	
	Delay = FMath::Max(Delay, 0.0001f);
		
	FTimerHandle UnusedHandle;
	Actor->GetWorldTimerManager().SetTimer(UnusedHandle, Owner, InFunction, Delay, false);
}