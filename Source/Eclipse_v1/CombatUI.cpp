// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatUI.h"
#include "Ennemy.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"


void UCombatUI::NativeConstruct() {
	
	Super::NativeConstruct();

}

void UCombatUI::UpdateEnemyUI(AActor* EnemyActor) {

	AEnnemy* Enemy = Cast<AEnnemy>(EnemyActor); //Attribue le .h & .cpp à une "entité" 

		if (Enemy) {//Vérifie si c'est valide | Si il y a quelque chose dedans
			FString Name = Enemy->EnemyName; //Récupération des Variables dans Ennemy et assimilation 
			float HP = Enemy->HealthPoint;
			int LVL = Enemy->Enemylvl;


			//Changement Direct de l'UI

			if (EnemyNameText) {
				EnemyNameText->SetText(FText::FromString(Name));
			}
			if (Enemy_HP) {
				float HPRatio = HP / 100.0f; //Mit sur 100%
				Enemy_HP->SetPercent(HPRatio);
			}
			if (Enemy_lvl) {
				Enemy_lvl->SetText(FText::AsNumber(LVL));
			}
		}
}

