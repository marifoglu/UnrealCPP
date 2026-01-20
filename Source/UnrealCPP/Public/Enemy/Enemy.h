// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"

class UAnimMontage;
class UAttributeComponent;	
class UHealthBarComponent;
class AAIController;
class UPawnSensingComponent;

UCLASS()
class UNREALCPP_API AEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	void DirectionalHitReact(const FVector& ImpactPoint);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
protected:
	virtual void BeginPlay() override;
	void CheckCombatTarget();
	void CheckPatrolTarget();

	// Play Montage Function  ============================================
	void PlayHitReactMontage(const FName& SectionName);
	void Die();

	UPROPERTY(BlueprintReadOnly)
	EDeathPose DeathPose = EDeathPose::EAS_Alive;

	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	
	AActor* ChoosePatrolTarget();

	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);
	
private:

	// States ============================================
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;
	
	// Components ============================================
	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* Attributes;
	
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;
	
	// Animation Montage ============================================
	UPROPERTY(EditDefaultsOnly, Category="Montages")
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	UAnimMontage* DeathMontage;

	// VFX - SFX ============================================
	UPROPERTY(EditAnywhere, Category="Sounds")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category="VisualEffects")
	UParticleSystem* HitParticles;

	// Combat ============================================
	UPROPERTY()
	AActor* CombatTarget;

	UPROPERTY(EditAnywhere)
	double CombatRadius = 500.0f;

	UPROPERTY(EditAnywhere)
	double AttackRadius = 150.0f;

	// Navigation ============================================
	UPROPERTY()
	AAIController* EnemyController;
	
	UPROPERTY(EditInstanceOnly, Category="AI NAvigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category="AI NAvigation")
	TArray<AActor*> PatrolTargets;
	
	UPROPERTY(EditAnywhere)
	double PatrolRadius = 200.0f;

	FTimerHandle PatrolTimer;
	void PatrolTimerFinished();
	
	UPROPERTY(EditAnywhere, Category="AI NAvigation")
	float WaitMin = 5.f;
	
	UPROPERTY(EditAnywhere, Category="AI NAvigation")
	float WaitMax = 10.f;
};
