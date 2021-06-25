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

#include <vector>
#include <future>
#include <mutex>
#include <iostream>

template <class Processor, typename SourceData, typename SinkData, class Source, class Sink, typename... ProcessorArgs>
void dispatcher(Source&& source, Sink&& sink, int maxJobs = 1, bool verb = false, ProcessorArgs... processorArgs)
{
  std::vector<std::future<SinkData>> jobsContainer{};
  for (int i = 0; i < maxJobs; i++)
  {
    jobsContainer.push_back(std::future<SinkData>{});
  }

  int busyCount = 0;
  {
    std::unique_lock<std::mutex> taskReadyLock{Processor::executionControl};
    for (SourceData sourceData : source)
    {
      if (verb) std::cout << "+";
      for (int jobSlot : Processor::jobsDone)
      {
        auto& job = jobsContainer[jobSlot];
        sink(job.get());
        busyCount--;
      }
      Processor::jobsDone.clear();

      for (int jobSlot = 0; jobSlot < maxJobs; jobSlot++)
      {
        auto& job = jobsContainer[jobSlot];
        if (!job.valid())
        {
          job = std::async(std::launch::async, Processor{jobSlot}, sourceData, processorArgs...);
          busyCount++;
          break;
        }
      }

      if (busyCount == maxJobs)
      {
        Processor::jobReady.wait(taskReadyLock, []{return !Processor::jobsDone.empty();});
      }
    }
  }

  for (int jobNo = 0; jobNo < maxJobs; jobNo++)
  {
    auto& job = jobsContainer[jobNo];
    if (job.valid())
    {
      sink(job.get());
    }
  }
  Processor::jobsDone.clear();
}
