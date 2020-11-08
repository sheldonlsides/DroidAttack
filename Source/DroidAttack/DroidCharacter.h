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
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	//allows function to be called from Blueprints
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void Fire();
	
	UPROPERTY(EditAnywhere)
	float RotationPitchRate = 150.0f; 

	UPROPERTY(EditAnywhere)
	float RotationTurnRate = 150.0f; 

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGun> GunClass;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float Speed = 1.0f;

	UPROPERTY()
	AGun* Gun;
};
