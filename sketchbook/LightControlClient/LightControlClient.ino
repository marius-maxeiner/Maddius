// Light Control Client i2c
#define DEVMODE true

#define CHANNELCOUNT 3

#define I2CADRESS 8

#define PotiMulti 0.2925
#define PotiTolerance 2

#include <Wire.h>

struct channel_def
{
    byte type;
    byte d_i;
    byte d_o;
    byte a_i;
    byte a_o;
    byte inputState;
    byte inputLastState;
    byte incomingValue;
    byte incomingLastValue;
    byte outgoingValue;
    byte outgoingLastValue;
};
typedef struct channel_def Channel;
/* TYPES
 * 1 : Push Button
 * 2 : Reverse Button
 */

Channel channel[CHANNELCOUNT] = {
    {2, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {3, 12, 2, 0, 0, 0, 0, 0, 0, 0, 0},
    {10, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}};

bool init1 = false;

void setup()
{
    Wire.begin(I2CADRESS);
    // register events
    Wire.onRequest(requestEvent);
    Wire.onReceive(receiveEvent);
    if (DEVMODE)
    {
        Serial.begin(38400); // start serial for output
        Serial.println("Start Slave");
    }
    for (int chanelIndex = 0; chanelIndex < CHANNELCOUNT; chanelIndex++)
    {
        if (channel[chanelIndex].d_i > 0)
        {
            pinMode(channel[chanelIndex].d_i, INPUT_PULLUP);
        }
        if (channel[chanelIndex].d_o > 0)
        {
            pinMode(channel[chanelIndex].d_o, OUTPUT);
        }
    }
}

void loop()
{
    bool onKeyUp;
    bool dState;
    int aState;
    byte tmp0;
    byte out;
    for (int chanelIndex = 0; chanelIndex < CHANNELCOUNT; chanelIndex++)
    {
        onKeyUp = false;
        switch (channel[chanelIndex].type)
        {
        case 1:
            dState = digitalRead(channel[chanelIndex].d_i);
            if (!dState)
            {
                channel[chanelIndex].inputState = 255;
            }
            else
            {
                channel[chanelIndex].inputState = 0;
            }
            out = channel[chanelIndex].inputState;
            if (channel[chanelIndex].d_o > 0)
            {
                if (channel[chanelIndex].incomingValue > 127)
                {
                    digitalWrite(channel[chanelIndex].d_o, HIGH);
                }
                else
                {
                    digitalWrite(channel[chanelIndex].d_o, LOW);
                }
            }
            break;
        case 2:
            onKeyUp = true;
        case 3:
            dState = digitalRead(channel[chanelIndex].d_i);
            if (!dState)
            {
                channel[chanelIndex].inputState = 255;
            }
            else
            {
                channel[chanelIndex].inputState = 0;
            }
            if (channel[chanelIndex].inputLastState != channel[chanelIndex].inputState)
            {
                out = channel[chanelIndex].outgoingValue;
                Serial.println((onKeyUp && channel[chanelIndex].inputLastState == 255));
                Serial.println((!onKeyUp && channel[chanelIndex].inputState == 255));
                if ((onKeyUp && channel[chanelIndex].inputLastState == 255) || (!onKeyUp && channel[chanelIndex].inputLastState == 0))
                {
                    if (channel[chanelIndex].outgoingValue > 127)
                    {
                        out = 0;
                    }
                    else
                    {
                        out = 255;
                    }
                }
            }
            if (channel[chanelIndex].d_o > 0)
            {
                if (channel[chanelIndex].incomingValue > 127)
                {
                    digitalWrite(channel[chanelIndex].d_o, HIGH);
                }
                else
                {
                    digitalWrite(channel[chanelIndex].d_o, LOW);
                }
            }
            break;
        case 10:
            aState = analogRead(channel[chanelIndex].a_i);
            // Serial.println(aState);
            channel[chanelIndex].inputState = map(aState, 0, 872, 0, 255);
            if (channel[chanelIndex].inputState < PotiTolerance)
            {
                channel[chanelIndex].inputState = 0;
            }
            else if (channel[chanelIndex].inputState > (255 - PotiTolerance))
            {
                channel[chanelIndex].inputState = 255;
            }
            else
            {
                // distance
                tmp0 = fabs(channel[chanelIndex].inputState - channel[chanelIndex].outgoingValue);
                if (tmp0 <= PotiTolerance)
                {
                    channel[chanelIndex].inputState = channel[chanelIndex].outgoingValue;
                }
            }
            out = channel[chanelIndex].inputState;
            break;
        default:
            out = channel[chanelIndex].inputState;
            Serial.println("No such Type");
        }
        if (channel[chanelIndex].inputState != channel[chanelIndex].inputLastState)
        {
            if (DEVMODE)
            {
                printStatus(chanelIndex, "mainloop");
            }
            channel[chanelIndex].inputLastState = channel[chanelIndex].inputState;
            channel[chanelIndex].outgoingValue = out;
        }
    }
}

void printStatus(int chanelIndex, char type[8])
{
    Serial.print("###  ");
    Serial.print(chanelIndex);
    Serial.print("  ###  ");
    Serial.print(type);
    Serial.println("  ###");
    Serial.print("inputState: ");
    Serial.print(channel[chanelIndex].inputLastState);
    Serial.print(" -> ");
    Serial.println(channel[chanelIndex].inputState);
    Serial.print("incomingValue: ");
    Serial.print(channel[chanelIndex].incomingLastValue);
    Serial.print(" -> ");
    Serial.println(channel[chanelIndex].incomingValue);
    Serial.print("outgoingValue: ");
    Serial.print(channel[chanelIndex].outgoingLastValue);
    Serial.print(" -> ");
    Serial.println(channel[chanelIndex].outgoingValue);
    // delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
    for (int chanelIndex = 0; chanelIndex < CHANNELCOUNT; chanelIndex++)
    {
        channel[chanelIndex].incomingValue = Wire.read();
        if (channel[chanelIndex].incomingValue != channel[chanelIndex].incomingLastValue)
        {
            channel[chanelIndex].outgoingValue = channel[chanelIndex].incomingValue;
            if (DEVMODE)
            {

                printStatus(chanelIndex, "incoming");
            }
            channel[chanelIndex].incomingLastValue = channel[chanelIndex].incomingValue;
        }
    }
}

void requestEvent()
{
    for (int chanelIndex = 0; chanelIndex < CHANNELCOUNT; chanelIndex++)
    {
        Wire.write(channel[chanelIndex].outgoingValue);
        if (channel[chanelIndex].outgoingValue != channel[chanelIndex].outgoingLastValue)
        {
            if (DEVMODE)
            {
                printStatus(chanelIndex, "outgoing");
            }
            channel[chanelIndex].outgoingLastValue = channel[chanelIndex].outgoingValue;
        }
    }
}