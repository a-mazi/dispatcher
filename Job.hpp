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

#include <mutex>
#include <set>
#include <condition_variable>

class Job
{
public:
  Job() = delete;
  inline Job(int jobSlot) : jobSlot{jobSlot} {};

  static std::mutex executionControl;
  static std::set<int> jobsDone;
  static std::condition_variable jobReady;

protected:
  void notifyDone();

private:
  const int jobSlot;
};
