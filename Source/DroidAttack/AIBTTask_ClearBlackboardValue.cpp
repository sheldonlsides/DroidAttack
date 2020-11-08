#include "AIBTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

void UAIBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue() 
{
    NodeName = "Clear Blackboard Value";
}

EBTNodeResult::Type UAIBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    //clears the value of the selected blackboard key
    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    return EBTNodeResult::Succeeded;
}
