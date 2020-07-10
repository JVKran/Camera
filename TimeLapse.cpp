#include "TimeLapse.hpp"

TimeLapse::TimeLapse(const uint32_t picturePeriod):
	picturePeriod(picturePeriod)
{}

void TimeLapse::begin(){
	if(!SD_MMC.begin()){
		return;
	}

	uint8_t cardType = SD_MMC.cardType();
	if(cardType == CARD_NONE){
		return;
	}

	EEPROM.begin(EEPROM_SIZE);
}

void TimeLapse::operator()(){
	if(millis() - lastPicture > picturePeriod){
		lastPicture = millis();
		camera_fb_t * fb = NULL;
		fb = esp_camera_fb_get();  
		if(!fb) {
			return;
		}

		String path = "/picture" + String(pictureNumber++) +".jpg";
		File file = fs.open(path.c_str(), FILE_WRITE);
		if(file){
			file.write(fb->buf, fb->len);
			EEPROM.write(0, pictureNumber);
			EEPROM.commit();
			file.close();
		}
		esp_camera_fb_return(fb);
	}
}