// Fill out your copyright notice in the Description page of Project Settings.


#include "SArm.h"

// Sets default values
ASArm::ASArm()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Robotic arm and set it as the root component
	MeshComp = CreateAbstractDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ASArm::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASArm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

