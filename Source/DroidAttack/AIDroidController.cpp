#include "AIDroidController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AAIDroidController::BeginPlay() 
{
    Super::BeginPlay();
    
     if (AIBehavior != nullptr) {
         //start running AI behavior tree
        RunBehaviorTree(AIBehavior);

        //sets blackboard player start location
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
     }
}

void AAIDroidController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    //gets a reference to the player pawn in the world which is at index 0
    //PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    // //checks that player is in line of sight before following
    if (LineOfSightTo(PlayerPawn)) {
        //runs Behavior Tree if available
        if (AIBehavior != nullptr) {
            RunBehaviorTree(AIBehavior);

            //sets the blackboard location of the player
            GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
            GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());

        }
    } else {
        //clears player location if AI loses line of sight
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    }
    
}
