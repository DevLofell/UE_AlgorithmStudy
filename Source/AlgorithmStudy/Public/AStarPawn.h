// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AStarPawn.generated.h"

UCLASS()
class ALGORITHMSTUDY_API AAStarPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAStarPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void InputLMouseDown();

	void FindPath();
	void AddOpen(FVector dir);

public:

	// ��ã�� ���� ��ġ
	UPROPERTY(VisibleAnywhere)
	class ACubeBlock* startCube;

	// ��ã�� ������ ��ġ
	UPROPERTY(VisibleAnywhere)
	class ACubeBlock* goalCube;

	// �ش� Cube �������� ��, ��, ��, �츦 �˻�
	UPROPERTY(VisibleAnywhere)
	class ACubeBlock* currCube;

	// �� ������ ����ִ� Cube ���� �������� ��, ��, ��, �츦 �˻�
	UPROPERTY(VisibleAnywhere)
	TArray<class ACubeBlock*> openArray;

	// �˻��� �� ���� Cube
	UPROPERTY(VisibleAnywhere)
	TArray<class ACubeBlock*> closeArray;
};
