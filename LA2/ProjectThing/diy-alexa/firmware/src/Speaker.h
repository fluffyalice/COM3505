#ifndef _speaker_h_
#define _speaker_h_

class I2SOutput;
class WAVFileReader;

class Speaker
{
private:
    WAVFileReader *m_ok;
    WAVFileReader *m_cantdo;
    WAVFileReader *m_ready_ping;
    WAVFileReader *m_greeting;
    WAVFileReader *m_encourage[2];
    WAVFileReader *m_positive[2];
    WAVFileReader *m_tight;
    WAVFileReader *m_nothing;
    WAVFileReader *m_nothing1;
    WAVFileReader *m_music;

    I2SOutput *m_i2s_output;

public:
    Speaker(I2SOutput *i2s_output);
    ~Speaker();
    void playOK();
    void playReady();
    void playCantDo();
    void playRandomJoke();
    void playGreeting();
    void playRandomEncourage();
    void playRandomPosFeedback();
    void playTight();
    void playNothing();
    void playMusic();

};

#endif