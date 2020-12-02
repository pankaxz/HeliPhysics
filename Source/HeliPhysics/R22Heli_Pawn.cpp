// Fill out your copyright notice in the Description page of Project Settings.


#include "R22Heli_Pawn.h"
#include "PawnPhysicsController.h"
#include "HeliEngine.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AR22Heli_Pawn::AR22Heli_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Physics box
	SM_RootBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_RootBody"));
	RootComponent = SM_RootBody;
	SM_RootBody->SetSimulatePhysics(true);
	SM_RootBody->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	SM_RootBody->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	SM_RootBody->SetCollisionResponseToAllChannels(ECR_Ignore);
	//SM_PhysicsBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	

	//Graphics group
	SC_Graphics = CreateDefaultSubobject<USceneComponent>(TEXT("SC_Graphics"));
	SC_Graphics->SetupAttachment(SM_RootBody);
	
	//Colliders
	Col_Fuselage = CreateDefaultSubobject<UCapsuleComponent>(TEXT("COL_Fuselage"));
	Col_Fuselage->SetupAttachment(SM_RootBody);
	Col_Fuselage->SetCapsuleRadius(16.0f);
	Col_Fuselage->SetCapsuleHalfHeight(26.0f);
	Col_Fuselage->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Col_Fuselage->SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	Col_Fuselage->SetCollisionResponseToAllChannels(ECR_Block);
	
	Col_Mast = CreateDefaultSubobject<UCapsuleComponent>(TEXT("COL_Mast"));
	Col_Mast->SetupAttachment(SM_RootBody);
	Col_Mast->SetCapsuleRadius(7.0f);
	Col_Mast->SetCapsuleHalfHeight(15.0f);
	Col_Mast->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Col_Mast->SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	Col_Mast->SetCollisionResponseToAllChannels(ECR_Block);
	
	Col_Tail = CreateDefaultSubobject<UCapsuleComponent>(TEXT("COL_Tail"));
	Col_Tail->SetupAttachment(SM_RootBody);
	Col_Tail->SetCapsuleRadius(4.0f);
	Col_Tail->SetCapsuleHalfHeight(21.0f);
	Col_Tail->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Col_Tail->SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	Col_Tail->SetCollisionResponseToAllChannels(ECR_Block);

	Col_LSkid = CreateDefaultSubobject<UCapsuleComponent>(TEXT("COL_LSkid"));
	Col_LSkid->SetupAttachment(SM_RootBody);
	Col_LSkid->SetCapsuleRadius(1.0f);
	Col_LSkid->SetCapsuleHalfHeight(20.0f);
	Col_LSkid->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Col_LSkid->SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	Col_LSkid->SetCollisionResponseToAllChannels(ECR_Block);

	Col_RSkid = CreateDefaultSubobject<UCapsuleComponent>(TEXT("COL_RSkid"));
	Col_RSkid->SetupAttachment(SM_RootBody);
	Col_RSkid->SetCapsuleRadius(1.0f);
	Col_RSkid->SetCapsuleHalfHeight(20.0f);
	Col_RSkid->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Col_RSkid->SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	Col_RSkid->SetCollisionResponseToAllChannels(ECR_Block);

	//Setup Center of mass for PawnPhysicsController
	SC_HeliCenterOfMass = CreateDefaultSubobject<USceneComponent>(TEXT("Center of Mass"));
	SC_HeliCenterOfMass->SetupAttachment(SM_RootBody);
	
	// Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	PawnPhysicsControllerVar = CreateDefaultSubobject<UPawnPhysicsController>(TEXT("Pawn Contoroller"));
	AddOwnedComponent(PawnPhysicsControllerVar);

	HeliEngine = CreateDefaultSubobject<UHeliEngine>(TEXT("Heli Engine"));
	AddOwnedComponent(HeliEngine);
}

void AR22Heli_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AR22Heli_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AR22Heli_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

		PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &AR22Heli_Pawn::SetHorizontalInput);
		PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &AR22Heli_Pawn::SetVerticalInput);
		PlayerInputComponent->BindAxis(TEXT("Throttle"), this, &AR22Heli_Pawn::SetThrottleInput);
		PlayerInputComponent->BindAxis(TEXT("Collective"), this, &AR22Heli_Pawn::SetCollectiveInput);
		PlayerInputComponent->BindAxis(TEXT("Pedal"), this, &AR22Heli_Pawn::SetPedalInput);
	
}
//Setter Functions

void AR22Heli_Pawn::SetHorizontalInput(float AxisValue)
{
	HorizontalInput = AxisValue;
	CyclicInput.X = HorizontalInput;
}

void AR22Heli_Pawn::SetVerticalInput(float AxisValue)
{
	VerticalInput = AxisValue;
	CyclicInput.Y = VerticalInput;
}

void AR22Heli_Pawn::SetThrottleInput(float AxisValue)
{
	ThrottleInput = AxisValue;
}

void AR22Heli_Pawn::SetPedalInput(float AxisValue)
{
	PedalInput = AxisValue;
}

void AR22Heli_Pawn::SetCollectiveInput(float AxisValue)
{
	CollectiveInput = AxisValue;
}

void AR22Heli_Pawn::SetCyclicInput()
{
	CyclicInput.Y = VerticalInput;
	CyclicInput.X = HorizontalInput;
}


//Getter Functions

float AR22Heli_Pawn::GetHorizontalInput()
{
	return HorizontalInput;
}

float AR22Heli_Pawn::GetVerticalInput()
{
	return  VerticalInput;
}

float AR22Heli_Pawn::GetThrottleInput()
{
	return ThrottleInput;
}

float AR22Heli_Pawn::GetPedalInput()
{
	return PedalInput;
}

float AR22Heli_Pawn::GetCollectiveInput()
{
	return CollectiveInput;
}

FVector2D AR22Heli_Pawn::GetCyclicInput()
{
	return CyclicInput;
}

UStaticMeshComponent* AR22Heli_Pawn::GetHeliRootBody()
{
	return SM_RootBody;
}

FVector AR22Heli_Pawn::GetHeliCenterOfMass()
{
	FVector HeliCenterOfMassLocation = SC_HeliCenterOfMass->GetComponentLocation();
	return HeliCenterOfMassLocation;
}
