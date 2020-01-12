#include "Ala.h"
#include "AlaLedRgb.h"
#include "WiFiUdp.h"
#include "ESP8266WiFi.h"

//Gamma-corrected (2.8) values
const PROGMEM short int AlaLedRgb::gammat[1024] = {
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   
      0,    0,    0,    0,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,   
      1,    1,    1,    1,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    3,    3,    3,    3,    3,    3,    3,    3,   
      3,    3,    3,    3,    3,    3,    3,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    5,    5,    5,    5,    5,    5,    5,    5,    5,    5,    5,    6,   
      6,    6,    6,    6,    6,    6,    6,    6,    7,    7,    7,    7,    7,    7,    7,    7,    7,    8,    8,    8,    8,    8,    8,    8,    8,    9,    9,    9,    9,    9,    9,    9, 
      9,   10,   10,   10,   10,   10,   10,   10,   11,   11,   11,   11,   11,   11,   12,   12,   12,   12,   12,   12,   12,   13,   13,   13,   13,   13,   13,   14,   14,   14,   14,   14,  
     15,   15,   15,   15,   15,   15,   16,   16,   16,   16,   16,   17,   17,   17,   17,   17,   18,   18,   18,   18,   18,   19,   19,   19,   19,   20,   20,   20,   20,   20,   21,   21,  
     21,   21,   22,   22,   22,   22,   23,   23,   23,   23,   24,   24,   24,   24,   25,   25,   25,   25,   26,   26,   26,   26,   27,   27,   27,   27,   28,   28,   28,   29,   29,   29,  
     29,   30,   30,   30,   31,   31,   31,   31,   32,   32,   32,   33,   33,   33,   34,   34,   34,   35,   35,   35,   35,   36,   36,   36,   37,   37,   37,   38,   38,   38,   39,   39,  
     40,   40,   40,   41,   41,   41,   42,   42,   42,   43,   43,   43,   44,   44,   45,   45,   45,   46,   46,   46,   47,   47,   48,   48,   48,   49,   49,   50,   50,   50,   51,   51,  
     52,   52,   52,   53,   53,   54,   54,   55,   55,   55,   56,   56,   57,   57,   58,   58,   58,   59,   59,   60,   60,   61,   61,   62,   62,   63,   63,   63,   64,   64,   65,   65,  
     66,   66,   67,   67,   68,   68,   69,   69,   70,   70,   71,   71,   72,   72,   73,   73,   74,   74,   75,   75,   76,   76,   77,   77,   78,   79,   79,   80,   80,   81,   81,   82, 
     82,   83,   83,   84,   85,   85,   86,   86,   87,   87,   88,   89,   89,   90,   90,   91,   92,   92,   93,   93,   94,   95,   95,   96,   96,   97,   98,   98,   99,   99,  100,  101, 
    101,  102,  103,  103,  104,  105,  105,  106,  106,  107,  108,  108,  109,  110,  110,  111,  112,  112,  113,  114,  115,  115,  116,  117,  117,  118,  119,  119,  120,  121,  122,  122, 
    123,  124,  124,  125,  126,  127,  127,  128,  129,  130,  130,  131,  132,  132,  133,  134,  135,  136,  136,  137,  138,  139,  139,  140,  141,  142,  143,  143,  144,  145,  146,  146, 
    147,  148,  149,  150,  151,  151,  152,  153,  154,  155,  155,  156,  157,  158,  159,  160,  161,  161,  162,  163,  164,  165,  166,  167,  167,  168,  169,  170,  171,  172,  173,  174, 
    175,  175,  176,  177,  178,  179,  180,  181,  182,  183,  184,  185,  186,  186,  187,  188,  189,  190,  191,  192,  193,  194,  195,  196,  197,  198,  199,  200,  201,  202,  203,  204, 
    205,  206,  207,  208,  209,  210,  211,  212,  213,  214,  215,  216,  217,  218,  219,  220,  221,  222,  223,  224,  225,  226,  228,  229,  230,  231,  232,  233,  234,  235,  236,  237, 
    238,  239,  241,  242,  243,  244,  245,  246,  247,  248,  249,  251,  252,  253,  254,  255,  256,  257,  259,  260,  261,  262,  263,  264,  266,  267,  268,  269,  270,  272,  273,  274, 
    275,  276,  278,  279,  280,  281,  282,  284,  285,  286,  287,  289,  290,  291,  292,  294,  295,  296,  297,  299,  300,  301,  302,  304,  305,  306,  308,  309,  310,  311,  313,  314, 
    315,  317,  318,  319,  321,  322,  323,  325,  326,  327,  329,  330,  331,  333,  334,  336,  337,  338,  340,  341,  342,  344,  345,  347,  348,  349,  351,  352,  354,  355,  356,  358, 
    359,  361,  362,  364,  365,  366,  368,  369,  371,  372,  374,  375,  377,  378,  380,  381,  383,  384,  386,  387,  389,  390,  392,  393,  395,  396,  398,  399,  401,  402,  404,  405, 
    407,  408,  410,  412,  413,  415,  416,  418,  419,  421,  423,  424,  426,  427,  429,  431,  432,  434,  435,  437,  439,  440,  442,  444,  445,  447,  448,  450,  452,  453,  455,  457, 
    458,  460,  462,  463,  465,  467,  468,  470,  472,  474,  475,  477,  479,  480,  482,  484,  486,  487,  489,  491,  493,  494,  496,  498,  500,  501,  503,  505,  507,  509,  510,  512, 
    514,  516,  518,  519,  521,  523,  525,  527,  528,  530,  532,  534,  536,  538,  539,  541,  543,  545,  547,  549,  551,  553,  554,  556,  558,  560,  562,  564,  566,  568,  570,  572, 
    574,  575,  577,  579,  581,  583,  585,  587,  589,  591,  593,  595,  597,  599,  601,  603,  605,  607,  609,  611,  613,  615,  617,  619,  621,  623,  625,  627,  629,  631,  633,  635, 
    637,  640,  642,  644,  646,  648,  650,  652,  654,  656,  658,  660,  663,  665,  667,  669,  671,  673,  675,  678,  680,  682,  684,  686,  688,  690,  693,  695,  697,  699,  701,  704, 
    706,  708,  710,  712,  715,  717,  719,  721,  724,  726,  728,  730,  733,  735,  737,  739,  742,  744,  746,  749,  751,  753,  755,  758,  760,  762,  765,  767,  769,  772,  774,  776, 
    779,  781,  783,  786,  788,  790,  793,  795,  798,  800,  802,  805,  807,  810,  812,  814,  817,  819,  822,  824,  827,  829,  831,  834,  836,  839,  841,  844,  846,  849,  851,  854, 
    856,  859,  861,  864,  866,  869,  871,  874,  876,  879,  881,  884,  887,  889,  892,  894,  897,  899,  902,  905,  907,  910,  912,  915,  918,  920,  923,  925,  928,  931,  933,  936, 
    939,  941,  944,  947,  949,  952,  955,  957,  960,  963,  965,  968,  971,  973,  976,  979,  982,  984,  987,  990,  992,  995,  998, 1001, 1004, 1006, 1009, 1012, 1015, 1017, 1020, 1023
};

//taken from AlaLedRgb.cpp to check if given animId-Parameter (http) is valid
const PROGMEM short int AlaLedRgb::validAnimIds[35] = {
    101, 102, 103, 104, 105, 106, 107, 151,
    201, 202, 203, 211, 212, 213, 221, 222,
    241, 242, 251, 252, 301, 302, 303, 304,
    305, 306, 351, 352, 353, 354, 501, 502, 
    503, 0, 1
};

AlaLedRgb::AlaLedRgb()
{
    // set default values
    maxOut = 1.0F;
    newMaxOut = 1.0F;
    speed = 2000;
    animSeqLen = 0;
    lastRefreshTime = 0;
    refreshMillis = 1000/50;
    pxPos = NULL;
    pxSpeed = NULL;
    oneAnimationCycled = false;
    this->palette.numColors = 1;
    // TODO is this a memory leak?
	this->palette.colors = (AlaColor*)malloc(3);
    this->palette.colors[0] = 0;
}

//returns the gamma-corrected pwm value. i/o-range = 0-1023
short int AlaLedRgb::gamma(short int va){
    return pgm_read_word(gammat + va);
}

short int AlaLedRgb::animId(short int va){
    return pgm_read_word(validAnimIds + va);
}

void AlaLedRgb::initPWM(byte pinRed, byte pinGreen, byte pinBlue)
{
    byte *pins_ = (byte *)malloc(3);
    pins_[0] = pinRed;
    pins_[1] = pinGreen;
    pins_[2] = pinBlue;

    initPWM(1, pins_);
}

void AlaLedRgb::initPWM(int numLeds, byte *pins)
{
    this->driver = ALA_PWM;
    this->numLeds = numLeds;
    this->pins = pins;

    for (int x=0; x<3*numLeds ; x++)
    {
        pinMode(pins[x], OUTPUT);
    }

    // allocate and clear leds array
    leds = (AlaColor *)malloc(3*numLeds);
    memset(leds, 0, 3*numLeds);
}

void AlaLedRgb::setBrightness(int maxOut, int speed)
{
    if (maxOut > 100)
        this->newMaxOut = 1;
    else if (maxOut < 0)
        this->newMaxOut = 0;
    else
        this->newMaxOut = maxOut / 100.0F;
    this->oldMaxOut = this->maxOut;
    this->brightSpeed = speed;
    brightStartTime = millis();
}

void AlaLedRgb::calculateBrightness(bool andApply){
    if (maxOut != newMaxOut){
        float t = _min(((millis()-brightStartTime))*1.0/brightSpeed, 1.0);
        
        this->maxOut = (newMaxOut - oldMaxOut) * t + oldMaxOut;

        if (andApply)
            applyLEDChanges();
    }
}

int AlaLedRgb::getBrightness(){
    return this->newMaxOut * 100;
}

void AlaLedRgb::setRefreshRate(int refreshRate)
{
    this->refreshMillis = 1000/refreshRate;
}

int AlaLedRgb::getCurrentRefreshRate()
{
    return refreshRate;
}


void AlaLedRgb::setAnimation(int animation, long speed, AlaColor color, bool isSeq, bool shouldPlayOnce)
{
    // is there any change?
    if (this->animation == animation && this->speed == speed && this->palette.numColors == 1 && this->palette.colors[0] == color && shouldPlayOnce == false)
        return;

    // delete any previously allocated array
    if (pxPos!=NULL)
    { delete[] pxPos; pxPos=NULL; }
    if (pxSpeed!=NULL)
    { delete[] pxSpeed; pxSpeed=NULL; }

    this->animation = animation;
    this->speed = speed;
    playOnce = shouldPlayOnce;
    this->oneAnimationCycled = false;

    this->palette.numColors = 1;
    // TODO is this a memory leak?
	this->palette.colors = (AlaColor*)malloc(3);
    this->palette.colors[0] = color;

	if (!isSeq)
		animSeqLen=0;
    setAnimationFunc(animation);
    animStartTime = millis();
}


void AlaLedRgb::setAnimation(int animation, long speed, AlaPalette palette, bool isSeq, bool shouldPlayOnce)
{
    // is there any change?
    if (this->animation == animation && this->speed == speed && this->palette == palette && shouldPlayOnce == false)
        return;

    // delete any previously allocated array
    if (pxPos!=NULL)
    { delete[] pxPos; pxPos=NULL; }
    if (pxSpeed!=NULL)
    { delete[] pxSpeed; pxSpeed=NULL; }

    this->animation = animation;
    this->speed = speed;
    this->palette = palette;
    playOnce = shouldPlayOnce;
    this->oneAnimationCycled = false;

	if (!isSeq)
		animSeqLen=0;
    setAnimationFunc(animation);
    animStartTime = millis();
}


void AlaLedRgb::setAnimation(AlaSeq animSeq[])
{
    this->animSeq = animSeq;

    // initialize animSeqDuration and animSeqLen variables
    animSeqDuration = 0;
    for(animSeqLen=0; animSeq[animSeqLen].animation!=ALA_ENDSEQ; animSeqLen++)
    {
        animSeqDuration = animSeqDuration + animSeq[animSeqLen].duration;
    }
    animSeqStartTime = millis();
    setAnimation(animSeq[0].animation, animSeq[0].speed, animSeq[0].palette, true);
}

void AlaLedRgb::setSpeed(long speed)
{
    this->speed = speed;
	animStartTime = millis();
}

void AlaLedRgb::setColor(AlaColor color)
{
    this->palette.colors[0] = color;
}

void AlaLedRgb::setColor(AlaPalette color)
{
    this->palette = color;
}

int AlaLedRgb::getAnimation()
{
    return animation;
}


bool AlaLedRgb::runAnimation()
{
    // skip the refresh if not enough time has passed since last update
    unsigned long cTime = millis();
    if (cTime < lastRefreshTime + refreshMillis)
        return false;

    // calculate real refresh rate
    refreshRate = 1000/(cTime - lastRefreshTime);

    lastRefreshTime = cTime;

    if (animation == ALA_STOPSEQ){
        calculateBrightness(true);
        return true;
    }
    else
        calculateBrightness(false);

    // if it's a sequence we have to calculate the current animation
    if (animSeqLen != 0)
    {
        long c = 0;
        long t = (cTime-animSeqStartTime) % animSeqDuration;
        for(int i=0; i<animSeqLen; i++)
        {
            if (t>=c && t<(c+animSeq[i].duration))
            {
                setAnimation(animSeq[i].animation, animSeq[i].speed, animSeq[i].palette, true);
                break;
            }
            c = c + animSeq[i].duration;
        }
    }


    // run the animantion calculation
    if (animFunc != NULL)
        (this->*animFunc)();

    // update leds
    if(driver==ALA_PWM)
        applyLEDChanges();

    oneAnimationCycled = true;
    if (playedOnce){
        animation = ALA_STOPSEQ;
        playedOnce = false;
    }
}

void AlaLedRgb::applyLEDChanges(){
    for(int i=0; i<numLeds; i++){
        int j = 3*i;
        // use an 8 bit shift to divide by 256
        calcedColors[0] = gamma(leds[i].r/255.0F*1023.0F*maxOut);
        calcedColors[1] = gamma(leds[i].g/255.0F*1023.0F*maxOut);
        calcedColors[2] = gamma(leds[i].b/255.0F*1023.0F*maxOut);
        if (i == 0){
            colorsForUdp[0] = calcedColors[0] & 0x00FF;
            colorsForUdp[1] = calcedColors[0] >> 8;
            colorsForUdp[2] = calcedColors[1] & 0x00FF;
            colorsForUdp[3] = calcedColors[1] >> 8;
            colorsForUdp[4] = calcedColors[2] & 0x00FF;
            colorsForUdp[5] = calcedColors[2] >> 8;
            udp.beginPacket(ipSlaveUdp, 91); //port hardcoded in slave
            udp.write(colorsForUdp, 6);
            udp.endPacket();
        }
        analogWrite(pins[j],   calcedColors[0]);
        analogWrite(pins[j+2], calcedColors[2]);
        analogWrite(pins[j+1], calcedColors[1]);
    }
}


///////////////////////////////////////////////////////////////////////////////

void AlaLedRgb::setAnimationFunc(int animation)
{

    switch(animation)
    {
        case ALA_ON:                    animFunc = &AlaLedRgb::on;                    break;
        case ALA_OFF:                   animFunc = &AlaLedRgb::off;                   break;
        case ALA_BLINK:                 animFunc = &AlaLedRgb::blink;                 break;
        case ALA_BLINKALT:              animFunc = &AlaLedRgb::blinkAlt;              break;
        case ALA_SPARKLE:               animFunc = &AlaLedRgb::sparkle;               break;
        case ALA_SPARKLE2:              animFunc = &AlaLedRgb::sparkle2;              break;
        case ALA_STROBO:                animFunc = &AlaLedRgb::strobo;                break;
        case ALA_CYCLECOLORS:           animFunc = &AlaLedRgb::cycleColors;           break;

        case ALA_PIXELSHIFTRIGHT:       animFunc = &AlaLedRgb::pixelShiftRight;       break;
        case ALA_PIXELSHIFTLEFT:        animFunc = &AlaLedRgb::pixelShiftLeft;        break;
        case ALA_PIXELBOUNCE:           animFunc = &AlaLedRgb::pixelBounce;           break;
        case ALA_PIXELSMOOTHSHIFTRIGHT: animFunc = &AlaLedRgb::pixelSmoothShiftRight; break;
        case ALA_PIXELSMOOTHSHIFTLEFT:  animFunc = &AlaLedRgb::pixelSmoothShiftLeft;  break;
        case ALA_PIXELSMOOTHBOUNCE:     animFunc = &AlaLedRgb::pixelSmoothBounce;     break;
        case ALA_COMET:                 animFunc = &AlaLedRgb::comet;                 break;
        case ALA_COMETCOL:              animFunc = &AlaLedRgb::cometCol;              break;
        case ALA_MOVINGBARS:            animFunc = &AlaLedRgb::movingBars;            break;
        case ALA_MOVINGGRADIENT:        animFunc = &AlaLedRgb::movingGradient;        break;
        case ALA_LARSONSCANNER:         animFunc = &AlaLedRgb::larsonScanner;         break;
        case ALA_LARSONSCANNER2:        animFunc = &AlaLedRgb::larsonScanner2;        break;

        case ALA_FADEIN:                animFunc = &AlaLedRgb::fadeIn;                break;
        case ALA_FADEOUT:               animFunc = &AlaLedRgb::fadeOut;               break;
        case ALA_FADEINOUT:             animFunc = &AlaLedRgb::fadeInOut;             break;
        case ALA_GLOW:                  animFunc = &AlaLedRgb::glow;                  break;
        case ALA_PLASMA:                animFunc = &AlaLedRgb::plasma;                break;
        case ALA_FADETO:                animFunc = &AlaLedRgb::fadeTo;                break;
        case ALA_PIXELSFADECOLORS:      animFunc = &AlaLedRgb::pixelsFadeColors;      break;
        case ALA_FADECOLORS:            animFunc = &AlaLedRgb::fadeColors;            break;
        case ALA_FADECOLORSLOOP:        animFunc = &AlaLedRgb::fadeColorsLoop;        break;

        case ALA_FIRE:                  animFunc = &AlaLedRgb::fire;                  break;
        case ALA_BOUNCINGBALLS:         animFunc = &AlaLedRgb::bouncingBalls;         break;
        case ALA_BUBBLES:               animFunc = &AlaLedRgb::bubbles;               break;

        default:                        animFunc = &AlaLedRgb::off;
    }

}


void AlaLedRgb::on()
{
    for(int i=0; i<numLeds; i++)
    {
        leds[i] = palette.colors[0];
    }
}

void AlaLedRgb::off()
{
    for(int i=0; i<numLeds; i++)
    {
        leds[i] = 0x000000;
    }
}


void AlaLedRgb::blink()
{
    int t = getStep(animStartTime, speed, 2);
    int k = (t+1)%2;
    for(int x=0; x<numLeds; x++)
    {
        leds[x] = palette.colors[0].scale(k);
    }
}

void AlaLedRgb::blinkAlt()
{
    int t = getStep(animStartTime, speed, 2);

    for(int x=0; x<numLeds; x++)
    {
        int k = (t+x)%2;
        leds[x] = palette.colors[0].scale(k);
    }
}

void AlaLedRgb::sparkle()
{
    int p = speed/100;
    for(int x=0; x<numLeds; x++)
    {
        leds[x] = palette.colors[random(palette.numColors)].scale(random(p)==0);
    }
}

void AlaLedRgb::sparkle2()
{
    int p = speed/10;
    for(int x=0; x<numLeds; x++)
    {
        if(random(p)==0)
            leds[x] = palette.colors[random(palette.numColors)];
        else
            leds[x] = leds[x].scale(0.88);
    }
}


void AlaLedRgb::strobo()
{
    int t = getStep(animStartTime, speed, ALA_STROBODC);

    AlaColor c = palette.colors[0].scale(t==0);
    for(int x=0; x<numLeds; x++)
    {
        leds[x] = c;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
// Shifting effects
////////////////////////////////////////////////////////////////////////////////////////////

void AlaLedRgb::pixelShiftRight()
{
    int t = getStep(animStartTime, speed, numLeds);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);

    for(int x=0; x<numLeds; x++)
    {
        int k = (x==t ? 1:0);
        leds[x] = c.scale(k);
    }
}

void AlaLedRgb::pixelShiftLeft()
{
    int t = getStep(animStartTime, speed, numLeds);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);

    for(int x=0; x<numLeds; x++)
    {
        int k = ((x==(numLeds-1-t) ? 1:0));
        leds[x] = c.scale(k);
    }
}

// Bounce back and forth
void AlaLedRgb::pixelBounce()
{
    int t = getStep(animStartTime, speed, 2*numLeds-2);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);

    for(int x=0; x<numLeds; x++)
    {
        int k = x==(-abs(t-numLeds+1)+numLeds-1) ? 1:0;
        leds[x] = c.scale(k);
    }
}

void AlaLedRgb::pixelSmoothShiftRight()
{
    float t = getStepFloat(animStartTime, speed, numLeds+1);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);

    for(int x=0; x<numLeds; x++)
    {
        float k = _max(0, (-abs(t-1-x)+1));
        leds[x] = c.scale(k);
    }
}

void AlaLedRgb::pixelSmoothShiftLeft()
{
    float t = getStepFloat(animStartTime, speed, numLeds+1);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);

    for(int x=0; x<numLeds; x++)
    {
        float k = _max(0, (-abs(numLeds-t-x)+1));
        leds[x] = c.scale(k);
    }
}

void AlaLedRgb::comet()
{
    float l = numLeds/2;  // length of the tail
    float t = getStepFloat(animStartTime, speed, 2*numLeds-l);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);

    for(int x=0; x<numLeds; x++)
    {
        float k = constrain( (((x-t)/l+1.2f))*(((x-t)<0)? 1:0), 0, 1);
        leds[x] = c.scale(k);
    }
}

void AlaLedRgb::cometCol()
{
    float l = numLeds/2;  // length of the tail
    float t = getStepFloat(animStartTime, speed, 2*numLeds-l);

    AlaColor c;
    for(int x=0; x<numLeds; x++)
    {
        float tx = mapfloat(_max(t-x, 0), 0, numLeds/1.7, 0, palette.numColors-1);
        c = palette.getPalColor(tx);
        float k = constrain( (((x-t)/l+1.2f))*(((x-t)<0)? 1:0), 0, 1);
        leds[x] = c.scale(k);
    }
}

void AlaLedRgb::pixelSmoothBounce()
{
    // see larsonScanner
    float t = getStepFloat(animStartTime, speed, 2*numLeds-2);
    AlaColor c = palette.getPalColor(getStepFloat(animStartTime, speed, palette.numColors));

    for(int x=0; x<numLeds; x++)
    {
        float k = constrain((-abs(abs(t-numLeds+1)-x)+1), 0, 1);
        leds[x] = c.scale(k);
    }
}


void AlaLedRgb::larsonScanner()
{
    float l = numLeds/4;
    float t = getStepFloat(animStartTime, speed, 2*numLeds-2);
    AlaColor c = palette.getPalColor(getStepFloat(animStartTime, speed, palette.numColors));

    for(int x=0; x<numLeds; x++)
    {
        float k = constrain((-abs(abs(t-numLeds+1)-x)+l), 0, 1);
        leds[x] = c.scale(k);
    }
}

void AlaLedRgb::larsonScanner2()
{
    float l = numLeds/4;  // 2>7, 3-11, 4-14
    float t = getStepFloat(animStartTime, speed, 2*numLeds+(l*4-1));
    AlaColor c = palette.getPalColor(getStepFloat(animStartTime, speed, palette.numColors));

    for(int x=0; x<numLeds; x++)
    {

        float k = constrain((-abs(abs(t-numLeds-2*l)-x-l)+l), 0, 1);
        leds[x] = c.scale(k);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////
// Fading effects
////////////////////////////////////////////////////////////////////////////////////////////

void AlaLedRgb::fadeIn()
{
    float s = getStepFloat(animStartTime, speed, 1);
    AlaColor c = palette.colors[0].scale(s);

    for(int x=0; x<numLeds; x++)
    {
        leds[x] = c;
    }
}


void AlaLedRgb::fadeOut()
{
    float s = getStepFloat(animStartTime, speed, 1);
    AlaColor c = palette.colors[0].scale(1-s);

    for(int x=0; x<numLeds; x++)
    {
        leds[x] = c;
    }
}


void AlaLedRgb::fadeInOut()
{
    float s = getStepFloat(animStartTime, speed, 2) - 1;
    AlaColor c = palette.colors[0].scale(abs(1-abs(s)));

    for(int x=0; x<numLeds; x++)
    {
        leds[x] = c;
    }
}

void AlaLedRgb::glow()
{
    float s = getStepFloat(animStartTime, speed, TWO_PI);
    float k = (-cos(s)+1)/2;

    for(int x=0; x<numLeds; x++)
    {
        leds[x] = palette.colors[0].scale(k);
    }
}

void AlaLedRgb::plasma()
{
    float t = getStepFloat(animStartTime, speed, numLeds);

    for(int x=0; x<numLeds; x++)
    {
        AlaColor c1 = palette.getPalColor((float)((x+t)*palette.numColors)/numLeds);
        AlaColor c2 = palette.getPalColor((float)((2*x-t+numLeds)*palette.numColors)/numLeds);
        leds[x] = c1.interpolate(c2, 0.5);
    }
}

void AlaLedRgb::fadeTo()
{
    if (!oneAnimationCycled)
        addCurrentColorToFirstPositionAtPalette();

    float t = getStepFloat(animStartTime, speed, 1);
    AlaColor c = palette.getPalColor(t);
    for(int x=0; x<numLeds; x++)
    {
        leds[x] = c;
    }
}


void AlaLedRgb::fadeColors()
{
    float t = getStepFloat(animStartTime, speed, palette.numColors-1);
    AlaColor c = palette.getPalColor(t);
    for(int x=0; x<numLeds; x++)
    {
        leds[x] = c;
    }

}

void AlaLedRgb::pixelsFadeColors()
{
    float t = getStepFloat(animStartTime, speed, palette.numColors);

    for(int x=0; x<numLeds; x++)
    {
        AlaColor c = palette.getPalColor(t+7*x);
        leds[x] = c;
    }
}

void AlaLedRgb::fadeColorsLoop()
{
    float t = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(t);
    for(int x=0; x<numLeds; x++)
    {
        leds[x] = c;
    }
}


void AlaLedRgb::cycleColors()
{
    int t = getStep(animStartTime, speed, palette.numColors);

    for(int x=0; x<numLeds; x++)
    {
        leds[x] = palette.colors[t];
    }
}


void AlaLedRgb::movingBars()
{
    int t = getStep(animStartTime, speed, numLeds);

    for(int x=0; x<numLeds; x++)
    {
        leds[x] = palette.colors[(((t+x)*palette.numColors)/numLeds)%palette.numColors];
    }
}

void AlaLedRgb::movingGradient()
{
    float t = getStepFloat(animStartTime, speed, numLeds);

    for(int x=0; x<numLeds; x++)
    {
        leds[x] = palette.getPalColor((float)((x+t)*palette.numColors)/numLeds);
    }
}


/*******************************************************************************
* FIRE
* Porting of the famous Fire2012 effect by Mark Kriegsman.
* Actually works at 50 Hz frame rate with up to 50 pixels.
*******************************************************************************/
void AlaLedRgb::fire()
{
    // COOLING: How much does the air cool as it rises?
    // Less cooling = taller flames.  More cooling = shorter flames.
    // Default 550
    #define COOLING  600

    // SPARKING: What chance (out of 255) is there that a new spark will be lit?
    // Higher chance = more roaring fire.  Lower chance = more flickery fire.
    // Default 120, suggested range 50-200.
    #define SPARKING 120

    // Array of temperature readings at each simulation cell
    static byte *heat = NULL;

    // Initialize array if necessary
    if (heat==NULL)
        heat = new byte[numLeds];

    // Step 1.  Cool down every cell a little
    int rMax = (COOLING / numLeds) + 2;
    for(int i=0; i<numLeds; i++)
    {
        heat[i] = _max(((int)heat[i]) - random(0, rMax), 0);
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for(int k=numLeds-1; k>=3; k--)
    {
        heat[k] = ((int)heat[k - 1] + (int)heat[k - 2] + (int)heat[k - 3] ) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if(random(255) < SPARKING)
    {
        int y = random(7);
        heat[y] = _min(heat[y] + random(160, 255), 255);
    }

    // Step 4.  Map from heat cells to LED colors
    for(int j=0; j<numLeds; j++)
    {
        float colorindex = (float)(heat[j] * (palette.numColors-1) ) / 256;
        leds[j] = palette.getPalColor(colorindex);
    }
}

void AlaLedRgb::bouncingBalls()
{
    static long lastRefresh;

    if (pxPos==NULL)
    {
        // allocate new arrays
        pxPos = new float[palette.numColors];
        pxSpeed = new float[palette.numColors];

        for (int i=0; i<palette.numColors; i++)
        {
            pxPos[i] = ((float)random(255))/255;
            pxSpeed[i] = 0;
        }
        lastRefresh = millis();

        return; // skip the first cycle
    }

    float speedReduction = (float)(millis() - lastRefresh)/5000;
    lastRefresh = millis();

    for (int i=0; i<palette.numColors; i++)
    {
        if(pxSpeed[i]>-0.04 and pxSpeed[i]<0 and pxPos[i]>0 and pxPos[i]<0.1)
            pxSpeed[i]=(0.09)-((float)random(10)/1000);

        pxPos[i] = pxPos[i] + pxSpeed[i];
        if(pxPos[i]>=1)
        {
            pxPos[i]=1;
        }
        if(pxPos[i]<0)
        {
            pxPos[i]=-pxPos[i];
            pxSpeed[i]=-0.91*pxSpeed[i];
        }

        pxSpeed[i] = pxSpeed[i]-speedReduction;
    }

    for (int x=0; x<numLeds ; x++)
    {
        leds[x] = 0;
    }
    for (int i=0; i<palette.numColors; i++)
    {
        int p = mapfloat(pxPos[i], 0, 1, 0, numLeds-1);
        leds[p] = leds[p].sum(palette.colors[i]);
    }

}

void AlaLedRgb::bubbles()
{
    static long lastRefresh;

    if (pxPos==NULL)
    {
        // allocate new arrays
        pxPos = new float[palette.numColors];
        pxSpeed = new float[palette.numColors];

        for (int i=0; i<palette.numColors; i++)
        {
            pxPos[i] = ((float)random(255))/255;
            pxSpeed[i] = 0;
        }
        lastRefresh = millis();

        return; // skip the first cycle
    }

    float speedDelta = (float)(millis() - lastRefresh)/80000;
    lastRefresh = millis();

    for (int i=0; i<palette.numColors; i++)
    {
        //pos[i] = pos[i] + speed[i];
        if(pxPos[i]>=1)
        {
            pxPos[i]=0;
            pxSpeed[i]=0;
        }
        if(random(20)==0 and pxPos[i]==0)
        {
            pxPos[i]=0.0001;
            pxSpeed[i]=0.0001;
        }
        if(pxPos[i]>0)
        {
            pxPos[i] = pxPos[i] + pxSpeed[i];
            pxSpeed[i] = pxSpeed[i] + speedDelta;
        }
    }

    for (int x=0; x<numLeds ; x++)
    {
        leds[x] = 0;
    }
    for (int i=0; i<palette.numColors; i++)
    {
        if (pxPos[i]>0)
        {
            int p = mapfloat(pxPos[i], 0, 1, 0, numLeds-1);
            AlaColor c = palette.colors[i].scale(1-(float)random(10)/30); // add a little flickering
            leds[p] = c;
        }
    }

}

//copies the currently displayed color to the begin of the color palette
void AlaLedRgb::addCurrentColorToFirstPositionAtPalette(){
    palette.numColors = palette.numColors + 1;
    palette.colors = (AlaColor*) realloc(palette.colors, palette.numColors * sizeof(AlaColor));
    for (int i = palette.numColors-1; i > 0; i--){
        palette.colors[i] = palette.colors[i-1];
    }
    palette.colors[0] = *leds;
}

