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

#ifndef IOPort_h
#define IOPort_h

extern "C" {
	void outb  (unsigned port, unsigned value);
	void outw (unsigned port, unsigned value);
	unsigned inb  (unsigned port);
	unsigned inw  (int port);
}

class IOPort8 {
public:
	IOPort8 (unsigned char port): port(port) {}

	//! schreiben in das register
	void write (unsigned char val) const
	{
		::outb (this -> port, val);
	}

	//! lesen aus dem register
	unsigned read () const
	{
		return (::inb (this -> port));
	}

private:
	unsigned char port;
};

class IOPort16 {
public:
	IOPort16 (unsigned char port): port(port) {}

  //! schreiben in das register
	void write (unsigned char val) const
	{
		::outw (this -> port, val);
	}

	//! lesen aus dem register
	unsigned read () const
	{
		return (::inw (this -> port));
	}

private:
	unsigned char port;
};

#endif
