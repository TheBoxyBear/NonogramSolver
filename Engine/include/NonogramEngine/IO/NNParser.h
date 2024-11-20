#pragma once

#include "../Board.h"
#include "../Utils/rawalloc.h"

#include <filesystem>

namespace Nonogram
{
	namespace IO
	{
		class NNParser
		{
		public:
			static void parse(const std::filesystem::path& path, rawalloc<Board>& out);
			static void serialize(const Board& board, const std::filesystem::path& path);
		};
	}
}
