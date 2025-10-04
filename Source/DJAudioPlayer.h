// SOONG ZI RUI

#pragma once
#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource {
public:
	DJAudioPlayer(juce::AudioFormatManager& _formatManager);
	~DJAudioPlayer();

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;

	void loadURL(juce::URL audioURL);
	void setGain(double gain);
	void setSpeed(double ratio);
	void setPosition(double positionInSeconds);
	void setPositionRelative(double position);

	void start();
	void stop();

	double getPositionRelative(); // To get the relative position of playhead

private:
	juce::AudioFormatManager& formatManager;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	juce::AudioTransportSource transportSource;
	juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
};