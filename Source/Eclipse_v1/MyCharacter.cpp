#include "MyCharacter.h"
#include "Ennemy.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "GameFramework/SpringArmComponent.h"
#include "EngineUtils.h"

// Sets default values | Constructeur ou Fondation plutôt 
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	
	//Camera Movement | Action set | Spring Arm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));//Creation de l'actachement de la camera au joueur 
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bDoCollisionTest = true;
	//Camera Object
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	//Orientation CAM 
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	

	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ClampCameraPitch();
	
	if (IsLocked && LockedTarget)
	{
		// Rotation du personnage vers la cible (sans pitch ni roll)
		FVector ToTarget = LockedTarget->GetActorLocation() - GetActorLocation();
		FRotator LookAtRot = FRotationMatrix::MakeFromX(ToTarget).Rotator();
		LookAtRot.Pitch = 0.0f;
		LookAtRot.Roll = 0.0f;

		SetActorRotation(FMath::RInterpTo(GetActorRotation(), LookAtRot, DeltaTime, 5.0f));

		// Rotation du SpringArm vers la cible (avec un clamp sur pitch)
		FVector ToTargetFromCameraBoom = LockedTarget->GetActorLocation() - CameraBoom->GetComponentLocation();
		FRotator DesiredBoomRot = ToTargetFromCameraBoom.Rotation();
		DesiredBoomRot.Pitch = FMath::ClampAngle(DesiredBoomRot.Pitch, -60.0f, 60.0f);
		DesiredBoomRot.Roll = 0.0f;

		FRotator SmoothedBoomRot = FMath::RInterpTo(CameraBoom->GetComponentRotation(), DesiredBoomRot, DeltaTime, 5.0f);
		CameraBoom->SetWorldRotation(SmoothedBoomRot);

		// Optionnel, si tu souhaites synchroniser aussi la rotation contrôleur
		Controller->SetControlRotation(LookAtRot);
	}
	else
	{
		// En mode libre, faire en sorte que le SpringArm suive la rotation contrôleur (si besoin)
		FRotator ControlRot = Controller->GetControlRotation();
		CameraBoom->SetWorldRotation(ControlRot);
	}

}

// Ici, c'est pour les Input OK !!
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	//Input Movement x Jump x Camera
	PlayerInputComponent->BindAxis("MoveX", this, &AMyCharacter::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &AMyCharacter::MoveY);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);// Quand Action définir l'action voulu (Presser, relacher, double click)
	PlayerInputComponent->BindAxis("MoveCameraX", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MoveCameraY", this, &APawn::AddControllerPitchInput);


	//Input Running
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter::Run);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacter::StopRun);


	//Input Lock
	PlayerInputComponent->BindAction("FocusE", IE_Pressed, this, &AMyCharacter::ToggleFocus);

}


//Movement Plan Horizontal / Ground
void AMyCharacter::MoveX(float Value) {
	if ((Controller != nullptr) && (Value != 0.0f)) 
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}
void AMyCharacter::MoveY(float Value) {
	if ((Controller != nullptr) && (Value != 0.0f)) 
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

//Camera Movement
void AMyCharacter::ClampCameraPitch() {

	FRotator ControlRotation = Controller->GetControlRotation();
	float ClampedPitch = FMath::ClampAngle(ControlRotation.Pitch, -60.0f, 60.0f);
	Controller->SetControlRotation(FRotator(ClampedPitch, ControlRotation.Yaw, 0.0f));
}


//Sprint Ici
void AMyCharacter::Run() {
	IsRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}
void AMyCharacter::StopRun() {
	IsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}


//Focus Lock, Comme Xenoblade
void AMyCharacter::ToggleFocus() {

	if (IsLocked) {
		LockedTarget = nullptr;
		IsLocked = false;

		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		Camera->bUsePawnControlRotation = false;
	}
	else {
		FindTargetToLock();

		if (LockedTarget) {
			// Active la rotation contrôleur sur personnage et caméra
			IsLocked = true;
			bUseControllerRotationYaw = true;
			GetCharacterMovement()->bOrientRotationToMovement = false;
			Camera->bUsePawnControlRotation = true;
		}
	}
}
void AMyCharacter::FindTargetToLock() {
	
	FVector Start = GetActorLocation();
	float LockRange = 1000.0f;
	float BestDistance = LockRange;

	AEnnemy* BestTarget = nullptr;

	for (TActorIterator<AEnnemy> It(GetWorld()); It; ++It) {
		AEnnemy* Candidate = *It;

		if (Candidate == Cast<AEnnemy>(this)) continue; // Sécurité

		float Dist = FVector::Dist(Candidate->GetActorLocation(), Start);
		if (Dist < BestDistance) {
			BestDistance = Dist;
			BestTarget = Candidate;
		}
	}

	LockedTarget = BestTarget;
}


