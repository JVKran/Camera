#ifndef __TIME_LAPSE
#define __TIME_LAPSE

#include <EEPROM.h>
#include <Arduino.h>

#include "FS.h"
#include "SD_MMC.h"
#include "esp_camera.h"
#include "fb_gfx.h"

#define EEPROM_SIZE 1

class TimeLapse {
	private:
		fs::FS &fs = SD_MMC;

		const uint32_t picturePeriod;
		uint32_t lastPicture = 0;
		uint32_t pictureNumber = 0;
	public:
		TimeLapse(const uint32_t picturePeriod);
		void begin();
		void operator()();

};

#endif //__TIME_LAPSE