#include  "RGB_LED.h"
 

#define	PINVAL(x) 	(type == COMMON_CATHOD ? (x) : (255 - (x)))



RGB_LED::RGB_LED(
	int _pinred, int _pingreen, int _pinblue , bool _type
) {
	pinred = _pinred;
	pinblue = _pinblue;
	pingreen = _pingreen;
	type = _type;
	index = 0;
	_params = NULL;
	pinMode(_pinred, OUTPUT);
	pinMode(_pingreen, OUTPUT);
	pinMode(_pinblue, OUTPUT);
	setRGB(0);
}

void RGB_LED::set (unsigned long *param, int _repeat) {
	if (!param && _params) {
		setRGB(0);
	}	
	_params = param;
	if (!_params)
		return;
	index = 0;	
	startTime = millis();
	repeat = _repeat;
	count = *param;
 Serial.println(count);
	setRGB(_params[1+index*2]);
}

int RGB_LED::tick(void) {
	int		i;
	unsigned long	t = 0;
	unsigned long	delta;

	if (!_params)
		return 0;

	delta = millis() - startTime;

	for (i=0; i<count; i++) {
		t += _params[2+i*2];
		

		if (delta > t)
			continue;

		break;
	}
  
 if (index == i)
  return 0;
  
	if (i >= count) {
		startTime = millis();
		if (repeat == 0) {
			i = 0;
		} else if (repeat == 1) {
			_params = NULL;
		} else {
			i = 0;
			
			repeat--;
		}
		if (!_params) {
			setRGB(0);
			return 0;
		} 
	} 

	index = i;
	setRGB(_params[1+index*2]);
	return 0;
} 

void RGB_LED::setRGB(unsigned long p){
	analogWrite(pinred, PINVAL(p >> 16 & 0xff));	
	analogWrite(pingreen, PINVAL(p >> 8 & 0xff));
	analogWrite(pinblue, PINVAL(p & 0xff));
}

