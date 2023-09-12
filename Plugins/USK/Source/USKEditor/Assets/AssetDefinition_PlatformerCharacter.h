#pragma once

#include "CoreMinimal.h"
#include "AssetDefinitionDefault.h"
#include "USK/Character/PlatformerCharacter.h"
#include "AssetDefinition_PlatformerCharacter.generated.h"

UCLASS()
class USKEDITOR_API UAssetDefinition_PlatformerCharacter : public UAssetDefinitionDefault
{
	GENERATED_BODY()
	
public:
	virtual FText GetAssetDisplayName() const override { return FText::FromString("Platformer Character"); }
	virtual FLinearColor GetAssetColor() const override { return FLinearColor(FColor(63, 126, 255)); }
	virtual TSoftClassPtr<> GetAssetClass() const override { return APlatformerCharacter::StaticClass(); }
	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories()
	{
		static const auto Categories = { EAssetCategoryPaths::Basic };
		return Categories;
	}
};
