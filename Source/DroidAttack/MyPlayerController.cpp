#include "MyPlayerController.h"
#include "TimerManager.h"

void AMyPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    UE_LOG(LogTemp, Warning, TEXT("Game has ended"));

    /*
        Restarts the level based on a delay
        RestartLevel belongs to APlayerController
    */
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
