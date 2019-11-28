// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#pragma once

#include "CoreMinimal.h"

/**
 * Helper class to solve the queen problem.
 */

class QUEENPROBLEM_API Solution {
public:
	TArray<int32> positions;
	float energy;

	Solution& operator=(const Solution& solution);
};