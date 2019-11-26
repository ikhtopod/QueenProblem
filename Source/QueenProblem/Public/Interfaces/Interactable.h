// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(BlueprintType)
class UInteractable : public UInterface {
	GENERATED_BODY()
};

/**
 * Interface for interaction.
 */
class QUEENPROBLEM_API IInteractable {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "QueenProblem|Interface")
		void Interact();
};
