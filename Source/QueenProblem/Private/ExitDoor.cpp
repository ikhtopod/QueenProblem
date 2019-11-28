// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#include "ExitDoor.h"
#include "GameFramework/WorldSettings.h"
#include "Kismet/KismetSystemLibrary.h"


AExitDoor::AExitDoor() {
	PrimaryActorTick.bCanEverTick = true;
}

void AExitDoor::QuitGame() {
	UObject* world { Cast<UObject>(GetWorld()) };
	APlayerController* playerController { GetWorld()->GetFirstPlayerController() };

	UKismetSystemLibrary::QuitGame(world, playerController, EQuitPreference::Type::Quit, false);
}

void AExitDoor::Interact_Implementation() {
	this->QuitGame();
}
