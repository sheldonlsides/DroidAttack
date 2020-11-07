#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	//mesh that gun will be attached to
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SkeletalMesh->SetupAttachment(Root);

}

void AGun::PullTrigger() 
{
	/*
		Spanws a muzzle flash particle system
		Attaches it to the mesh with a socket named MuzzleFlashSocket
	*/
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, SkeletalMesh, TEXT("MuzzleFlashSocket"));

	//Get owner of gun could be player of AI
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;

	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;

	//passes out the location and rotation info to variables
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	//code for calculating end trace location point
	FVector End = Location + Rotation.Vector() * MaxRange;

	//testing camera view
	// DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);

	//stores hit result info. includes info about actor that was hit
	FHitResult Hit;

	/*
		sets the Line Trace Hit info, End location and uses the 
		ECC_GameTraceChannel1 that was setup in the project settings 
		Engine collision settings
	*/
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1);

	if (bSuccess) {
		//get direction where shot came from
		FVector ShotDirection = -Rotation.Vector();

		//creates debug view helper for camera
		// DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletImpact, Hit.Location, ShotDirection.Rotation());

		//gets actor that was hit
		AActor* HitActor = Hit.GetActor();
		
		if (HitActor != nullptr) {
			//creates struct to store damage event info
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);

			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

