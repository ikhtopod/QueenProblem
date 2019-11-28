// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#pragma once

#include "Solution.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chessboard.generated.h"

UCLASS()
class QUEENPROBLEM_API AChessboard : public AActor {
	GENERATED_BODY()

private:
	static constexpr int32 BOARD_LENGTH = 8;

	Solution m_solution {};

public:
	AChessboard();

public:
	// Solve the Queen problem using the Annealing simulation algorithm.
	UFUNCTION(BlueprintCallable, Category = "QueenProblem")
		TArray<int32> SolveQueenProblem();

	// Return last solution.
	UFUNCTION(BlueprintPure, Category = "QueenProblem")
		TArray<int32> GetLastSolution() const;

private:
	void InitSolution();
	void RandomSwap();
	void UpdateEnergy();
	void UpdateSolution();
};
