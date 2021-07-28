// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"
// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = capsuleComponent;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(RootComponent);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh->SetupAttachment(baseMesh);

	projectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	projectileSpawn->SetupAttachment(turretMesh);

}

void APawnBase::RotateTurret(FVector LookAtTarget) 
{

	FVector  LookAtTargetClean = FVector(LookAtTarget.X, LookAtTarget.Y, turretMesh->GetComponentLocation().Z);
	FVector StartLocation =  FVector(turretMesh->GetComponentLocation());

	FRotator TurretRotation = FVector(FVector(LookAtTargetClean - StartLocation)).Rotation();
	turretMesh->SetWorldRotation(TurretRotation);

}

void APawnBase::Fire() 
{
	// Get ProjectileSpawnPoint Location && Rotation -> Spawn Projectile class at Location firing towards Rotation

	if(ProjectileClass)
	{	
		//I need this for Cognito
		FVector SpawnLocation = projectileSpawn->GetComponentLocation();
		FRotator SpawnRotaion = projectileSpawn->GetComponentRotation(); 
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation,  SpawnRotaion);

		TempProjectile->SetOwner(this);

	}
}

void APawnBase::HandleDestruction() 
{
	// -- Universal Functionality --
	// Play death effects particle, sound and camera shake

	// -- Then do Child overrides --
	// --PawnTurret - Inform GameMode Turred Died -> Then Destroy() self 

	// -- PawnTank - Inform GameMode PlayerDied -> Then Hide() all components && stop movement input.
}



