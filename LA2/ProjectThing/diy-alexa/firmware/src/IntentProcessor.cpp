#include <Arduino.h>
#include "IntentProcessor.h"
#include "Speaker.h"
#include <dotstar_wing.h>

IntentProcessor::IntentProcessor(Speaker *speaker)
{
    m_speaker = speaker;
}

IntentResult IntentProcessor::greeting()
{
    m_speaker->playGreeting();
    return SILENT_SUCCESS;
}

// Determine whether the semantic meaning is positive or negative and returns the corresponding feedback
IntentResult IntentProcessor::sentiment(const Intent &intent)
{
    if (intent.intent_confidence < 0.4)
    {
        Serial.printf("Only %.f%% certain on intent\n", 100 * intent.intent_confidence);
        return FAILED;
    }

    // If negative 
    if (intent.trait_value == "negative")
    {
        m_speaker->playRandomEncourage();
        return SILENT_SUCCESS;
    }
    // If positive
    else if (intent.trait_value == "positive") {
        m_speaker->playRandomPosFeedback();
        return SILENT_SUCCESS;
    }
    // If neutral
    else
    {
        Serial.println("I don't know how you feel");
    }
    // give the 'OK' feedback
    return SUCCESS;
}

// Determine if the pin is touched and returns the corresponding feedback 
IntentResult IntentProcessor::feel(const Intent &intent) 
{
    int touchVal = touchRead(T9);
    Serial.print("touchVal is ");
    Serial.println(touchVal);
    if (intent.intent_confidence < 0.4)
    {
        Serial.printf("Only %.f%% certain on intent\n", 100 * intent.intent_confidence);
        return FAILED;
    }

    // Capacitance is low - touched
    if (touchVal < 20) {
    m_speaker->playTight();
    return SILENT_SUCCESS;
    }

    // Not touched
    else 
    {
        m_speaker->playNothing();
        return SILENT_SUCCESS;
    }
}

// Play music and make LEDs blink
IntentResult IntentProcessor::music()
{
    m_speaker->playMusic();
   
    int i = 0;
    while (i<4) {
        for (const auto &dev_pin : m_device_to_pin)
        {
            digitalWrite(dev_pin.second, true);
            delay(200);
            digitalWrite(dev_pin.second, false);
            delay(200);
        }
        i++; 
    }
    
    return SILENT_SUCCESS;
}

IntentResult IntentProcessor::processIntent(const Intent &intent)
{
    Serial.printf(
      "processIntent: name=%s; confidence=%.f%%; trait_value=%s; trait_confidence=%.f%%\n",
      intent.intent_name.c_str(), 100 * intent.intent_confidence,
      intent.trait_value.c_str(), 100 * intent.trait_confidence
    );

    Serial.print("intent name is : ");
    Serial.println(intent.intent_name.c_str());
    if (intent.text.empty())
    {
        Serial.println("No text recognised");
        return FAILED;
    }
    Serial.printf("I heard \"%s\"\n", intent.text.c_str());
    if (intent.intent_name.empty())
    {
        Serial.println("Can't work out what you want to do with the device...");
        return FAILED;
    }
    Serial.printf("Intent is %s\n", intent.intent_name.c_str());

    //determine different instructions by the intent name
    if (intent.intent_name == "greeting")
    {
        return greeting();
    }
    if (intent.intent_name == "sentiment")
    {
        return sentiment(intent);
    }
    if (intent.intent_name == "true_or_false")
    {
        return feel(intent);
    }
    if (intent.intent_name == "wit$play_music")
    {
        return feel(intent);
    }

    return FAILED;
}

void IntentProcessor::addDevice(const std::string &name, int gpio_pin)
{
    m_device_to_pin.insert(std::make_pair(name, gpio_pin));
    pinMode(gpio_pin, OUTPUT);
}
