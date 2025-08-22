// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Declaration Lourd | Importe tous ce que contient le fichier |Pratique lors d'utilisation de Fonction provenant du Fichier
#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

//Foward Declaration | déclaration plus légère que les include |Pratique quand on veut juste un Réf 
class UCombatUI;
class UCombatRadialUI;
UCLASS()
class ECLIPSE_V1_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Fonction des actions
	void MoveX(float Value);
	void MoveY(float Value);
	void ClampCameraPitch();
	void Run();
	void StopRun();
	void ToggleFocus();
	void FindTargetToLock();
	void OnRadialNavigation(float Value);


	// Vérif d'état de paramètre 
	bool IsRunning;
	bool IsLocked;

	//Variable de sécu RAdial
	float TimeSinceLastRadialInput = 0.0f;
	float RadialInputCD = 0.2f;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY()
	AActor* LockedTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UCombatUI> CombatUIClass;

	UPROPERTY()
	UCombatUI* CombatUIInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UCombatRadialUI>RadialMenuClass;
	
	UPROPERTY()
	UCombatRadialUI* RadialMenuInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RadialMenu")
	UDataTable* ArtTable;
};
