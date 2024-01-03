// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PuzzleWidget.generated.h"

/**
 * 
 */
UCLASS()
class ALGORITHMSTUDY_API UPuzzleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	void InitCard();
	void SelectCard(FVector2D mousePos);
	void FindNearCard(int32 idx);

public:
	UPROPERTY(EditAnywhere)
	TArray<class UBorder*> cardWidgets;

	UPROPERTY(EditAnywhere)
	TArray<int32> cardValues;	

	// ī��ũ��
	float cardSize = 120;
	// ī�尡�ΰ���
	int32 hCount = 3;
	// ī�尡�μ��ΰ���
	int32 vCount = 3;

	// ù��° ī���� ��ġ(������ ����)
	float offsetX;
	float offsetY;
};
