#include "KIllEmAllGameMode.h"
#include "MyPlayerController.h"

void AKIllEmAllGameMode::PawnKilled(APawn* PawnKilled) 
{
    Super::PawnKilled(PawnKilled);

    //gets player controller
    AMyPlayerController* PlayerController = Cast<AMyPlayerController>(PawnKilled->GetController());

    if (PlayerController != nullptr){
        //sets game ended and player was killed
        PlayerController->GameHasEnded(nullptr, false);
        UE_LOG(LogTemp, Warning, TEXT("Player Killed"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Enemy Killed"));
    }
}
