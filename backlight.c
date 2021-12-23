#include <stdio.h>
#include <stdlib.h>

const char *root = "/sys/class/backlight/intel_backlight";

int main(int argc, char **argv) {
	char temp[1024];

	snprintf(temp, 1024, "%s/max_brightness", root);
	FILE *f = fopen(temp, "r");
	fgets(temp, 1024, f);
	fclose(f);
	int maxb = strtol(temp, NULL, 10);

	if (argc != 2) {
		printf("Usage: backlight <percent>\n");
		return -1;
	}

	int pct = strtol(argv[1], NULL, 10);
	if (pct < 0) pct = 0;
	if (pct > 100) pct = 100;

	int out = maxb * pct / 100;

	snprintf(temp, 1024, "%s/brightness", root);
	f = fopen(temp, "w");
	if (!f) {
		printf("Unable to open %s\n", temp);
		return -1;
	}
	fprintf(f, "%d\n", out);
	fclose(f);

	return 0;
}
