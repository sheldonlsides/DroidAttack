// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DroidCharacter.generated.h"


//needs to be forward declared because it's being used as a type for one of the properties
class AGun;

UCLASS()
class DROIDATTACK_API ADroidCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADroidCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void Fire();
	
	UPROPERTY(EditAnywhere)
	float RotationRate = 150.0f; 

	UPROPERTY(EditAnywhere)
	float RotationRateRight = 150.0f; 

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;
};
