// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "Cube.h"
#include "Information.h"
#include "core.h"


// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MyMesh->SetupAttachment(Root);
	HitBox = CreateDefaultSubobject <UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(Root);
	HitBox->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
	MySkel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MySkel"));
	MySkel->SetupAttachment(Root);

	OnClicked.AddDynamic(this, &ACube::OnPlayerClick);
	OnBeginCursorOver.AddDynamic(this, &ACube::OnPlayerOver);
	OnEndCursorOver.AddDynamic(this, &ACube::OnPlayerOff);
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ACube::AddInteractable);
	HitBox->OnComponentEndOverlap.AddDynamic(this, &ACube::RemoveInteractable);
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();
	initialLocation = GetActorLocation();
	initialRotate = GetActorRotation();
	currentLocation = initialLocation;
	destination = initialLocation;
	if (MySkel) {
		MySkel->PlayAnimation(IdleAnim, true);
	}

	FString InFilename = FPaths::GameContentDir() + ProgramFile;
	TArray<FString> OutStrings;
	FString ProgramFromFile;
	if (FFileHelper::LoadANSITextFileToStrings(*InFilename, NULL, OutStrings)) {
		ProgramFromFile.Append(OutStrings[0]);
		for (int i = 1; i < OutStrings.Num(); i++) {
			ProgramFromFile.Append(TEXT("\n") + OutStrings[i]);
		}
		MyProgram = FText::FromString(ProgramFromFile);
	}

}

// Called every frame
void ACube::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (currentLocation.Equals(destination)) {
		if (walking) {
			MySkel->PlayAnimation(IdleAnim, true);
			walking = false;
		}
	}
	else {
		currentLocation = FMath::VInterpConstantTo(currentLocation, destination, DeltaTime, velocity);
		SetActorLocation(currentLocation);
	}
	if (desiredAngle != 0) {
		float diff = DeltaTime * TurnRate * FMath::Sign(desiredAngle);
		if (FMath::Abs(diff) >= FMath::Abs(desiredAngle)) {
			SetActorRotation(GetActorQuat() * FQuat(FVector(0, 0, 1), desiredAngle));
			desiredAngle = 0;
		}
		else {
			SetActorRotation(GetActorQuat() * FQuat(FVector(0, 0, 1), diff));
			desiredAngle -= diff;
		}
	}
}

void ACube::OnPlayerClick(AActor* TouchedActor, FKey ButtonPressed)
{
	AInformation* hud = Cast<AInformation>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (hud == nullptr)
	{
		;
	}
	else {
		hud->SetProgram(MyProgram, this);
		hud->tutorialWindow->ExternalNext();
	}
}

void ACube::OnPlayerOver(AActor* TouchedActor)
{
	AInformation* hud = Cast<AInformation>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (hud == nullptr)
	{
		;
	}
	else {
		hud->SetString(Name);
	}
}

void ACube::OnPlayerOff(AActor* TouchedActor)
{
	AInformation* hud = Cast<AInformation>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (hud == nullptr)
	{
		;
	}
	else {
		hud->SetString("");
	}
}

void ACube::SetProgram(FText program)
{
	MyProgram = program;
}

void ACube::AddInteractable(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) {
	;
}

void ACube::RemoveInteractable(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	;
}

void ACube::MoveCharacter(float x, float y, float z, float speed) {
	destination = FVector(x, y, z);
	velocity = speed;
	if (WalkAnim) {
		MySkel->PlayAnimation(WalkAnim, true);
		walking = true;
	}
}

void ACube::Walk(float distance, float speed) {
	velocity = speed;
	destination = currentLocation+distance*GetActorRightVector();
	if (WalkAnim) {
		MySkel->PlayAnimation(WalkAnim, true);
		walking = true;
	}
}

int ACube::TurnTo(FVector destin) {
	FVector difference = destin - currentLocation;
	difference.Normalize();
	FVector forward = GetActorRightVector();
	float product = FVector::DotProduct(difference, forward);
	float diff = 0;
	if (product == 0) {
		diff = PI / 2 * FMath::Sign(FVector::CrossProduct(forward, difference).Z);
	}
	else {
		//Strangely Acos only returns 0 to PI/2...
		diff = FMath::Acos(product) * FMath::Sign(FVector::CrossProduct(forward, difference).Z);
	}
	desiredAngle += diff;
	return FMath::Abs(diff * 1000 /TurnRate);
}

int ACube::WalkTo(FVector destin, float speed) {
	destination = destin;
	velocity = speed;
	if (WalkAnim) {
		MySkel->PlayAnimation(WalkAnim, true);
		walking = true;
	}
	return FVector::Dist(currentLocation, destination) * 1000 / speed;
}

void ACube::Turn(float angle) {
	desiredAngle += angle;
}

bool ACube::Near(FVector location)
{
	return FVector::Dist(currentLocation, location) < 50;
}

void ACube::reset() {
	currentLocation = initialLocation;
	destination = initialLocation;
	desiredAngle = 0;
	SetActorLocation(initialLocation);
	SetActorRotation(initialRotate);
	if (MySkel) {
		MySkel->PlayAnimation(IdleAnim, true);
		walking = false;
	}
}

void ACube::nextLevel() {
	FString currentLevel = UGameplayStatics::GetCurrentLevelName(this);
	if (currentLevel.Equals("Level1")) {
		UGameplayStatics::OpenLevel(GetWorld(), "Level2");
	}
	else {
		UGameplayStatics::OpenLevel(GetWorld(), "Level3");
	}
}