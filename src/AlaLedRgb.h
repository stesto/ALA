#ifndef AlaLedRgb_h
#define AlaLedRgb_h

#include "Ala.h"
#include "WiFiUdp.h"
#include "ESP8266WiFi.h"

/**
 *  AlaLedRgb can be used to drive a single or multiple RGB leds to perform animations.
 *  Available drivers are PWM pin, TLC5940, WS2811.
 */
class AlaLedRgb
{

public:

    AlaLedRgb();

    void initPWM(byte pinRed, byte pinGreen, byte pinBlue);
    void initPWM(int numLeds, byte *pins);

    /**
    * Sets the maximum brightness level.
    */
    void setBrightness(int maxOut, int speed);
    int getBrightness();

    /**
    * Sets the maximum refresh rate in Hz (default value is 50 Hz).
    * May be useful to reduce flickering in some cases.
    */
    void setRefreshRate(int refreshRate);

    int getCurrentRefreshRate();


    void setAnimation(int animation, long speed, AlaColor color, bool isSeq=false, bool shouldPlayOnce=false);
    void setAnimation(int animation, long speed, AlaPalette palette, bool isSeq=false, bool shouldPlayOnce=false);
    void setAnimation(AlaSeq animSeq[]);
    void setSpeed(long speed);
    void setColor(AlaColor color);
    void setColor(AlaPalette color);
    
    int getAnimation();

    bool runAnimation();
    void applyLEDChanges();

    static const short int gammat[1024];
    static const short int validAnimIds[35];
    
    AlaPalette palette;
    long speed;

    short int gamma(short int va);
    short int animId(short int va);

    //IP address of slave led controller
    IPAddress ipSlaveUdp;

private:

    void setAnimationFunc(int animation);
    void calculateBrightness(bool andApply);

    void on();
    void off();
    void blink();
    void blinkAlt();
    void sparkle();
    void sparkle2();
    void strobo();
    void cycleColors();

    void pixelShiftRight();
    void pixelShiftLeft();
    void pixelBounce();
    void pixelSmoothShiftRight();
    void pixelSmoothShiftLeft();
    void comet();
    void cometCol();
    void pixelSmoothBounce();
    void larsonScanner();
    void larsonScanner2();

    void fadeIn();
    void fadeOut();
    void fadeInOut();
    void glow();
    void plasma();
    void fadeTo();
    void fadeColors();
    void pixelsFadeColors();
    void fadeColorsLoop();

    void movingBars();
    void movingGradient();

    void fire();
    void bouncingBalls();
    void bubbles();

    void addCurrentColorToFirstPositionAtPalette();

    byte driver;    // type of led driver: ALA_PWM, ALA_TLC5940
    byte *pins;     // pins where the leds are attached to
    AlaColor *leds; // array to store leds brightness values
    int numLeds;    // number of leds

    short int calcedColors[3];
    byte colorsForUdp[6];
    WiFiUDP udp;

    int animation;
    AlaSeq *animSeq;
    int animSeqLen;
    long animSeqDuration;

    void (AlaLedRgb::*animFunc)();
    float oldMaxOut;
    float newMaxOut;
    float maxOut;
    int refreshMillis;
    int refreshRate;   // current refresh rate
    unsigned long animStartTime;
    unsigned long animSeqStartTime;
    unsigned long lastRefreshTime;
    
    unsigned long brightStartTime;
    long brightSpeed;

    bool oneAnimationCycled;

    float *pxPos;
    float *pxSpeed;

};


#endif