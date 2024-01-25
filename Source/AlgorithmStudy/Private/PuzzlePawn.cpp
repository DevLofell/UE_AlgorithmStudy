

#include "PuzzlePawn.h"
#include "PuzzleWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

APuzzlePawn::APuzzlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UPuzzleWidget> tempWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/BP_PuzzleWidget.BP_PuzzleWidget_C'"));
	if (tempWidget.Succeeded())
	{
		puzzleWidgetClass = tempWidget.Class;
	}
}

void APuzzlePawn::BeginPlay()
{
	Super::BeginPlay();
	
	// Puzzle Widget �����
	puzzleWidget = CreateWidget<UPuzzleWidget>(GetWorld(), puzzleWidgetClass);
	puzzleWidget->AddToViewport();

	// ���콺 ���̰� ����
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

// Called every frame
void APuzzlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APuzzlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("RightMouse"), EInputEvent::IE_Pressed, this, &APuzzlePawn::InputRMouse);

	PlayerInputComponent->BindAction(TEXT("RightMouse"), EInputEvent::IE_Released, this, &APuzzlePawn::InputRMouseUp);
}

void APuzzlePawn::InputRMouse()
{
	// ���콺 Ŭ�� ��ǥ�� ������
	FVector2D mousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	//UE_LOG(LogTemp, Warning, TEXT("mosuePos = %s"), *mousePos.ToString());
	
	puzzleWidget->SelectCard(mousePos);
}

void APuzzlePawn::InputRMouseUp()
{
	puzzleWidget->InitCard();
}



