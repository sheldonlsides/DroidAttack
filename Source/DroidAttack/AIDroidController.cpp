#include "AIDroidController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AAIDroidController::BeginPlay() 
{
    Super::BeginPlay();
    // Old code for manually handling AI focus

    //sets initial focus on the player pawn
    // SetFocus(PlayerPawn);

    /*
        allows AI to move to player within 2 units
        functionality inherited from AAIController
    */
    // MoveToActor(PlayerPawn, DistanceFromPlayer);
}

void AAIDroidController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    //gets a reference to the player pawn in the world which is at index 0
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    // //checks that player is in line of sight before following
    if (LineOfSightTo(PlayerPawn)) {
        //runs Behavior Tree if available
        if (AIBehavior != nullptr) {
            RunBehaviorTree(AIBehavior);

            //sets the blackboard location of the player
            GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());

            /*
                sets the blackboard location of the AI
                GetPawn() gets info about the current pawn
            */
            GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
        }
    } else {
        //clears player location if AI loses line of sight
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    }
    
}
