// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController_Cube.h"

#include "CubeBase.h"
#include "CubeDataRow.h"
#include "EnhancedInputComponent.h"
#include "Inputs.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"


void APlayerController_Cube::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIP->BindAction(_LookAction, ETriggerEvent::Triggered, this, &APlayerController_Cube::Look);
		EIP->BindAction(_MoveAction, ETriggerEvent::Triggered, this, &APlayerController_Cube::Move);
		EIP->BindAction(_JumpAction, ETriggerEvent::Triggered, this, &APlayerController_Cube::JumpPressed);
		EIP->BindAction(_JumpAction, ETriggerEvent::Completed, this, &APlayerController_Cube::JumpReleased);
		EIP->BindAction(_SwapChar, ETriggerEvent::Started, this , &APlayerController_Cube::SwapChar);
	}
	
}

void APlayerController_Cube::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	UE_LOG(LogTemp, Display, TEXT("X: %f Y: %f"), LookVector.X, LookVector.Y);
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputs::StaticClass()))
		{
			IInputs::Execute_Input_Look(currentPawn, LookVector);
		}
	}
}

void APlayerController_Cube::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputs::StaticClass()))
		{
			IInputs::Execute_Input_Move(currentPawn, MoveVector);
		}
	}
}

void APlayerController_Cube::JumpPressed()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputs::StaticClass()))
		{
			IInputs::Execute_Input_JumpPressed(currentPawn);
		}
	}
}

void APlayerController_Cube::JumpReleased()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputs::StaticClass()))
		{
			IInputs::Execute_Input_JumpReleased(currentPawn);
		}
	}
}

void APlayerController_Cube::SwapChar()
{
	_CurrentCharacter++;
	if(_CurrentCharacter == _CharacterArray.Num())
	{
		_CurrentCharacter = 0;
	}
	this->Possess(_CharacterArray[_CurrentCharacter]);
}

void APlayerController_Cube::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(UKismetSystemLibrary::DoesImplementInterface(InPawn, UInputs::StaticClass()))
		{
			subsystem->AddMappingContext(IInputs::Execute_GetMappingContext(InPawn), 0);
		}
	}
}

void APlayerController_Cube::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PC = Cast<APlayerController>(this))
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

		if (InputSubsystem && _InputMapping)
		{
			InputSubsystem->AddMappingContext(_InputMapping, 1);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("InputSubsystem or _InputMapping is null in PlayerController_Cube"));
		}
	}

	FindPlayerStart_Implementation();
	
	if(_CubeDataTable)
	{
		FString ContextString(TEXT("Cube Data Retrieval"));
		TArray<FCubeDataRow*> DataRows;
		_CubeDataTable->GetAllRows<FCubeDataRow>(ContextString, DataRows);
		
		FActorSpawnParameters _ActorSpawnParameters;
		_ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		float _SpawnRadius = (DataRows.Num() * 100.0f);
		FVector _RandomPoint;
		for (FCubeDataRow* Row : DataRows)
		{
			if (Row)
			{
				if(_PlayerStarts[0])
				{
					_RandomPoint = _PlayerStarts[0]->GetActorLocation() + FMath::VRand() * FMath::RandRange(0.0f, _SpawnRadius);
				}
				else
				{
					_RandomPoint = FVector(10,10,10);
					UE_LOG(LogTemp, Warning, TEXT("Failed to get random location"));
				}
				
				ACubeBase* Obj = GetWorld()->SpawnActor<ACubeBase>(ACubeBase::StaticClass(), FVector(), FRotator::ZeroRotator, _ActorSpawnParameters);
        
				if (Obj)
				{
					_CharacterArray.Add(Obj);
					if (Row->CubeDataAsset)
					{
						Obj->Init(Row->CubeDataAsset);
						Obj->SetActorLocation(FVector(_RandomPoint.X, _RandomPoint.Y, 10.0f));
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Row's CubeDataAsset is null"));
					}
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to spawn Cube Actor from _CubeClass"));
				}
			}
		}

		if(!_CharacterArray.IsEmpty())
		{
			this->Possess(_CharacterArray[0]);
		}
		
	}
}

void APlayerController_Cube::FindPlayerStart_Implementation()
{
	if(_PlayerStarts.Num() == 0)
	{
		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), foundActors);
		for(AActor* actor : foundActors)
		{
			_PlayerStarts.Add(actor);
		}
	}
}


