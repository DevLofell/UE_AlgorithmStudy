// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleWidget.h"
#include <Components/Border.h>
#include <Components/CanvasPanelSlot.h>

void UPuzzleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ī�� Border ��������
	for (int32 i = 0; i < 9; i++)
	{
		FString widgetName = FString::Printf(TEXT("Card_%d"), i);
		UWidget* widget = GetWidgetFromName(*widgetName);
		UBorder* card = Cast<UBorder>(widget);
		cardWidgets.Add(card);

		// ���࿡ i �� 0 �̶��(ù��° ī����)
		if (i == 0)
		{
			// ī���� ��ġ���� ����
			UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(card->Slot);
			offsetX = slot->GetPosition().X;
			offsetY = slot->GetPosition().Y;
		}
	}	

	// ī�� �ʱ�ȭ
	InitCard();
}

void UPuzzleWidget::InitCard()
{
	// ī���� ���� �ʱ�ȭ
	cardValues.Empty();

	// �������� ī���� ������ �ٲ��� (�Ķ���, �����)
	for (int32 i = 0; i < cardWidgets.Num(); i++)
	{
		// ������ ���� ���� (0, 1)
		int32 rand = FMath::RandRange(0, 1);

		// ī���� ���� ����
		cardValues.Add(rand);

		// 0 ���̸� �Ķ���, 1 ���̸� �����
		if (rand == 0)
		{
			cardWidgets[i]->SetBrushColor(FLinearColor::Blue);
		}
		else
		{
			cardWidgets[i]->SetBrushColor(FLinearColor::Yellow);
		}
	}
}

void UPuzzleWidget::SelectCard(FVector2D mousePos)
{
	// (x / ī��ũ��) + (y / ī��ũ��) * ī�尡�ΰ��� = ���õ� ī�� Index
	int32 hIndex = (int32)((mousePos.X - offsetX) / cardSize);
	int32 vIndex = (int32)((mousePos.Y - offsetY) / cardSize);
	int32 selectCardIdx = hIndex + vIndex * hCount;

	UE_LOG(LogTemp, Warning, TEXT("select card = %d"), selectCardIdx);

	// ������ ī��� ������
	cardWidgets[selectCardIdx]->SetBrushColor(FLinearColor::Red);

	// ��ó ī�带 ã�� (��, ��, ��, ��)
	FindNearCard(selectCardIdx);
}

void UPuzzleWidget::FindNearCard(int32 idx)
{
	int32 n;

	// ��
	// if (idx > hCount - 1)
	if (idx / hCount > 0)
	{
		n = idx - hCount;
		UE_LOG(LogTemp, Warning, TEXT("up = %d"), n);
		cardWidgets[n]->SetBrushColor(FLinearColor::Red);
	}
	// ��
	if (idx / hCount < vCount - 1)
	{
		n = idx + hCount;
		UE_LOG(LogTemp, Warning, TEXT("down = %d"), n);
		cardWidgets[n]->SetBrushColor(FLinearColor::Red);
	}
	// ��
	if (idx % hCount > 0)
	{
		n = idx - 1;
		UE_LOG(LogTemp, Warning, TEXT("left = %d"), n);
		cardWidgets[n]->SetBrushColor(FLinearColor::Red);
	}
	// ��
	if (idx % hCount < hCount - 1)
	{
		n = idx + 1;
		UE_LOG(LogTemp, Warning, TEXT("right = %d"), n);
		cardWidgets[n]->SetBrushColor(FLinearColor::Red);
	}
}
