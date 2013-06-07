#include "device/CgaChannel.h"
#include "io/PrintStream.h"

CgaChannel cga;		// unser CGA-Ausgabekanal
PrintStream out(cga);	// unseren PrintStream mit Ausgabekanal verknuepfen

int main()
{
  //  out.print('\n');
  //  out.print('\r');
  //  out.print('A');
  //  out.print('\n');
  //  out.print("BB");
    out.println("Hello World");
  //  out.print(1000, 10);
  //  out.println();
  //  out.print(1000, 16);
  //  out.println();
  //  out.print(1000, 2);
  //  out.println();
  //
  for(int i = 0; i < 1024; i++) {
    out.print("Dezimal: \t");
    out.print((unsigned)i, 10);
    out.print(" Binaer: \t");
    out.print(i, 2);
    out.print(" Hexadezimal: \t");
    out.print(i, 16);
    out.println();
  }

  //out.println("\t\tRise Against - Roadside\t\n\rTell me what I'm supposed to do  With all these leftover Feelings of you Cause I don't know And tell me how I'm supposed to feel When all these nightmares become real Cause i don't know\t\n\rAnd I don't think you see The places inside me that I find you I don't know how we seperate the lies Here from the truth Don't know how we woke up One day somehow thought we knew Exactly what we're supposed to do\t\n\rSo leave me at the roadside And hang me up and out to dry So leave me at the roadside And hang me up and out to dry\t\n\rAnd I don't think you see The places inside me that I find you I don't know how we woke up One day somehow thought we knew Exactly what we're supposed to do\t\n\rSo leave me at the roadside And hang me up and out to dry So leave me at the roadside And hang me up and out to dry\t\n\rCause I don't think you see The places inside me that I find you I don't know how we woke up One day somehow thought we knew Exactly what we're supposed to do Exactly what to do");
out.println("\t\tRise Against - The Good Left Undone\n\r\tIn fields where nothing grew but weeds. I found a flower at my feet. Bending there in my direction. I wrapped a hand around its stem. And pulled until the roots gave in. Finding there what. I'd been missing.\n\r\tAnd I know… So I tell myself, I tell myself it's wrong. There's a point we pass from which we can't return. I felt the cold rain of the coming storm.\n\r\tAll because of you. I haven't slept in so long. When I do I dream of drowning in the ocean. Longing for the shore where I can lay my head down. I'll follow your voice. All you have to do is shout it out.\n\r\tInside my hands these petals browned. Dried up, fallen to the ground. But it was already too late now. I pushed my fingers thru the earth. Returned this flower to the dirt. So it could live I walked away now.\n\r\tI know… Not a day goes by that I don't feel this burn. There's a point we pass from which we can't return. I felt the cold rain of the coming storm.\n\r\tAll because of you. I haven't slept in so long. When I do I dream of drowning in the ocean. Longing for the shore where I can lay my head down. I'll follow your voice. All you have to do is shout it out.\n\r\tAll because of you. All because of you.\n\r\tAll because of you. I haven't slept in so long. When I do I dream of drowning in the ocean. Longing for the shore where I can lay my head down. Inside these arms of yours.\n\r\tAll because of you. I believe in angels. Not the kind with wings. No, not the kind with halos. The kind that bring you home. When home becomes a strange place. I'll follow your voice. All you have to do is shout it out.");
  //out.println("done");

  while(1){}

return 0;
}
