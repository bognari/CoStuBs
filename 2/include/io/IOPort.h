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
	IOPort8 (unsigned port): port(port) {}

	void write (unsigned val) const
	{
		::outb (port, val);
	}

	unsigned read () const
	{
		return ::inb (port);
	}

private:
	unsigned port;
};

class IOPort16 {
public:
	IOPort16 (unsigned port): port(port) {}

	void write (unsigned val) const
	{
		::outw (port, val);
	}

	unsigned read () const
	{
		return ::inw (port);
	}

private:
	unsigned port;
};

#endif
