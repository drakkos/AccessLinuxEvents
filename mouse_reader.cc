// Majority of code for this comes from http://stackoverflow.com/questions/11519759/how-to-read-low-level-mouse-click-position-in-linux

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/input.h>
#include <fcntl.h>
#include <X11/Xlib.h>

#define MOUSEFILE "/dev/input/mice"

int main()
{
  int fd;
  struct input_event ie;
  Display *dpy;
  Window root, child;
  int rootX, rootY, winX, winY;
  unsigned int mask;
  int buffer[3];
  int ret;
  int clmb, llmb;

//  dpy = XOpenDisplay(NULL);

  if((fd = open(MOUSEFILE, O_RDONLY | O_NONBLOCK)) == -1) {
    perror("opening device");
    exit(EXIT_FAILURE);
  }

  while (1) {
  	ret = read (fd, buffer, 3);
  	clmb = (buffer[0] & 0x01) > 0;

	printf ("%d: LMB: %d RMB: %d MMB: %d\n", ret, buffer[0] & 0x01, buffer[0] & 0x02, buffer[0] & 0x04);

        if (clmb) {
		printf ("LMB down\n");
	}
	
	if (llmb == 1 &&  clmb == 0) {
		printf ("LMB up\n");
		return 0;
	}

	llmb = clmb;
//	printf ("%s %s %s\n", byte1 & (1 << 0x7), byte2, byte3);
  }

 return 0;
}
