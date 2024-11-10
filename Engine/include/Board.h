#pragma once

#include <vector>

namespace Nonogram
{
	class NonogramBoard final
	{
	public:
		using Clue = unsigned char;

		enum class CellState
		{
			EMPTY,
			FILL,
			CROSS
		};

		NonogramBoard(size_t width, size_t height);
		NonogramBoard(const NonogramBoard& board);
		NonogramBoard(NonogramBoard&& board) noexcept;

		NonogramBoard& operator=(const NonogramBoard& board);
		NonogramBoard& operator=(NonogramBoard&& board) noexcept;

		~NonogramBoard();

		size_t width() const noexcept;
		size_t height() const noexcept;
		size_t size() const noexcept;

		CellState& operator()(int x, int y);
		const CellState& operator()(int x, int y) const;

		std::vector<Clue>& rowClues(int y);
		const std::vector<Clue>& rowClues(int y) const;

		std::vector<Clue>& colClues(int x);
		const std::vector<Clue>& colClues(int x) const;

		bool validateCluesValid() const noexcept;

	private:
		size_t m_Width, m_Height;
		CellState* m_Cells;

		std::vector<Clue> *m_RowClues, *m_ColClues;
	};
}

