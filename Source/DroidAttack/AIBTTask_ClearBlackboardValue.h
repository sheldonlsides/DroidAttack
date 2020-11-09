#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AIBTTask_ClearBlackboardValue.generated.h"

/**
 * 
 */
UCLASS()
class DROIDATTACK_API UAIBTTask_ClearBlackboardValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	void UBTTask_ClearBlackboardValue();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
