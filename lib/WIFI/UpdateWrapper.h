#pragma once

class UpdateWrapper {
public:
    void setSTMUpdate(bool stmMode) {
        _stmMode = stmMode;
    }

#if PLATFORM_ESP8266
    bool begin(size_t size) {
#else
    bool begin() {
#endif
      _running = true;
#if PLATFORM_ESP8266
        return Update.begin(size, U_FLASH);
#else
        return Update.begin();
#endif
    }

    size_t write(uint8_t *data, size_t len) {
        return Update.write(data, len);
    }

    bool end(bool evenIfRemaining = false) {
        _running = false;
        return Update.end(evenIfRemaining);
    }

    void printError(Print &out) {
        return Update.printError(out);
    }

    bool hasError() {
        return Update.hasError();
    }

    void runAsync(bool async) {
    #ifdef PLATFORM_ESP8266
        if (!_stmMode) Update.runAsync(async);
    #endif
    }

    bool isRunning() {
        return _running;
    }

#ifdef PLATFORM_ESP32
    void abort() {
        if (!_stmMode) Update.abort();
    }
#endif

private:
    bool _stmMode = false;
    bool _running = false;
};
