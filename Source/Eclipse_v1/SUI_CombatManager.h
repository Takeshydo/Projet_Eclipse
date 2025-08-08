// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class ECLIPSE_V1_API SUI_CombatManager : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUI_CombatManager)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
