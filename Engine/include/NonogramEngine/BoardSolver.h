#pragma once

#include "Board.h"

namespace Nonogram
{
	class BoardSolver
	{
	public:
		enum class SolveState
		{
			SUCCESS,
			INCOMPLETE,
			INVALID
		};

		BoardSolver(Board& board);

		BoardSolver(const BoardSolver& solver) = delete;

		SolveState Solve();

	private:
		bool validateBoardState() const noexcept;

		Board m_Board;
	};
}
