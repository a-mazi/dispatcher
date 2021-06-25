/* Copyright © Artur Maziarek MMXXI
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */
#pragma once
#include <string>
#include <vector>
#include <fstream>

class FileSource
{
public:
  FileSource(std::string fileName, size_t lineChunkSize = 1, int chunks = 0);

  std::vector<std::string> getData();
  bool isEmpty() const;
  void advance();

private:
  const std::string fileName{};
  const size_t lineChunkSize{1};
  int chunks{0};
  bool isParsingSizeLimited{false};
  std::ifstream file{};
  std::vector<std::string> lineChunk{};

  bool isBufferEmpty[2]{false, false};
  size_t isbufferEmptyIterator{0};
};
