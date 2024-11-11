#pragma once

#include "../Board.h"

#include <filesystem>

namespace Nonogram
{
	namespace IO
	{
		class NNParser
		{
		public:
			static void Parse(const std::filesystem::path& path, Board* out);
			static void Serialize(const Board& board, const std::filesystem::path& path);
		};
	}
}
