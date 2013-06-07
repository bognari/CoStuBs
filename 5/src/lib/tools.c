// This file is part of CoStuBS.
//
// CoStuBS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CoStuBS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CoStuBS.  If not, see <http://www.gnu.org/licenses/>.

#include "lib/tools.h"

void* memcpy(void* dest, const void* src, unsigned n){

  char* a = dest;
  char* b = (char*)src;
  unsigned i = 0;
  for(i = 0; i < n; i++){
    (*a) = (*b);
    a++;
    b++;
  }

return (dest);
}


