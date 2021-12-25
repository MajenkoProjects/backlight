#include <stdio.h>
#include <stdlib.h>

const char *root = "/sys/class/backlight/intel_backlight";

int getValue(const char *item) {
	char temp[1024];
	snprintf(temp, 1024, "%s/%s", root, item);
	FILE *f = fopen(temp, "r");
	if (!f) {
		return -1;
	}
	fgets(temp, 1024, f);
	fclose(f);
	return strtol(temp, NULL, 10);
}

int main(int argc, char **argv) {
	char temp[1024];

	if (argc != 2) {
		printf("Usage: backlight <percent>\n");
		return -1;
	}

	int max_brightness = getValue("max_brightness");
	int current_brightness = getValue("brightness");

	int current_percent = current_brightness * 100 / max_brightness;

	int percent = current_percent;

	if (argv[1][0] == '+') {
		percent += strtol(argv[1]+1, NULL, 10);
	} else if (argv[1][0] == '-') {
		percent -= strtol(argv[1]+1, NULL, 10);
	} else {
		percent = strtol(argv[1], NULL, 10);
	}

	if (percent < 0) percent = 0;
	if (percent > 100) percent = 100;

	int out = max_brightness * percent / 100;

	snprintf(temp, 1024, "%s/brightness", root);
	FILE *f = fopen(temp, "w");
	if (!f) {
		printf("Unable to open %s\n", temp);
		return -1;
	}
	fprintf(f, "%d\n", out);
	fclose(f);

	return 0;
}
