// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarPawn.h"
#include "CubeBlock.h"

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
	
	// 마우스 커서 보이게 하자
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
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
	// 길찾기 시작.....

	FHitResult hit;
	FVector start, goal;
	FCollisionQueryParams parmas;
	bool result;

	// Start Cube 를 알아오자 (나의 위치에서 아래방향으로 LineTrace 를 실행)
	start = GetActorLocation() + FVector::UpVector;
	goal = start + FVector::DownVector * 5;
	parmas.AddIgnoredActor(this);

	result = GetWorld()->LineTraceSingleByChannel(hit, start, goal, ECC_Visibility, parmas);
	if (result == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("start : %s"), *hit.GetActor()->GetActorLabel());
		startCube = Cast<ACubeBlock>(hit.GetActor());

		openArray.Add(startCube);
	}

	// Goal Cube 를 알아오자

	FVector mouseDir;
	// 마우스 클릭위치를 3D 공간의 좌표로 바꾸자
	GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(start, mouseDir);

	goal = start + mouseDir * 100000;

	result =GetWorld()->LineTraceSingleByChannel(hit, start, goal, ECC_Visibility, parmas);
	if (result == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("goal : %s"), *hit.GetActor()->GetActorLabel());
		goalCube = Cast<ACubeBlock>(hit.GetActor());
	}

	FindPath();
}

void AAStarPawn::FindPath()
{
	// 기준이 되는 Cube 설정
	currCube = openArray[0];

	// 오른쪽
	AddOpen(FVector::RightVector);
	// 위 (앞)
	AddOpen(FVector::ForwardVector);
	// 왼쪽
	AddOpen(FVector::LeftVector);
	// 아래 (뒤)
	AddOpen(FVector::BackwardVector);
}

void AAStarPawn::AddOpen(FVector dir)
{
	// dir 방향으로 Cube 가 있는 검출 (LineTrace)
	FHitResult hit;
	FVector start, end;
	FCollisionQueryParams params;
	params.AddIgnoredActor(currCube);

	start = currCube->GetActorLocation();
	end = start + dir * 100;

	bool result = GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, params);
	if (result == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : %s"), *dir.ToString(), *hit.GetActor()->GetActorLabel());
	}
	
	// 해당 Cube 의 Cost 구하자
	// openArray 값을 넣자 (나보다 Cost 큰 Cube 앞에)
}

