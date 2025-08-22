// ArtSlot.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArtListStruct.h"
#include "ArtSlot.generated.h"

UCLASS()
class ECLIPSE_V1_API UArtSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetupSlot(const FArtData& Data);
	void SetSelected(bool IsSelected);

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* IconImage;

	UPROPERTY(meta = (BindWidget))
	class UBorder* SelectionBorder;
};