// Fill out your copyright notice in the Description page of Project Settings.


#include "CarPawn.h"

// Sets default values
ACarPawn::ACarPawn():MaxwellStaticMesh(nullptr), CurrentSpeed(0), HoverDistance(0)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Params.AddIgnoredActor(this);
}

// Called when the game starts or when spawned
void ACarPawn::BeginPlay()
{
	Super::BeginPlay();
	MaxwellStaticMesh = this->FindComponentByClass<UStaticMeshComponent>();
}


// Called every frame
void ACarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentSpeed = FVector::DotProduct(GetVelocity(), GetActorForwardVector());
	Hover();
}

// Called to bind functionality to input
void ACarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ACarPawn::Move(float returnValue, float deltaTime, bool isBoosting)
{
	if(CurrentSpeed < MaxSpeed || CurrentSpeed < -MaxSpeed)
	{
		FVector speed = this->GetActorForwardVector() * Acceleration * 10 * returnValue;
		//MaxwellStaticMesh->AddForceAtLocation(speed * deltaTime, this->GetActorLocation());
		MaxwellStaticMesh->AddForce(speed * deltaTime, "Force", true);
	}
}

void ACarPawn::Turn(float value, float deltaTime)
{
	FRotator turnRotator = FRotator(FRotator(0, TurnSpeed * value * 10 * deltaTime, 0));
	MaxwellStaticMesh->SetWorldRotation(turnRotator + this->GetActorRotation());
}

void ACarPawn::Strafe(float value, float deltaTime)
{
	//FTransform strafeMath = StrafeSpeed * value * 10 * deltaTime;
	//MaxwellStaticMesh->AddLocalTransform(strafeMath);
}

void ACarPawn::Hover()
{	
	FVector hoverHeight = HoverDistance* -2 + this->GetActorLocation();
	if(GetWorld()->LineTraceSingleByChannel(HoverHitResult, this->GetActorLocation(), hoverHeight, ECC_WorldStatic, Params))
	{
		if(HoverHitResult.Distance < HoverDistance.Z)
		{
			MaxwellStaticMesh->AddForce(FVector(0,0,HoverStrength), "Force", true);
		}
		else
		{
			MaxwellStaticMesh->AddForce(FVector(0,0,HoverStrength-30), "Force", true);
		}
	}
}

