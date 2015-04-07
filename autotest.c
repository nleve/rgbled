#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define RGBIOCTL_MAGIC 0xB8
#define RGB_SET 	_IOW(RGBIOCTL_MAGIC, 1, colors_t *)
#define RGB_SET_RW	_IOWR(RGBIOCTL_MAGIC, 1, colors_t *)
#define RGB_READ	_IOR(RGBIOCTL_MAGIC, 1, colors_t *)	
#define ever ;;

// Tests rgb driver
// See testcases.txt for individual test details
int main(int argc, char *argv[])
{
	typedef struct {
	int red, green, blue;
	} colors_t;
	int delay = 10;
	int fh;
	colors_t c;

	fh = open("/dev/rgb", O_WRONLY);
	if (fh < 0) {
		perror("open: ");
		exit(EXIT_FAILURE);
	}
	
	// Tests:
	// 1
	errno = 0;
	if (ioctl(fh, RGB_SET, &c) < 0) {
		if (errno == EINVAL) printf("1: pass\n");
		else printf("1: fail\n");
	}
	else printf("1: fail\n");

	// 2
	errno = 0;
	c.red = -1;
	c.green = -1;
	c.blue = -1;
	if (ioctl(fh, RGB_SET, &c) < 0) {
		if (errno == EINVAL) printf("2: pass\n");
		else printf("2: fail\n");
	}
	else printf("2: fail\n");
	// 3
	errno = 0;
	c.red = -1;
	c.green = 0;
	c.blue = 0;
	if (ioctl(fh, RGB_SET, &c) < 0) {
		if (errno == EINVAL) printf("3: pass\n");
		else printf("3: fail\n");
	}
	else printf("3: fail\n");

	// 4
	errno = 0;
	c.red = 0;
	c.green = -1;
	c.blue = 0;
	if (ioctl(fh, RGB_SET, &c) < 0) {
		if (errno == EINVAL) printf("4: pass\n");
		else printf("4: fail\n");
	}
	else printf("4: fail\n");

	// 5
	errno = 0;
	c.red = 0;
	c.green = 0;
	c.blue = -1;
	if (ioctl(fh, RGB_SET, &c) < 0) {
		if (errno == EINVAL) printf("5: pass\n");
		else printf("5: fail\n");
	}
	else printf("5: fail\n");

	// 6
	errno = 0;
	c.red = 2048;
	c.green = 2048;
	c.blue = 2048;
	if (ioctl(fh, RGB_SET, &c) < 0) {
		if (errno == EINVAL) printf("6: pass\n");
		else printf("6: fail\n");
	}
	else printf("6: fail\n");

	// 7
	errno = 0;
	c.red = 2048;
	c.green = 2047;
	c.blue = 2047;
	if (ioctl(fh, RGB_SET, &c) < 0) {
		if (errno == EINVAL) printf("7: pass\n");
		else printf("7: fail\n");
	}
	else printf("7: fail\n");

	// 8
	errno = 0;
	c.red = 2047;
	c.green = 2048;
	c.blue = 2047;
	if (ioctl(fh, RGB_SET, &c) < 0) {
		if (errno == EINVAL) printf("8: pass\n");
		else printf("8: fail\n");
	}
	else printf("8: fail\n");

	// 9
	errno = 0;
	c.red = 2047;
	c.green = 2047;
	c.blue = 2048;
	if (ioctl(fh, RGB_SET, &c) < 0) {
		if (errno == EINVAL) printf("9: pass\n");
		else printf("9: fail\n");
	}
	else printf("9: fail\n");

	// 10
	errno = 0;
	c.red = 2047;
	c.green = 2047;
	c.blue = 2047;
	if (ioctl(fh, RGB_SET_RW, &c) < 0) {
		if (errno == ENOTTY) printf("10: pass\n");
		else printf("10: fail\n");
	}
	else printf("10: fail\n");

	// 11
	errno = 0;
	if (ioctl(fh, RGB_READ, &c) < 0) {
		if (errno == ENOTTY) printf("11: pass\n");
		else printf("11: fail\n");
	}
	else printf("11: fail\n");
	
	// 12
	errno = 0;
	if ((write(fh, NULL, 0)) < 0) {
		if (errno == ENOTSUP) printf("12: pass\n");
		else printf("12: fail\n");
	}
	else printf("12: fail\n");
	
	
	// 13
	errno = 0;
	if ((read(fh, NULL, 0)) == ENOTSUP) printf("13: pass\n");
	else printf("13: fail\n");
	
	
	// 14
	c.red = 0;
	c.green = 0;
	c.blue = 0;
	if (ioctl(fh, RGB_SET, &c) < 0) printf("14: fail\n");
	else printf("14: pass (LED off)\n");
	printf("Press enter to continue\n");
	getchar();
	
	
	// 15
	c.red = 2047;
	c.green = 2047;
	c.blue = 2047;
	if (ioctl(fh, RGB_SET, &c) < 0) printf("15: fail\n");
	else printf("15: pass (LED white)\n");
	printf("Press enter to continue\n");
	getchar();
	
	
	// 16
	c.red = 2047;
	c.green = 0;
	c.blue = 0;
	if (ioctl(fh, RGB_SET, &c) < 0) printf("16: fail\n");
	else printf("16: pass (LED red)\n");
	printf("Press enter to continue\n");
	getchar();
	

	// 17
	c.red = 0;
	c.green = 2047;
	c.blue = 0;
	if (ioctl(fh, RGB_SET, &c) < 0) printf("17: fail\n");
	else printf("17: pass (LED green)\n");
	printf("Press enter to continue\n");
	getchar();
	

	// 18
	c.red = 0;
	c.green = 0;
	c.blue = 2047;
	if (ioctl(fh, RGB_SET, &c) < 0) printf("18: fail\n");
	else printf("18: pass (LED blue)\n");
	printf("Press enter to continue\n");
	getchar();
	


	#if 0
	for(ever) {
		while (c.red > 0) {
			if (ioctl(fh, RGB_SET, &c) < 0)
				perror("ioctl: ");
			usleep(delay);
			c.red--;
			c.green++;
		}
		while (c.green > 0) {
			if (ioctl(fh, RGB_SET, &c) < 0)
				perror("ioctl: ");
			usleep(delay);
			c.green--;
			c.blue++;
		}
		while (c.blue > 0) {
			if (ioctl(fh, RGB_SET, &c) < 0)
				perror("ioctl: ");
			usleep(delay);
			c.blue--;
			c.red++;
		}
	}
	#endif
	close(fh);
	return 0;
}