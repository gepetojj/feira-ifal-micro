#include <Tone32.h>

#define BUZZER_PIN 16
#define BUZZER_CHANNEL 0

#define TOUCH_1_PIN 15
#define TOUCH_2_PIN 2
#define TOUCH_3_PIN 32
#define TOUCH_4_PIN 33
#define TOUCH_5_PIN 27
#define TOUCH_6_PIN 14
#define TOUCH_7_PIN 12
#define TOUCH_8_PIN 13

const int threshold = 20;
int touchValue;

void setup()
{
	Serial.begin(115200);
	ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
	delay(1000);
}

void loop()
{
	if (touchValue = touchRead(TOUCH_1_PIN))
	{
		if (touchValue < threshold)
		{
			tone(BUZZER_PIN, NOTE_C4, 100, BUZZER_CHANNEL);
		}
		else
		{
			noTone(BUZZER_PIN, BUZZER_CHANNEL);
		}
	}

	if (touchValue = touchRead(TOUCH_2_PIN))
	{
		if (touchValue < threshold)
		{
			tone(BUZZER_PIN, NOTE_D4, 100, BUZZER_CHANNEL);
		}
		else
		{
			noTone(BUZZER_PIN, BUZZER_CHANNEL);
		}
	}

	if (touchValue = touchRead(TOUCH_3_PIN))
	{
		if (touchValue < threshold)
		{
			tone(BUZZER_PIN, NOTE_E4, 100, BUZZER_CHANNEL);
		}
		else
		{
			noTone(BUZZER_PIN, BUZZER_CHANNEL);
		}
	}

	if (touchValue = touchRead(TOUCH_4_PIN))
	{
		if (touchValue < threshold)
		{
			tone(BUZZER_PIN, NOTE_F4, 100, BUZZER_CHANNEL);
		}
		else
		{
			noTone(BUZZER_PIN, BUZZER_CHANNEL);
		}
	}

	if (touchValue = touchRead(TOUCH_5_PIN))
	{
		if (touchValue < threshold)
		{
			tone(BUZZER_PIN, NOTE_G4, 100, BUZZER_CHANNEL);
		}
		else
		{
			noTone(BUZZER_PIN, BUZZER_CHANNEL);
		}
	}

	if (touchValue = touchRead(TOUCH_6_PIN))
	{
		if (touchValue < threshold)
		{
			tone(BUZZER_PIN, NOTE_A4, 100, BUZZER_CHANNEL);
		}
		else
		{
			noTone(BUZZER_PIN, BUZZER_CHANNEL);
		}
	}

	if (touchValue = touchRead(TOUCH_7_PIN))
	{
		if (touchValue < threshold)
		{
			tone(BUZZER_PIN, NOTE_B4, 100, BUZZER_CHANNEL);
		}
		else
		{
			noTone(BUZZER_PIN, BUZZER_CHANNEL);
		}
	}

	if (touchValue = touchRead(TOUCH_8_PIN))
	{
		if (touchValue < threshold)
		{
			tone(BUZZER_PIN, NOTE_C5, 100, BUZZER_CHANNEL);
		}
		else
		{
			noTone(BUZZER_PIN, BUZZER_CHANNEL);
		}
	}
}
