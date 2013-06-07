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
