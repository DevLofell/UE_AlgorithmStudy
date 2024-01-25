// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeBlock.h"
#include <Components/WidgetComponent.h>
#include <Components/Border.h>
#include <Components/TextBlock.h>

// Sets default values
ACubeBlock::ACubeBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACubeBlock::BeginPlay()
{
	Super::BeginPlay();
	
	// widget component ã�ƿ���
	UWidgetComponent* widget = GetComponentByClass<UWidgetComponent>();
	UUserWidget* costWidget = widget->GetUserWidgetObject();

	//costWidget �� ��ġ�Ǿ� �ִ� ������ ��������
	outLine = Cast<UBorder>(costWidget->GetWidgetFromName(TEXT("OutLine")));
	sCost = Cast<UTextBlock>(costWidget->GetWidgetFromName(TEXT("sCost")));
	gCost = Cast<UTextBlock>(costWidget->GetWidgetFromName(TEXT("gCost")));
	tCost = Cast<UTextBlock>(costWidget->GetWidgetFromName(TEXT("tCost")));
}

// Called every frame
void ACubeBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeBlock::SetCost(class ACubeBlock* s, class ACubeBlock* g)
{
	// ���� cubeBlock �� ��ġ
	FVector sPos = s->GetActorLocation();
	// ������ cubeBlock �� ��ġ
	FVector gPos = g->GetActorLocation();
	// ���� ���� ��ġ
	FVector myPos = GetActorLocation();

	// sCost ������
	sCostValue = FMath::Abs(sPos.X - myPos.X) + FMath::Abs(sPos.Y - myPos.Y);
	sCostValue += s->sCostValue;

	// gCost ������
	float gCostValue = FMath::Abs(gPos.X - myPos.X) + FMath::Abs(gPos.Y - myPos.Y);

	// tCost ������
	tCostValue = sCostValue + gCostValue;

	// �� Cost �� UI �� ǥ������
	sCost->SetText(FText::AsNumber(sCostValue));
	gCost->SetText(FText::AsNumber(gCostValue));
	tCost->SetText(FText::AsNumber(tCostValue));

	// OutLine Color �Ķ������� ����
	SetColor(FLinearColor::Blue);
}

void ACubeBlock::SetColor(FLinearColor color)
{
	outLine->SetBrushColor(color);
}

