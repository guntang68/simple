#include "Arduino.h"
#include <LocSpiff.h>



void setup()
{
	Serial.begin(912600, SERIAL_8N1, 3, 1);
	delay(300);
	log_i("\n\n\n\nSalam Dunia dari %s\n\n\n\n", __FILE__);
	log_i("Memory = %d", String(esp_get_free_heap_size()).c_str());

	//initial program load Memory = 1073447996



}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
}
