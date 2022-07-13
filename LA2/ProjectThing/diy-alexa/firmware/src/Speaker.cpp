#include "Speaker.h"
#include "I2SOutput.h"
#include "WAVFileReader.h"

Speaker::Speaker(I2SOutput *i2s_output)
{
    m_i2s_output = i2s_output;
    m_ok = new WAVFileReader("/ok.wav");
    m_ready_ping = new WAVFileReader("/ready_ping.wav");
    m_cantdo = new WAVFileReader("/cantdo.wav");
    // add new .wav files 
    m_greeting = new WAVFileReader("/greeting.wav");
    m_encourage[0] = new WAVFileReader("/encourage1.wav");
    m_encourage[1] = new WAVFileReader("/encourage2.wav");
    m_positive[0] = new WAVFileReader("/positive1.wav");
    m_positive[1] = new WAVFileReader("/positive2.wav");
    m_tight = new WAVFileReader("/tight.wav");
    m_nothing = new WAVFileReader("/nothing.wav");
}

Speaker::~Speaker()
{
    delete m_ok;
    delete m_ready_ping;
    delete m_cantdo;
    delete m_greeting;
    delete m_encourage[0];
    delete m_encourage[1];
    delete m_positive[0];
    delete m_positive[1];
    delete m_tight;
    delete m_nothing;
    delete m_music;
}

void Speaker::playOK()
{
    m_ok->reset();
    m_i2s_output->setSampleGenerator(m_ok);
}

void Speaker::playReady()
{
    m_ready_ping->reset();
    m_i2s_output->setSampleGenerator(m_ready_ping);
}

void Speaker::playCantDo()
{
    m_cantdo->reset();
    m_i2s_output->setSampleGenerator(m_cantdo);
}

// Play the greeting file
void Speaker::playGreeting()
{
    m_music->reset();
    m_i2s_output->setSampleGenerator(m_greeting);
}

// Play a random selected encouraging file
void Speaker::playRandomEncourage()
{
    int encourage = rand()%2;
    m_encourage[encourage]->reset();
    m_i2s_output->setSampleGenerator(m_encourage[encourage]);
}

// Play a random selected congratulatory file
void Speaker::playRandomPosFeedback()
{
    int positive = rand()%2;
    m_positive[positive]->reset();
    m_i2s_output->setSampleGenerator(m_positive[positive]);
}

// Play the feeling tight file
void Speaker::playTight()
{
    m_tight->reset();
    m_i2s_output->setSampleGenerator(m_tight);
}

//  Play the feeling nothing file
void Speaker::playNothing()
{
    m_nothing->reset();
    m_i2s_output->setSampleGenerator(m_nothing);
}

// play the music file
void Speaker::playMusic()
{
   m_music->reset();
   m_i2s_output->setSampleGenerator(m_music);
}

