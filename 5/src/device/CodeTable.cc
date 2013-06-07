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

#include "device/CodeTable.h"

bool CodeTable::lookup[256];

const unsigned char CodeTable::normalAscii[] =
{
//	0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf
	0,   27,   '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 225, 39,  '\b','\t',//0x0
	'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', 129, '+','\n', 0,   'a', 's', //0x1
	'd', 'f', 'g', 'h', 'j', 'k', 'l', 148, 132, '^', 0,   '#',	'y', 'x', 'c', 'v', //0x2
	'b', 'n', 'm', ',', '.', '-', 0,   '*', 0,   ' ', 0,   0,   0,   0,   0,   0,   //0x3
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   '-', 0,   0,   0,   '+', 0,   //0x4
	0,   0,   0,   0,   0,   0,   '<', 0,   0,   0,   0,   0,   0,   0,   0,   0,   //0x5
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   //0x6
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    //0x7
};

const unsigned char CodeTable::shiftAscii[] =
{
//	0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf
	0,   27,  '!', '"', 21,  '$', '%', '&', '/', '(', ')', '=', '?', 96,  0,   0,   //0x0
	'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'P', 154, '*', 0,	 0,   'A', 'S', //0x1
	'D', 'F', 'G', 'H', 'J', 'K', 'L', 153, 142, 248, 0,   39,  'Y', 'X', 'C', 'V', //0x2
	'B', 'N', 'M', ';', ':', '_', 0,   0,   0,   ' ', 0,   0,   0,   0,   0,   0,   //0x3
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   '-', 0,   0,   0,   '+', 0,   //0x4
	0,   0,   0,   0,   0,   0,   '>', 0,   0,   0,   0,   0,   0,   0,   0,   0,   //0x5
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   //0x6
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    //0x7
};

const unsigned char CodeTable::strgAscii[] =
{
//	0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf
	0,   27,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   //0x0
	17,  23,  5,   18,  20,  26,  21,  9,   15,  16,  27,  0,   10,	 0,   1,   19,  //0x1
	4,   6,   7,   8,   10,  11,  12,  0,   0,   0,   0,   0,   25,  24,  3,   22,  //0x2
	2,   14,  13,  0,   0,   0,   0,   0,   0,   20,  0,   0,   0,   0,   0,   0,   //0x3
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   //0x4
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   //0x5
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   //0x6
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    //0x7
};

const unsigned char CodeTable::altAscii[] =
{
//	0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf
	0,   0,   '�', '�', 0,   0,   0,   0,   '{', '[', ']', '}', '\\',0,   0,   0,   //0x0
	'@', 0,   '�', 0,   0,   0,   0,   0,   0,   0,   0,   '~', 0,	 0,   0,   0,   //0x1
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   //0x2
	0,   0,   '�', 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   //0x3
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   //0x4
	0,   0,   0,   0,   0,   0, '|',   0,   0,   0,   0,   0,   0,   0,   0,   0,   //0x5
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   //0x6
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    //0x7
};

const unsigned char CodeTable::numblockAscii[] =
{
	'7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', ','
};


