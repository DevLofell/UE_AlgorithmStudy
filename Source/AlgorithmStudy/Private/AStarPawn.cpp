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
	
	// ���콺 Ŀ�� ���̰� ����
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

// Called every frame
void AAStarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (path.Num() > 0)
	{
		currTime += DeltaTime;
		if (currTime > 0.5f)
		{
			currTime = 0;

			SetActorLocation(path[0]);
			path.RemoveAt(0);

			if (path.Num() == 0)
			{
				// �ʱ�ȭ
				for(int32 i = 0; i < openArray.Num(); i++)
					openArray[i]->SetInit();
				for(int32 i = 0; i < closeArray.Num(); i++)
					closeArray[i]->SetInit();

				openArray.Empty();
				closeArray.Empty();
			}
		}
	}
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
		startCube = Cast<ACubeBlock>(hit.GetActor());

		openArray.Add(startCube);
	}

	// Goal Cube �� �˾ƿ���

	FVector mouseDir;
	// ���콺 Ŭ����ġ�� 3D ������ ��ǥ�� �ٲ���
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
	// ������ �Ǵ� Cube ����
	currCube = openArray[0];

	openArray.RemoveAt(0);

	// ������
	AddOpen(FVector::RightVector);
	// �� (��)
	AddOpen(FVector::ForwardVector);
	// ����
	AddOpen(FVector::LeftVector);
	// �Ʒ� (��)
	AddOpen(FVector::BackwardVector);

	// ������ �Ǵ� Cube �� openArray ���� ����, closeArray �� ����
	
	closeArray.Add(currCube);
	// closeArray outline �� ����������
	currCube->SetColor(FLinearColor::Red);

	// ���������� �� ã�ư��ٸ�?
	if (openArray[0] == goalCube || openArray.Num() == 0)
	{
		// ���� ã�� ���� (��������� OutLine ����)

		// �θ� CubeBlock ���� ������ �ݺ�

		ACubeBlock* tempCube = goalCube;

		while (tempCube->parentCube != nullptr)
		{
			// �����ϴ� �� �߰�
			path.Insert(tempCube->GetActorLocation(), 0);

			tempCube->SetColor(FLinearColor::Yellow);
			tempCube = tempCube->parentCube;
		}
	}
	else
	{
		FindPath();
	}
}

void AAStarPawn::AddOpen(FVector dir)
{
	// dir �������� Cube �� �ִ� ���� (LineTrace)
	FHitResult hit;
	FVector start, end;
	FCollisionQueryParams params;
	params.AddIgnoredActor(currCube);
	params.AddIgnoredActor(this);

	start = currCube->GetActorLocation();
	end = start + dir * 100;

	bool result = GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, params);
	if (result == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : %s"), *dir.ToString(), *hit.GetActor()->GetActorLabel());

		
		ACubeBlock* cube = Cast<ACubeBlock>(hit.GetActor());
		// openArray, closeArray �ش� Cube �� ������ 
		if (openArray.Contains(cube) == false && closeArray.Contains(cube) == false)
		{
			// �ش� Cube �� Cost ������
			cube->SetCost(currCube, goalCube);

			// openArray ���� ���� (������ Cost ū Cube �տ�)
			int32 i = 0;
			for (i = 0; i < openArray.Num(); i++)
			{				
				if (openArray[i]->tCostValue >= cube->tCostValue)
				{
					break;
				}
			}
			openArray.Insert(cube, i);
		}
	}	
	
}

