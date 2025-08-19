// CombatUI.h

#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatUI.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * Widget de combat, utilisé pour afficher les informations de l'ennemi
 */
UCLASS()
class ECLIPSE_V1_API UCombatUI : public UUserWidget
{
	GENERATED_BODY()

public:
	// Fonction pour mettre à jour les informations de l'ennemi
	void UpdateEnemyUI(AActor* EnemyActor);

protected:
	// Fonction d'initialisation (appelée lors de la création du widget)
	virtual void NativeConstruct() override;

	// Références aux éléments du widget UMG
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* EnemyNameText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* Enemy_lvl;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* Enemy_HP;
};
