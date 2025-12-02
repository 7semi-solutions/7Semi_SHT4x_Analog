#include "7Semi_SHT4x_analog.h"
#include <math.h>

/**
 * Constructor implementation
 */
SHT4x_analog_7Semi::SHT4x_analog_7Semi(
    uint8_t pinRH,
    uint8_t pinT,
    uint16_t adcMax,
    SHT4x_analog_type_7Semi type
)
: _pinRH(pinRH),
  _pinT(pinT),
  _adcMax(adcMax),
  _type(type)
{
}

/**
 * Prepare pins for analog read
 */
void SHT4x_analog_7Semi::begin() {
    pinMode(_pinRH, INPUT);
    if (_pinT != 0xFF) {
        pinMode(_pinT, INPUT);
    }
}

/**
 * Read raw humidity ADC value
 */
uint16_t SHT4x_analog_7Semi::readRawRH() {
    return analogRead(_pinRH);
}

/**
 * Read raw temperature ADC value
 */
uint16_t SHT4x_analog_7Semi::readRawT() {
    if (_pinT == 0xFF) {
        return 0;
    }
    return analogRead(_pinT);
}

/**
 * Read humidity as %RH
 */
float SHT4x_analog_7Semi::readHumidity() {
    float ratio = _ratioFromAdc(readRawRH());
    float rh = _humidityFromRatio(ratio);

    if (rh < 0.0f) rh = 0.0f;
    if (rh > 100.0f) rh = 100.0f;

    return rh;
}

/**
 * Read temperature in °C
 */
float SHT4x_analog_7Semi::readTemperatureC() {
    if (_pinT == 0xFF) return NAN;
    float ratio = _ratioFromAdc(readRawT());
    return _temperatureCFromRatio(ratio);
}

/**
 * Read temperature in °F
 */
float SHT4x_analog_7Semi::readTemperatureF() {
    float tC = readTemperatureC();
    if (isnan(tC)) return NAN;
    return (tC * 9.0f / 5.0f) + 32.0f;
}

/**
 * Set ADC maximum value
 */
void SHT4x_analog_7Semi::setAdcMax(uint16_t adcMax) {
    _adcMax = adcMax;
}

/**
 * Change SHT4x type
 */
void SHT4x_analog_7Semi::setType(SHT4x_analog_type_7Semi type) {
    _type = type;
}

/**
 * Convert ADC to Vout/VDD ratio
 */
float SHT4x_analog_7Semi::_ratioFromAdc(uint16_t value) const {
    if (_adcMax == 0) return 0.0f;
    return (float)value / (float)_adcMax;
}

/**
 * Convert Vout/VDD to %RH
 *
 * - Uses correct formula for each SHT4x analog variant
 */
float SHT4x_analog_7Semi::_humidityFromRatio(float ratio) const {
    switch (_type) {

        case SHT4X_HD1B:
            return -12.5f + 125.0f * ratio;

        case SHT4X_ID1B:
        case SHT4X_JD1B:
            return -(19.7f / 0.54f) + (100.0f / 0.54f) * ratio;

        case SHT4X_KD1B:
            return -(16.44f / 0.6489f) + (100.0f / 0.6489f) * ratio;

        case SHT4X_LD1B:
        {
            float slope = 100.0f / (0.737f - 0.197f);
            float offset = -slope * 0.197f;
            return offset + slope * ratio;
        }
    }

    return NAN;
}

/**
 * Convert Vout/VDD to °C
 *
 * - Uses correct formula or an approximation
 */
float SHT4x_analog_7Semi::_temperatureCFromRatio(float ratio) const {
    switch (_type) {

        case SHT4X_HD1B:
        case SHT4X_JD1B:
            return -66.875f + 218.75f * ratio;

        case SHT4X_ID1B:
            return 75.87f - 106.75f * ratio;

        case SHT4X_KD1B:
            return NAN;

        case SHT4X_LD1B:
            return -56.9f + 134.6f * ratio;
    }

    return NAN;
}
