#define BUZZER 3
#define LED_1 4
#define LED_2 5
#define SENSOR 6

int g_state;
int g_counter;

void logToSerial(char* data, int value)
{
	Serial.print(data);
	Serial.println(value);
}

void setup()
{
	Serial.begin(9600);

	logToSerial("[init] BUZZER on D", BUZZER);
	pinMode(BUZZER, OUTPUT);
	logToSerial("[init] LED1 on D", LED_1);
	pinMode(LED_1, OUTPUT);
	logToSerial("[init] LED2 on D", LED_2);
	pinMode(LED_2, OUTPUT);
	logToSerial("[init] SENSOR on D", SENSOR);
	pinMode(SENSOR, INPUT);

	g_state = HIGH;	 // no item
	g_counter = 0;
}

int itemDetected()
{
	int state = digitalRead(SENSOR);

	if (g_state == HIGH && state == LOW) {
		Serial.println("[loop] New item detected!");
	} else if (g_state == LOW && state == HIGH) {
		Serial.println("[loop] Tracked item was lost!");
	}

	g_state = state;
	return state == LOW;
}

void loop()
{
	if (itemDetected()) {
		int opt = g_counter % 2;
		digitalWrite(LED_1, opt == 0 ? HIGH : LOW);
		digitalWrite(LED_2, opt == 1 ? HIGH : LOW);
		digitalWrite(BUZZER, opt == 0 ? LOW : HIGH);
		++g_counter;
	} else {
		digitalWrite(LED_1, LOW);
		digitalWrite(LED_2, LOW);
		digitalWrite(BUZZER, HIGH);
		g_counter = 0;
	}

	delay(500);
}
