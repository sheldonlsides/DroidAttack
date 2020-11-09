#pragma once

#include "CoreMinimal.h"
#include "DroidAttackGameModeBase.h"
#include "KIllEmAllGameMode.generated.h"

UCLASS()
class DROIDATTACK_API AKIllEmAllGameMode : public ADroidAttackGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled) override;

};
