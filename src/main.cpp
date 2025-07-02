#include <Arduino.h>
#include <cstring>

const String MorseDictionnary[39][2] ={
    {"A",".-"},
    {"B","-..."},
    {"C","-.-."},
    {"D","-.."},
    {"E","."},
    {"F","..-."},
    {"G","--."},
    {"H","...."},
    {"I",".."},
    {"J",".---"},
    {"K","-.-"},
    {"L",".-.."},
    {"M","--"},
    {"N","-."},
    {"O","---"},
    {"P",".--."},
    {"Q","--.-"},
    {"R",".-."},
    {"S","..."},
    {"T","-"},
    {"U","..-"},
    {"V","...-"},
    {"W",".--"},
    {"X","-..-"},
    {"Y","-.--"},
    {"Z","--.."},
    {"0","-----"},
    {"1",".----"},
    {"2","..---"},
    {"3","...--"},
    {"4","....-"},
    {"5","....."},
    {"6","-...."},
    {"7","--..."},
    {"8","---.."},
    {"9","----."},
    {",","--..--"},
    {".",".-.-.-"},
    {";","-.-.-."}
};

constexpr unsigned int freq = 2100;
constexpr unsigned int UNIT = 100; // Base Morse time unit in ms (tweak this!)

constexpr unsigned int buzzerpin = 18;
constexpr unsigned int ledpin = 19;

const String message_to_translate = "example message";

void init_buzzer (int pin) {
    // Setup the PWM channel
    ledcSetup(0, 2000, 8);    // Channel 0, 2000 Hz, 8-bit resolution
    ledcAttachPin(pin, 0); // Attach GPIO pin (passed from arg) to channel 0
}

void play_morse_string (String morse_string) {
    unsigned int length = morse_string.length();

    for (int i = 0; i < length; i++) {
        Serial.print(morse_string[i]);
        if (morse_string[i] == '.') {
            digitalWrite(ledpin, HIGH);
            ledcWriteTone(0, freq); // 1.5 kHz tone
            delay(UNIT); // Dot = 1 unit
        } else if (morse_string[i] == '-') {
            digitalWrite(ledpin, HIGH);
            ledcWriteTone(0, freq); // 1.5 kHz tone
            delay(3 * UNIT); // Dash = 3 units
        }
        digitalWrite(ledpin, LOW);
        ledcWriteTone(0, 0); // 1.5 kHz tone
        delay(UNIT);
    }
    Serial.println("");
}

void decode_message (String message) {

    // Serial.print("Will now play: \"");
    // Serial.print(message);
    // Serial.println("\"");

    String morseStringToBlink;
    unsigned int length = message.length();

    for (int x = 0; x < length; x++) {
        if (message[x] == ' ') {
            Serial.println("*** NEXT WORD ***");
            delay(7 * UNIT); // Word gap
        }
        for(int i = 0 ; i < 39 ; i++)
        {
            if(toUpperCase(message[x]) == MorseDictionnary[i][0][0]){
                morseStringToBlink = MorseDictionnary[i][1];
                Serial.print(message[x]);
                Serial.print("   ");
                play_morse_string(morseStringToBlink);
            }
        }
        delay(3 * UNIT);
    }

}

void setup() {

    Serial.begin(115200);
    Serial.print("Booting");
    init_buzzer(buzzerpin);
    pinMode(ledpin, OUTPUT);

    ledcWriteTone(0, 250); // 1.5 kHz tone
    digitalWrite(ledpin, HIGH);
    delay(150); // Play for 150ms
    ledcWriteTone(0, 450); // 1.5 kHz tone
    delay(150); // Play for 150ms
    ledcWriteTone(0, 650); // 1.5 kHz tone
    delay(500);
    ledcWriteTone(0, 0); // 1.5 kHz tone
    digitalWrite(ledpin, LOW);

    delay(500);

    Serial.println("\n\n\n");

}

void loop() {

    decode_message(message_to_translate);
    // Serial.println("Stand by...\n\n");
    Serial.println("\n\n");
    delay(2500);

}