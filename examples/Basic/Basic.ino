#include <7Semi_SHT4x_analog.h>

/**
 * Basic SHT4x-Analog example
 *
 * - Connect RH pin to A0
 * - Connect T pin  to A1 (or leave SHT4x type as RH-only for KD1B)
 * - Adjust ADC resolution and type according to your MCU and sensor variant
 */

// Adjust these pins for your board
static const uint8_t PIN_RH = A0;
static const uint8_t PIN_T  = A1;

/**
 * Choose the correct SHT4x analog variant
 *
 * - SHT4X_HD1B : Standard RH + T
 * - SHT4X_ID1B : Industrial RH + table-based T (approximate)
 * - SHT4X_JD1B : Industrial RH + standard T
 * - SHT4X_KD1B : RH-only, T pin floating
 * - SHT4X_LD1B : Table-based RH + T (approximate)
 */
SHT4x_analog_7Semi sht4x(
    PIN_RH,
    PIN_T,
    1023,            // 10-bit ADC for classic AVR
    SHT4X_HD1B       // Change to your actual variant
);

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ; // Wait for native USB boards
    }

    /**
     * Initialize sensor pins
     */
    sht4x.begin();

    /**
     * Optional: adjust ADC max if using a different MCU
     *
     * - Example for 12-bit ADC:
     *   sht4x.setAdcMax(4095);
     */
    // sht4x.setAdcMax(4095);

    Serial.println(F("7Semi SHT4x-Analog basic example"));
}

void loop() {
    /**
     * Read humidity and temperature
     */
    float rh = sht4x.readHumidity();
    float tC = sht4x.readTemperatureC();
    float tF = sht4x.readTemperatureF();

    Serial.print(F("RH: "));
    Serial.print(rh, 1);
    Serial.print(F(" %  "));

    Serial.print(F("T: "));
    if (isnan(tC)) {
        Serial.print(F("N/A (RH-only variant)"));
    } else {
        Serial.print(tC, 2);
        Serial.print(F(" °C  /  "));
        Serial.print(tF, 2);
        Serial.print(F(" °F"));
    }

    Serial.println();
    delay(1000);
}
