// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ArtListStruct.generated.h"

USTRUCT(BlueprintType)
struct FArtData : public FTableRowBase 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ArtID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//Nom de l'art
	FText ArtName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//Image / design du logo
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//dégâts a l'ennemie ou à soit (Heal)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//Délai de réutilisation
	float CoolDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//Feu, eau, foudre, vent, terre, obscur, lumière
	FName Element;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//Tranchant, Percent, Contendant, Soutien
	FName Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//Disponibilité / acquis
	bool bUnlocked;

};
