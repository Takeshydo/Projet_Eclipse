// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatRadialUI.h"
#include "ArtSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

void UCombatRadialUI::InitializeFromDataTable(UDataTable* ArtTable) {
	
	if (!ArtTable || !ArtSlotClass || !ArtSlotBox) return;

	TArray<FArtData*> AllRows;
	ArtTable->GetAllRows(TEXT("Initialize Art Slot"), AllRows);
	
	for (FArtData* Art : AllRows) {
		if (!Art || !Art->bUnlocked) continue;
		
		UArtSlot* NewSlot = CreateWidget<UArtSlot>(GetWorld(), ArtSlotClass);
		
		if (NewSlot) {
			NewSlot->SetupSlot(*Art);
			ArtSlotBox->AddChildToHorizontalBox(NewSlot);
			NewSlot->SetPadding(FMargin(25.0f, 0.f, 25.0f, 0.f));

			ArtSlots.Add(NewSlot);
		}

	}

	if (ArtSlots.Num() > 0) {
		SelectedIndex = 0;
		ArtSlots[0]->SetSelected(true);
	}
}

void UCombatRadialUI::SelectNextSlot(int32 Direction) {
	UE_LOG(LogTemp, Warning, TEXT("SelectNextSlot called with Direction: %d"), Direction);
	if (ArtSlots.Num() == 0) {
		UE_LOG(LogTemp, Error, TEXT("No ArtSlots available when trying to select"));
		return;
	}
	ArtSlots[SelectedIndex]->SetSelected(false);
	SelectedIndex = (SelectedIndex + Direction + ArtSlots.Num()) % ArtSlots.Num();
	ArtSlots[SelectedIndex]->SetSelected(true);

}

void UCombatRadialUI::HandleKey(FKey Key) {
	
	if (Key == EKeys::Gamepad_DPad_Right) {
		SelectNextSlot(+1);
	
	}
	else if (Key == EKeys::Gamepad_DPad_Left) {
		SelectNextSlot(-1);
		
	}
}
