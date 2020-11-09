#include "BTTask_Shoot.h"
#include "AIController.h"
#include "DroidCharacter.h"

void UBTTask_Shoot::UBTTask_AIShoot() 
{
    NodeName = "AI Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    
    if (OwnerComp.GetOwner() == nullptr) {
        return EBTNodeResult::Failed;
    }

    //gets the AI Pawn and cast it to an DroidCharacter
    ADroidCharacter* character = Cast<ADroidCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if (character == nullptr) return EBTNodeResult::Failed;

    character->Fire();

    return EBTNodeResult::Succeeded;
}