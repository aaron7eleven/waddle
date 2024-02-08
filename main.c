#include "waddle.h"

//waddle g_waddle;

int main(int argc, char* argv[])
{	
	waddle_log("Starting Waddle");
	waddle waddle;
	if (waddle_init(&waddle)) {
		return 1;
	}

	while (!waddle.quit)
	{
		waddle_run(&waddle);

		if (waddle.restart) {
			waddle_free(&waddle);
			if (waddle_init(&waddle)) {
				return 1;
			}
		}
	}

	waddle_free(&waddle);

	return 0;
}