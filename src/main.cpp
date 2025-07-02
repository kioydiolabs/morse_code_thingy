#include <Arduino.h>
#define BUZZERPIN 11
#define LEDPIN 12

#define FREQUENCY 2100
#define UNIT 100

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

const String message_to_translate = "example message";

void play_morse_string (String morse_string) {
    unsigned int length = morse_string.length();

    for (unsigned int i = 0; i < length; i++) {
        Serial.print(morse_string[i]);
        if (morse_string[i] == '.') {
            digitalWrite(LEDPIN, HIGH);
            tone(BUZZERPIN, FREQUENCY);
            delay(UNIT); // Dot = 1 unit
        } else if (morse_string[i] == '-') {
            digitalWrite(LEDPIN, HIGH);
            tone(BUZZERPIN, FREQUENCY);
            delay(3 * UNIT); // Dash = 3 units
        }
        digitalWrite(LEDPIN, LOW);
        noTone(BUZZERPIN);
        delay(UNIT);
    }
    Serial.println("");
}

void decode_message (String message) {
    unsigned int length = message.length();

    for (unsigned int x = 0; x < length; x++) {
        if (message[x] == ' ') {
            Serial.println("*** NEXT WORD ***");
            delay(7 * UNIT); // Word gap
        }
        for(const auto & i : MorseDictionnary)
        {
            if(toUpperCase(message[x]) == i[0][0]){
                String morseStringToBlink = i[1];
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
    pinMode(BUZZERPIN, OUTPUT);
    pinMode(LEDPIN, OUTPUT);

    tone(BUZZERPIN, 250);
    digitalWrite(LEDPIN, HIGH);
    delay(150); // Play for 150ms
    tone(BUZZERPIN, 450);
    delay(150); // Play for 150ms
    tone(BUZZERPIN, 650);
    delay(500);
    noTone(BUZZERPIN);
    digitalWrite(LEDPIN, LOW);

    delay(500);

    Serial.println("\n\n\n");

}

void loop() {

    decode_message(message_to_translate);
    Serial.println("\n\n");
    delay(2500);

}