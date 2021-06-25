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

template <class Source>
class RangeBasedForLoopAdapter
{
public:
  RangeBasedForLoopAdapter() = delete;
  explicit RangeBasedForLoopAdapter(const RangeBasedForLoopAdapter& adapter) : adaptee{adapter.adaptee} {}
  explicit RangeBasedForLoopAdapter(Source& adaptee) : adaptee{adaptee} {}

  RangeBasedForLoopAdapter begin() const {return RangeBasedForLoopAdapter{*this};};
  RangeBasedForLoopAdapter end()   const {return RangeBasedForLoopAdapter{*this};};

  auto operator*() const{return adaptee.getData();}
  bool operator!=(const RangeBasedForLoopAdapter& rhs) const {return !adaptee.isEmpty();}
  void operator++() const {adaptee.advance();}

private:
  Source& adaptee;
};
