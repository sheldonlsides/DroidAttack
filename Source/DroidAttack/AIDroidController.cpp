#include "AIDroidController.h"
#include "Kismet/GameplayStatics.h"

void AAIDroidController::BeginPlay() 
{
    Super::BeginPlay();

    //gets a reference to the player pawn in the world which is at index 0
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    //sets initial focus on the player pawn
    SetFocus(PlayerPawn);

    /*
        allows AI to move to player within 2 units
        functionality inherited from AAIController
    */
    MoveToActor(PlayerPawn, DistanceFromPlayer);
}

void AAIDroidController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    MoveToActor(PlayerPawn, DistanceFromPlayer);
}
