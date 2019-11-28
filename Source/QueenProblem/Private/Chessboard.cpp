// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#include "Chessboard.h"
#include "Misc/DateTime.h"

#include <numeric>


AChessboard::AChessboard() {
	PrimaryActorTick.bCanEverTick = true;

	FMath::SRandInit(static_cast<int32>(FDateTime::Now().ToUnixTimestamp()));

	m_solution.positions.SetNum(BOARD_LENGTH);
}

TArray<int32> AChessboard::SolveQueenProblem() {
	do {
		UpdateSolution();
	} while (m_solution.energy != 0);

	return m_solution.positions;
}


TArray<int32> AChessboard::GetLastSolution() const {
	return m_solution.positions;
}

void AChessboard::InitSolution() {
	std::iota(m_solution.positions.begin(), m_solution.positions.end(), 0);

	for (int32 i = 0; i < m_solution.positions.Num(); ++i) {
		RandomSwap();
	}
}

void AChessboard::RandomSwap() {
	const int32 MIN_RAND_RANGE { 0 };
	const int32 MAX_RAND_RANGE { BOARD_LENGTH - 1 };

	int32 x = FMath::RandRange(MIN_RAND_RANGE, MAX_RAND_RANGE);
	int32 y = FMath::RandRange(MIN_RAND_RANGE, MAX_RAND_RANGE);

	while (x == y) {
		y = FMath::RandRange(MIN_RAND_RANGE, MAX_RAND_RANGE);
	}

	Swap<int32>(m_solution.positions[x], m_solution.positions[y]);
}

void AChessboard::UpdateEnergy() {
	const float STEP = 1.0f;
	const int32 dx[4] { 1, 1, -1, -1 };
	const int32 dy[4] { 1, -1, 1, -1 };

	bool board[BOARD_LENGTH][BOARD_LENGTH] {};
	for (int32 i = 0; i < BOARD_LENGTH; ++i) {
		board[i][m_solution.positions[i]] = true;
	}

	m_solution.energy = 0.0f;
	for (int32 i = 0; i < m_solution.positions.Num(); ++i) {
		int32 x = i, y = m_solution.positions[i];

		for (int32 j = 0; j < 4; ++j) {
			int32 xTmp = x, yTmp = y;

			while (true) {
				xTmp += dx[j];
				yTmp += dy[j];

				if ((xTmp < 0 || xTmp >= m_solution.positions.Num()) ||
					(yTmp < 0 || yTmp >= m_solution.positions.Num())) {
					break;
				}//fi

				if (board[xTmp][yTmp]) {
					m_solution.energy += STEP;
				}//fi
			}//elihw
		}//rof
	}//rof
}

void AChessboard::UpdateSolution() {
	Solution working, best;
	working.positions.SetNum(BOARD_LENGTH);
	best.positions.SetNum(BOARD_LENGTH);
	bool isSolved = false;

	best.energy = 100.0f;

	InitSolution();
	UpdateEnergy();
	working = m_solution;

	float temperature = 30.0f;
	while (temperature > .5f) {
		for (int32 step = 0; step < 100; ++step) {
			bool useNew = false;

			RandomSwap();
			UpdateEnergy();

			if (working.energy <= m_solution.energy) {
				useNew = true;
			} else {
				float test = FMath::SRand();
				float delta = working.energy - m_solution.energy;
				float calc = FMath::Exp(-delta / temperature);

				if (calc > test) {
					useNew = true;
				}
			}

			if (useNew) {
				useNew = false;
				m_solution = working;

				if (m_solution.energy < best.energy) {
					best = m_solution;
					isSolved = true;
				}
			} else {
				working = m_solution;
			}
		}

		temperature *= .98f;
	}

	if (isSolved) {
		m_solution = best;
		isSolved = false;
	}
}
