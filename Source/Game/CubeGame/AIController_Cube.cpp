
#include "AIController_Cube.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
AAIController_Cube::AAIController_Cube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

ACubeBase* AAIController_Cube::newPawn_Implementation()
{
	return _CurrentlyActivePawn;
}

void AAIController_Cube::PuaseBehaviorTree()
{
	_BlackboardComponent->SetValueAsBool(TEXT("Pause"), !_BlackboardComponent->GetValueAsBool(TEXT("Pause")));
}

// Called when the game starts or when spawned
void AAIController_Cube::BeginPlay()
{
	Super::BeginPlay();
}

void AAIController_Cube::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(_BehaviourTree);
	_BlackboardComponent = this->GetBlackboardComponent();
}

// Called every frame
void AAIController_Cube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

