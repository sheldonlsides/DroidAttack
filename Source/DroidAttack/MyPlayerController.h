#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

UCLASS()
class DROIDATTACK_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false);

private:
	UPROPERTY(EditAnywhere)
	float RestartDelay = 2.0f;

	//function handling for the restart timer
	FTimerHandle RestartTimer;
};
