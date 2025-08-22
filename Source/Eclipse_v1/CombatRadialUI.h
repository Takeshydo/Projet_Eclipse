// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArtSlot.h"
#include "ArtListStruct.h"
#include "CombatRadialUI.generated.h"



UCLASS()
class ECLIPSE_V1_API UCombatRadialUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitializeFromDataTable(UDataTable* ArtTable);
	void SelectNextSlot(int32 Direction);
	void HandleKey(FKey Key);

protected:
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* ArtSlotBox;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UArtSlot> ArtSlotClass;

	UPROPERTY()
	TArray<UArtSlot*> ArtSlots;

	int SelectedIndex = 0;
};
