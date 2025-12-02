#pragma once
#include <Arduino.h>

/**
 * Supported SHT4x analog output characteristics
 *
 * - SHT4X_HD1B : Standard linear RH + T (default)
 * - SHT4X_ID1B : Industrial RH + table-based T (approximate here)
 * - SHT4X_JD1B : Industrial RH + standard T
 * - SHT4X_KD1B : RH-only, T pin floating
 * - SHT4X_LD1B : Table-based RH + T (approximate here)
 */
enum SHT4x_analog_type_7Semi {
    SHT4X_HD1B,
    SHT4X_ID1B,
    SHT4X_JD1B,
    SHT4X_KD1B,
    SHT4X_LD1B
};

/**
 * SHT4x_analog_7Semi
 *
 * - Reads analog humidity and temperature outputs
 * - Converts them to %RH and °C using appropriate formula
 * - No I²C interface, pure analog signal conversion
 * - Includes support for all SHT40I-Analog output characteristics
 */
class SHT4x_analog_7Semi {
public:

    /**
     * Constructor
     *
     * - pinRH: Analog pin for humidity output
     * - pinT : Analog pin for temperature output (0xFF for RH-only types)
     * - adcMax: Maximum ADC count (1023, 4095, etc.)
     * - type: Output characteristic variant
     */
    SHT4x_analog_7Semi(
        uint8_t pinRH,
        uint8_t pinT,
        uint16_t adcMax = 1023,
        SHT4x_analog_type_7Semi type = SHT4X_HD1B
    );

    /**
     * Prepare analog pins
     */
    void begin();

    /**
     * Read raw ADC counts from humidity pin
     */
    uint16_t readRawRH();

    /**
     * Read raw ADC counts from temperature pin
     */
    uint16_t readRawT();

    /**
     * Convert RH ADC to %RH
     *
     * - Auto-selects correct math based on SHT4x variant
     */
    float readHumidity();

    /**
     * Convert T ADC to °C
     *
     * - Returns NAN if T pin is unavailable (e.g., KD1B)
     */
    float readTemperatureC();

    /**
     * Convert T ADC to °F
     */
    float readTemperatureF();

    /**
     * Update ADC resolution
     */
    void setAdcMax(uint16_t adcMax);

    /**
     * Change SHT4x type (HD1B, JD1B, etc.)
     *
     * - Useful for boards that support multiple build variants
     */
    void setType(SHT4x_analog_type_7Semi type);

private:
    uint8_t _pinRH;
    uint8_t _pinT;
    uint16_t _adcMax;
    SHT4x_analog_type_7Semi _type;

    /**
     * Convert raw ADC value to normalized voltage ratio
     *
     * - ratio = Vout / VDD
     */
    float _ratioFromAdc(uint16_t value) const;

    /**
     * Convert normalized humidity ratio to %RH
     */
    float _humidityFromRatio(float ratio) const;

    /**
     * Convert normalized temperature ratio to °C
     */
    float _temperatureCFromRatio(float ratio) const;
};
