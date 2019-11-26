// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#pragma once

#include "QueenProblem/Public/Interfaces/Interactable.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExitDoor.generated.h"

UCLASS(BlueprintType)
class QUEENPROBLEM_API AExitDoor : public AActor, public IInteractable {
	GENERATED_BODY()

public:
	AExitDoor();

private:
	void QuitGame();

public: // IInteractable
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "QueenProblem|Interface")
		void Interact();
	virtual void Interact_Implementation() override;
};
