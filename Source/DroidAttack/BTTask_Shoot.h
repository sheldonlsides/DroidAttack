#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class DROIDATTACK_API UBTTask_Shoot : public UBTTaskNode
{
	GENERATED_BODY()

public:
	void UBTTask_AIShoot();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
