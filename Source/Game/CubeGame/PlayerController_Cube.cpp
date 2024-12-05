// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController_Cube.h"
#include "CubeBase.h"
#include "CubeDataRow.h"
#include "EnhancedInputComponent.h"
#include "Inputs.h"
#include "PawnInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "HUD_Cube.h"
#include "Blueprint/UserWidget.h"
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
		EIP->BindAction(_SwapChar, ETriggerEvent::Started, this , &APlayerController_Cube::SwapChar);
		EIP->BindAction(_PauseAI, ETriggerEvent::Started, this , &APlayerController_Cube::PauseAI);
	}
	
}

void APlayerController_Cube::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
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
	isMoving = true;
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

void APlayerController_Cube::SwapChar()
{
	_NPCCharacterArray.Add(_PossessedPawn);
	
	int CharIndex = 0;
	for(AAIController_Cube* AiController : _AiControllers)
	{
		AiController->Possess(_NPCCharacterArray[CharIndex]);
		CharIndex++;
	}
	
	_PossessedPawn = _NPCCharacterArray[0];
	this->Possess(_PossessedPawn);
	_NPCCharacterArray.RemoveAt(0);

	for (AAIController_Cube* con : _AiControllers)
	{
		con->_CurrentlyActivePawn = _PossessedPawn;
	}
	
}

void APlayerController_Cube::PauseAI()
{
	for(AAIController_Cube* AiController : _AiControllers)
	{
		AiController->PuaseBehaviorTree();
	}
	_HUDWidget->ToggleAiFollow();
}


void APlayerController_Cube::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void APlayerController_Cube::BeginPlay()
{
	Super::BeginPlay();

	if(_HUDWidgetClass)
	{	
		_HUDWidget = CreateWidget<UHUD_Cube, APlayerController_Cube*>(this, _HUDWidgetClass.Get());
		_HUDWidget->AddToViewport();
		_HUDWidget->UpdateCoinsText(_CurrentCoins);
		_HUDWidget->DefaultHintText();
	}
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());

		if (InputSubsystem && _InputMapping)
		{
			InputSubsystem->AddMappingContext(_InputMapping, 1);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("InputSubsystem or _InputMapping is null in PlayerController_Cube"));
		}
	

	FindPlayerStart_Implementation();
	
	if(_CubeDataTable)
	{
		FString ContextString(TEXT("Cube Data Retrieval"));
		TArray<FCubeDataRow*> DataRows;
		_CubeDataTable->GetAllRows<FCubeDataRow>(ContextString, DataRows);
		
		FActorSpawnParameters _ActorSpawnParameters;
		_ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		

		float _SpawnRadius = (DataRows.Num() * 200.0f);
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
					UE_LOG(LogTemp, Warning, TEXT("Failed to find player start, Spawning at 10,10,10"));
				}

				
				ACubeBase* Obj = GetWorld()->SpawnActor<ACubeBase>(_CubeBase, FVector(), FRotator::ZeroRotator, _ActorSpawnParameters);
				
				AAIController_Cube* AiController = GetWorld()->SpawnActor<AAIController_Cube>(_AiControllerBluePrint);

				
				
				if (Obj && AiController)
				{
					_NPCCharacterArray.Add(Obj);
					_AllCharacterArray.Add(Obj);
					_AiControllers.Add(AiController);
					if (Row->CubeDataAsset)
					{
						if(UKismetSystemLibrary::DoesImplementInterface(Obj, UPawnInterface::StaticClass()))
						{
							IPawnInterface::Execute_Pawn_Init(Obj, Row->CubeDataAsset, FVector(_RandomPoint.X, _RandomPoint.Y, 0));
						}
						
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

				if(UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
				{
					if(UKismetSystemLibrary::DoesImplementInterface(Obj, UInputs::StaticClass()))
					{
						subsystem->AddMappingContext(IInputs::Execute_GetMappingContext(Obj), 0);
					}
				}
			}
		}

		if(!_NPCCharacterArray.IsEmpty())
		{
			int CharIndex = 0;
			for(AAIController_Cube* AiController : _AiControllers)
			{
				AiController->Possess(_NPCCharacterArray[CharIndex]);
				CharIndex++;
			}
			_PossessedPawn = _NPCCharacterArray[0];
			this->Possess(_PossessedPawn);
			_NPCCharacterArray.RemoveAt(0);
			for (AAIController_Cube* con : _AiControllers)
			{
				con->_CurrentlyActivePawn = _PossessedPawn;
				
			}
		}
		
	}
	OnPlayerControllerReady.Broadcast();
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

void APlayerController_Cube::AllCoinsCollected_Implementation()
{
	_HUDWidget->EndLevelHintText();
}

void APlayerController_Cube::EnableWinText_Implementation()
{
	_HUDWidget->EnableWinText();
}

void APlayerController_Cube::CubesOnPlatform_Implementation(int amount)
{
	if(amount == _AllCharacterArray.Num())
	{
		//Check1
		
		TMap<ACubeBase*, float> CharMap;
		for (ACubeBase* character : _AllCharacterArray)
		{
			CharMap.Add(character, character->_StaticMesh->GetComponentLocation().Z);
			FString CharacterName = character->GetName();
			UE_LOG(LogTemp, Display, TEXT("Character '%s' Z level %f"), *CharacterName , character->GetActorLocation().Z);
		}

		bool HasUniqueValues = true;
		TSet<float> SeenValues;
		for (const auto& Elem : CharMap)
		{
			float Value = Elem.Value;

			for (float SeenValue : SeenValues)
			{
				// Check if SeenValue is within RangeThreshold of Value
				if (FMath::Abs(SeenValue - Value) <= 5.0f)
				{
					HasUniqueValues = false;
					break;  // Exit the loop as soon as we find a near match
				}
			}

			// If no near match is found, add the value to SeenValues
			if (HasUniqueValues)
			{
				SeenValues.Add(Value);
			}
		}
		//check2
		for(ACubeBase* Char : _AllCharacterArray)
		{
			if(Char->bCanJump == false)
			{
				UE_LOG(LogTemp, Warning, TEXT("Duplicate values found in CharMap."));
				return;
			}
		}
		if(HasUniqueValues)
		{
			UE_LOG(LogTemp, Log, TEXT("All values are unique."));
			OnStacked.Broadcast();
		}
	}
}

APlayerController_Cube* APlayerController_Cube::GetPlayerController_Implementation()
{
	return this;
}

void APlayerController_Cube::SetCoins_Implementation(int coins)
{
	_CurrentCoins = coins;
	if(_HUDWidget)
	{
		_HUDWidget->UpdateCoinsText(_CurrentCoins);
	}
}


FVector APlayerController_Cube::GetCombineCubeSize_Implementation()
{
	for (ACubeBase* Cube : _AllCharacterArray)
	{
		if(Cube)
		{
			_CombinedCubeExtents += Cube->_CubeExtents3D;
			
		}
	}
	return _CombinedCubeExtents;
}




