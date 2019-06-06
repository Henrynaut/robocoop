// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SArm.generated.h"

class USkeletalMeshComponent;
class UDamageType;

UCLASS()
class ROBOCOOP_API ASArm : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASArm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;

	UFUNCTION(BlueprintCallable, Category = "Arm")
	void Grab();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arm")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Arm")
		FName MuzzleSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Arm")
		FName TracerTargetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arm")
		UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arm")
		UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arm")
		UParticleSystem* TracerEffect;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
