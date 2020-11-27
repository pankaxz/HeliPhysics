// Fill out your copyright notice in the Description page of Project Settings.


#include "R22Heli_Pawn.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AR22Heli_Pawn::AR22Heli_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Physics box
	SM_PhysicsBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_PhysicsBox"));
	RootComponent = SM_PhysicsBox;
	SM_PhysicsBox->SetSimulatePhysics(true);
	SM_PhysicsBox->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	SM_PhysicsBox->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	SM_PhysicsBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	//SM_PhysicsBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	

	//Graphics group
	SC_Graphics = CreateDefaultSubobject<USceneComponent>(TEXT("SC_Graphics"));
	SC_Graphics->SetupAttachment(SM_PhysicsBox);
	
	//Colliders
	COL_Fuselage = CreateDefaultSubobject<UCapsuleComponent>(TEXT("COL_Fuselage"));
	COL_Fuselage->SetupAttachment(SM_PhysicsBox);
	COL_Fuselage->SetCapsuleRadius(16.0f);
	COL_Fuselage->SetCapsuleHalfHeight(26.0f);
	COL_Fuselage->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	COL_Fuselage->SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	COL_Fuselage->SetCollisionResponseToAllChannels(ECR_Block);
	
	COL_Mast = CreateDefaultSubobject<UCapsuleComponent>(TEXT("COL_Mast"));
	COL_Mast->SetupAttachment(SM_PhysicsBox);
	COL_Mast->SetCapsuleRadius(7.0f);
	COL_Mast->SetCapsuleHalfHeight(15.0f);
	COL_Mast->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	COL_Mast->SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	COL_Mast->SetCollisionResponseToAllChannels(ECR_Block);
	
	COL_Tail = CreateDefaultSubobject<UCapsuleComponent>(TEXT("COL_Tail"));
	COL_Tail->SetupAttachment(SM_PhysicsBox);
	COL_Tail->SetCapsuleRadius(4.0f);
	COL_Tail->SetCapsuleHalfHeight(21.0f);
	COL_Tail->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	COL_Tail->SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	COL_Tail->SetCollisionResponseToAllChannels(ECR_Block);

	COL_LSkid = CreateDefaultSubobject<UCapsuleComponent>(TEXT("COL_LSkid"));
	COL_LSkid->SetupAttachment(SM_PhysicsBox);
	COL_LSkid->SetCapsuleRadius(1.0f);
	COL_LSkid->SetCapsuleHalfHeight(20.0f);
	COL_LSkid->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	COL_LSkid->SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	COL_LSkid->SetCollisionResponseToAllChannels(ECR_Block);

	COL_RSkid = CreateDefaultSubobject<UCapsuleComponent>(TEXT("COL_RSkid"));
	COL_RSkid->SetupAttachment(SM_PhysicsBox);
	COL_RSkid->SetCapsuleRadius(1.0f);
	COL_RSkid->SetCapsuleHalfHeight(20.0f);
	COL_RSkid->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	COL_RSkid->SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	COL_RSkid->SetCollisionResponseToAllChannels(ECR_Block);
}

// Called when the game starts or when spawned
void AR22Heli_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AR22Heli_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AR22Heli_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

