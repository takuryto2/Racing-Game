// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CarPawn.generated.h"

UCLASS()
class RACINGGAME_API ACarPawn : public APawn
{
	GENERATED_BODY()

public:
	ACarPawn();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* MaxwellStaticMesh;
	
	//Movement
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float CurrentSpeed;

	
	UFUNCTION(BlueprintCallable)
	void Move(float returnValue, float deltaTime, bool isBoosting);
	UPROPERTY(EditAnywhere, Category = Speed)
	float Acceleration;
	
	UPROPERTY(EditAnywhere, Category = Speed)
	float MaxSpeed;
	UPROPERTY(EditAnywhere)
	float MaxBoostSpeed;

	
	//strafe/turn	
	UFUNCTION(BlueprintCallable)
	void Turn(float value, float deltaTime);
	UPROPERTY(EditAnywhere, Category = SpeedValues)
	float TurnSpeed;
	
	
	UFUNCTION(BlueprintCallable)
	void Strafe(float value, float deltaTime);
	UPROPERTY(EditAnywhere, Category = SpeedValues)
	FTransform StrafeSpeed;
	
	
	void Hover();

	//hover linetrace parameters
	UPROPERTY(EditAnywhere, Category = Hover)
	FVector HoverDistance;
	FHitResult HoverHitResult;
	FCollisionQueryParams Params;
	
	UPROPERTY(EditAnywhere, Category = Hover)
	float HoverStrength;
		

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
