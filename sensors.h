#include <ADS1X15.h>

namespace sensors{
	void ads_init();

	int16_t read_int(int chnum);

	void sensors_init();

	float get_temp();
}