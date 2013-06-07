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

#include "lib/Queue.h"

void Queue::enqueue (Chain* item)
{
	item -> next = 0;
	*tail = item;
	tail = &(item -> next);
}


Chain* Queue::dequeue ()
{
	Chain* item;

	item = head;
	if (item) {
		head = item -> next;
		if (!head)
			tail = &head;
		else
			item -> next = 0;
	}
	return (item);
}


void Queue::remove (Chain* item)
{
	Chain* curr;

	if (head) {
		curr = head;
		if (item == curr)
			dequeue ();
		else {
			while (curr -> next && item != curr -> next)
				curr = curr -> next;

			if (curr -> next) {
				curr -> next = item -> next;
				item -> next = 0;

				if (!curr -> next)
					tail = &(curr -> next);
			}
		}
	}
}

Chain* Queue::getItem(int posi)
{
  Chain* curr = head;
  if(posi > 0) {
    int i = 1; // jaja ok man faengt bei der null an aber trotzdem ist es das item nummer 1 und nicht null, weil head ist null
    while(curr && (i <= posi)) {
      curr = curr -> next;
      i++;
    }
  }
  return (curr);
}
