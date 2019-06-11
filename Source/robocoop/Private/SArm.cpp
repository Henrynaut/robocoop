// Fill out your copyright notice in the Description page of Project Settings.


#include "SArm.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ASArm::ASArm()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Robotic arm and set it as the root component
	MeshComp = CreateAbstractDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	MuzzleSocketName = "MuzzleSocket";
	TracerTargetName = "Target";

	//Enable as Replicated Actor
	SetReplicates(true);
}

// Called when the game starts or when spawned
void ASArm::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASArm::Grab()
{
	//Trace the world, from pawn eyes to crosshair location

	////If the Role is a client, only run the ServerGrab function,
	////passing a request to the server
	//if (Role < ROLE_Authority)
	//{
	//	ServerGrab();
	//	return;
	//}

	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();

		//Create a direction vector for the raycast
		FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 10000);

		//Create QueryParams Struct that lets us ignore the owner and robot arm
		//However, it traces against each individual triangle of the mesh it is hitting (Complex Collision)
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		//Particle "Target" Parameter
		FVector TracerEndPoint = TraceEnd;

		FHitResult Hit;

		//Define a raycast with a Hit Result, Start, End, Collision Channel, and FCollisionQueryParams Parameter
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			// On Blocking Hit, process Arm Grab

			AActor* HitActor = Hit.GetActor();

			UGameplayStatics::ApplyPointDamage(HitActor, 20.0f, ShotDirection, Hit, MyOwner->GetInstigatorController(), this, DamageType);


			//If grab crosshair has a hit (collides), spawn emitter attached to hit location
			if (ImpactEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
			}

			TracerEndPoint = Hit.ImpactPoint;
		}

		//Create a debug line with start and end locations, color, render time, depth priority, and thickness)
		//DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);

		//Check if Muzzle Effect exists so the engine doesn't crash
		if (MuzzleEffect)
		{
			//Spawn Emitter on Arm
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);
		}


		if (TracerEffect)
		{
			FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);

			//Spawn Emitter tractor beam attached to arm
			UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAttached(TracerEffect, MeshComp, MuzzleSocketName, MuzzleLocation);
			
			//Spawn Static Emitter
			//UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect, MuzzleLocation);

			//if (TracerComp)
			//	{
			//	TracerComp->SetVectorParameter(TracerTargetName, TracerEndPoint);
			//	}

		}
	}
}

//void ASArm::ServerGrab()
//{
//	Grab();
//}

// Called every frame
void ASArm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


////UE4 requires "Server" prefix and "_Implementation" afterwards
//void ASArm::ServerGrab_Implementation()
//{
//	Grab();
//}
//
//bool ASArm::ServerGrab_Validate()
//{
//	return true;
//}

