// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIDroidController.generated.h"


class APawn;

UCLASS()
class DROIDATTACK_API AAIDroidController : public AAIController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	APawn* PlayerPawn;

	UPROPERTY(EditAnywhere, Category = "AI Settings")
	float DistanceFromPlayer = 200;
};
