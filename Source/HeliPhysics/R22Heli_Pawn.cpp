// Fill out your copyright notice in the Description page of Project Settings.


#include "R22Heli_Pawn.h"


#include "DrawDebugHelpers.h"
#include "HeliCharacteristics.h"
#include "HeliController.h"
#include "PawnPhysicsController.h"
#include "HeliEngine.h"
#include "HeliRotorController.h"
#include "HeliMainRotor.h"
#include "HeliTailRotor.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AR22Heli_Pawn::AR22Heli_Pawn()
{

	PrimaryActorTick.bCanEverTick = true;

	//Physics box
	SM_RootBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_RootBody"));
	RootComponent = SM_RootBody;
	SM_RootBody->SetSimulatePhysics(true);
	SM_RootBody->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	SM_RootBody->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	SM_RootBody->SetCollisionResponseToAllChannels(ECR_Ignore);
	//SM_PhysicsBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	// //Setup Center of mass for PawnPhysicsController
	// Col_COM = CreateDefaultSubobject<UCapsuleComponent>(TEXT("COL_COM"));
	// RootComponent = Col_COM;
	// Col_COM->SetCapsuleRadius(1.0f);
	// Col_COM->SetCapsuleHalfHeight(1.0f);


	//Graphics group
	SC_Graphics = CreateDefaultSubobject<USceneComponent>(TEXT("SC_Graphics"));
	SC_Graphics->SetupAttachment(SM_RootBody);

	SC_Body = CreateDefaultSubobject<USceneComponent>(TEXT("SC_Body"));
	SC_Body->SetupAttachment(SC_Graphics);

	SC_MainMastRotor = CreateDefaultSubobject<USceneComponent>(TEXT("SC_MainMastRotor"));
	SC_MainMastRotor->SetupAttachment(SC_Graphics);
    SC_MainMastRotor->SetMobility(EComponentMobility::Movable);
	
	SC_TailMastRotor = CreateDefaultSubobject<USceneComponent>(TEXT("SC_TailMastRotor"));
	SC_TailMastRotor->SetupAttachment(SC_Graphics);

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
	HeliPhysicsHandler = CreateDefaultSubobject<UCapsuleComponent>(TEXT("COL_CenterOfMass"));
	HeliPhysicsHandler->SetupAttachment(SM_RootBody);
	HeliPhysicsHandler->SetCapsuleRadius(1.0f);
	HeliPhysicsHandler->SetCapsuleHalfHeight(1.0f);

	// Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	PawnPhysicsControllerVar = CreateDefaultSubobject<UPawnPhysicsController>(TEXT("Pawn Contoroller"));
	AddOwnedComponent(PawnPhysicsControllerVar);
	PawnPhysicsControllerVar->ComponentTags.Add(FName("ActorComponentScript"));

	
	HeliController = CreateDefaultSubobject<UHeliController>(TEXT("Heli Controller"));
	AddOwnedComponent(HeliController);
	HeliController->ComponentTags.Add(FName("ActorComponentScript"));


	
	HeliEngineNew = CreateDefaultSubobject<UHeliEngine>(TEXT("Heli Engine"));
	AddOwnedComponent(HeliEngineNew);
	HeliEngineNew->ComponentTags.Add(FName("ActorComponentScript"));

	
	HeliRotorController = CreateDefaultSubobject<UHeliRotorController>(TEXT("Heli Rotor Controller"));
	AddOwnedComponent(HeliRotorController);
	HeliRotorController->ComponentTags.Add(FName("ActorComponentScript"));


	
	HeliMainRotor = CreateDefaultSubobject<UHeliMainRotor>(TEXT("Heli Main Rotor"));
	AddOwnedComponent(HeliMainRotor);
	HeliMainRotor->ComponentTags.Add(FName("ActorComponentScript"));


	
	HeliTailRotor = CreateDefaultSubobject<UHeliTailRotor>(TEXT("Heli Tail Rotor"));
	AddOwnedComponent(HeliTailRotor);
	HeliTailRotor->ComponentTags.Add(FName("ActorComponentScript"));


	HeliCharacteristics = CreateDefaultSubobject<UHeliCharacteristics>(TEXT("Heli Characterstics"));
	AddOwnedComponent(HeliCharacteristics);
	HeliCharacteristics->ComponentTags.Add(FName("ActorComponentScript"));
	
	HeliActorComponents = GetComponentsByTag(UActorComponent::StaticClass(),FName("ActorComponentScript"));
}


void AR22Heli_Pawn::BeginPlay()
{
	Super::BeginPlay();

	//Getting Static meshes from Blueprint by name
	SM_RMainBlade = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("R22_MainRotor_Mechanical_RBlade_Geo")));
	SM_LMainBlade = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("R22_MainRotor_Mechanical_LBlade_Geo")));
	SM_RTailBlade = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("R22_Mechanical_RTailBlade_Geo")));
	SM_LTailBlade = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("R22_Mechanical_LTailBlade_Geo")));
	ForwardArrow = Cast<UArrowComponent>(GetDefaultSubobjectByName(TEXT("Forward")));
	RightArrow = Cast<UArrowComponent>(GetDefaultSubobjectByName(TEXT("Right")));
}


void AR22Heli_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FBodyInstance *Body = GetHeliRootBody()->GetBodyInstance();
	DrawDebugSphere(GetWorld(), Body->GetCOMPosition(), 5.0f, 32, FColor::Yellow);
	
}

// Called to bind functionality to input
void AR22Heli_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

		PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &AR22Heli_Pawn::SetHorizontalInput);
		PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &AR22Heli_Pawn::SetVerticalInput);
		PlayerInputComponent->BindAxis(TEXT("Throttle"), this, &AR22Heli_Pawn::SetRawThrottleInput);
		PlayerInputComponent->BindAxis(TEXT("Collective"), this, &AR22Heli_Pawn::SetRawCollectiveInput);
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

void AR22Heli_Pawn::SetRawThrottleInput(float AxisValue)
{
	ThrottleInput = AxisValue;
	SetStickyThrottleInput();
}

void AR22Heli_Pawn::SetStickyThrottleInput()
{
	StickyThrottleInput += GetRawThrottleInput() * GetWorld()->GetDeltaSeconds();
	StickyThrottleInput = FMath::Clamp(StickyThrottleInput,0.0f,1.0f);
}

void AR22Heli_Pawn::SetPedalInput(float AxisValue)
{
	PedalInput = AxisValue;
}

void AR22Heli_Pawn::SetRawCollectiveInput(float AxisValue)
{
	CollectiveInput = AxisValue;
	SetStickyCollectiveInput();
}

void AR22Heli_Pawn::SetStickyCollectiveInput()
{
	if(GetRawCollectiveInput())
	{
		StickyCollectiveInput += GetRawCollectiveInput() * GetWorld()->GetDeltaSeconds();
		// StickyCollectiveInput = FMath::Clamp(StickyCollectiveInput,0.0f,1.0f);
		StickyCollectiveInput = FMath::Clamp(StickyCollectiveInput,-1.0f,1.0f);
	}

	else StickyCollectiveInput = 0.0f;
}

void AR22Heli_Pawn::SetCyclicInput()
{
	CyclicInput.Y = VerticalInput;
	CyclicInput.X = HorizontalInput;
}


//Getter Functions

float AR22Heli_Pawn::GetHorizontalInput() const
{
	return HorizontalInput;
}

float AR22Heli_Pawn::GetVerticalInput() const
{
	return  VerticalInput;
}

float AR22Heli_Pawn::GetRawThrottleInput() const
{
	return ThrottleInput;
}

float AR22Heli_Pawn::GetStickyThrottleInput() const
{
	return StickyThrottleInput;
}

float AR22Heli_Pawn::GetPedalInput() const
{
	return PedalInput;
}

float AR22Heli_Pawn::GetRawCollectiveInput() const
{
	return CollectiveInput;
}

float AR22Heli_Pawn::GetStickyCollectiveInput() const
{
	return StickyCollectiveInput;
}

FVector2D AR22Heli_Pawn::GetCyclicInput() const
{
	return CyclicInput;
}

UStaticMeshComponent* AR22Heli_Pawn::GetHeliRootBody() const
{
	return SM_RootBody;
}

USceneComponent* const AR22Heli_Pawn::GetSCGraphics() const
{
	return SC_Graphics;
}

FBodyInstance* AR22Heli_Pawn::GetPhysicsFBodyInstance()
{
	PhysicsFBodyHandler = HeliPhysicsHandler->GetBodyInstance();
	return  PhysicsFBodyHandler;
}
