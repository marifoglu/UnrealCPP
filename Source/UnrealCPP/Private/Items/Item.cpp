#include "Items/Item.h"
#include "UnrealCPP/DebugMacros.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	// UWorld* World = GetWorld();
	// FVector Location = GetActorLocation();
	// FVector Forward = GetActorForwardVector();
	//
	//
	//
	// DRAW_SPHERE(Location);
	// // DRAW_LINE(Location, Location + Forward * 100.f);
	// // DRAW_POINT(Location + Forward * 100.f);
	// DRAW_VECTOR(Location, Location + Forward * 100.f);


}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Movement rate in units of cm/s
	float MovementRate = 50.f;
	float RotationRate = 45.f;

	// MovementRate * DeltaTime (cm/s) * (s/frame) = (cm/frame)
	AddActorWorldOffset(FVector(MovementRate * DeltaTime, 0.f, 0.f));
	AddActorWorldRotation(FRotator(0.f, RotationRate * DeltaTime, 0.f));
	
	DRAW_SPHERE_SingleFrame(GetActorLocation());
	DRAW_VECTOR_SingleFrame(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f);


}

