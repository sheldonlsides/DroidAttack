#include "Gun.h"
#include "DroidCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkinnedMeshComponent.h"
// Sets default values
ADroidCharacter::ADroidCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADroidCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	//gets creates a reference to the gunclass and spawns it into the world
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);

	//hides the bone by socket name
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	//attaches gun to a socket by name
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_socket"));

	//ensures that the sun is assigned an owner
	Gun->SetOwner(this);
}

// Called every frame
void ADroidCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADroidCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// NOTES: BindAxis and BindAction are case sensitive

	//creates a forward and backward movement binding
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ADroidCharacter::MoveForward);
	
	//creates a look up and down binding
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ADroidCharacter::MoveRight);

	//creates a right and left movement binding
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);

	//Gamepad lookup rate
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ADroidCharacter::LookUpRate);

	/*
		creates a look left and right binding
		for simplicity a call for the yaw info is made directly to the APAwn class
		which is part of the base class that ACharacter inherits from
	*/
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);

	//Gamepad look right rate
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &ADroidCharacter::LookRightRate);

	//creates a jump action
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	//creates a fire action
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ADroidCharacter::Fire);
}

float ADroidCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	//gets value of damage taken
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//sets the max and min health allowed
	DamageToApply = FMath::Min(Health, DamageToApply);

	//updates health variable
	Health -= DamageToApply;

	if (IsDead()) {
		UE_LOG(LogTemp, Warning, TEXT("Dead"));
		// Destroy();
		
		// GetWorld()->GetTimerManager().SetTimer(Destroy(), Destroy(), 2, false)
		//  GetWorld()->GetTimerManager().SetTimer(PlayerEnabledHandle, PlayerEnabledDelegate, 3, false);
	}

	UE_LOG(LogTemp, Warning, TEXT("%f"), Health);

	return DamageToApply;
}

bool ADroidCharacter::IsDead() const
{
	return Health <= 0;
}

void ADroidCharacter::Fire() 
{
	//calls the pull trigger method on the reference to the gun setup in the begin play method
	Gun->PullTrigger();
}

void ADroidCharacter::MoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ADroidCharacter::MoveRight(float AxisValue) 
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ADroidCharacter::LookUpRate(float AxisValue) 
{
	//calculating movement speed
	AddControllerPitchInput(AxisValue * RotationPitchRate * GetWorld()->GetDeltaSeconds());
}

void ADroidCharacter::LookRightRate(float AxisValue) 
{
	//calculating turn speed
	AddControllerYawInput(AxisValue * RotationTurnRate * GetWorld()->GetDeltaSeconds());
}


