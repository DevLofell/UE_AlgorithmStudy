// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarPawn.h"

// Sets default values
AAStarPawn::AAStarPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAStarPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAStarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAStarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction(TEXT("LeftMouse"), IE_Pressed, this, &AAStarPawn::InputLMouseDown);
}

void AAStarPawn::InputLMouseDown()
{
	// ��ã�� ����.....

	FHitResult hit;
	FVector start, goal;
	FCollisionQueryParams parmas;
	bool result;

	// Start Cube �� �˾ƿ��� (���� ��ġ���� �Ʒ��������� LineTrace �� ����)
	start = GetActorLocation() + FVector::UpVector;
	goal = start + FVector::DownVector * 5;
	parmas.AddIgnoredActor(this);

	result = GetWorld()->LineTraceSingleByChannel(hit, start, goal, ECC_Visibility, parmas);
	if (result == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("start : %s"), *hit.GetActor()->GetActorLabel());
	}
}

