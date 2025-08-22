// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtSlot.h"
#include "Components/Image.h"
#include "Components/Border.h"

void UArtSlot::SetupSlot(const FArtData& Data) {
	if (IconImage && !Data.Icon.IsNull())
	{
		UTexture2D* LoadedTexture = Data.Icon.LoadSynchronous();
		
		if (LoadedTexture)
		{
			IconImage->SetBrushFromTexture(LoadedTexture);
		}
	}
}

void UArtSlot::SetSelected(bool IsSelected) {
	if (SelectionBorder) {
		SelectionBorder->SetBrushColor(IsSelected ? FLinearColor::Blue : FLinearColor::Transparent);
	}
}