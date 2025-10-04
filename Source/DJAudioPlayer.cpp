
#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager) : formatManager(_formatManager) {
}

DJAudioPlayer::~DJAudioPlayer() {
}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
    resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources() {
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(juce::URL audioURL) {
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) { // To determine whether the audio file is good
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}

void DJAudioPlayer::setGain(double gain) {
    if (gain < 0.0 || gain > 1.0) {
        DBG("Gain should be between 0.0 and 1.0.");
    }
    transportSource.setGain(gain);
}

void DJAudioPlayer::setSpeed(double ratio) {
    if (ratio < 0.0 || ratio > 10.0) {
        DBG("Ratio should be between 0.0 and 10.0.");
    }
    resampleSource.setResamplingRatio(ratio);
}

void DJAudioPlayer::setPosition(double positionInSeconds) {
    transportSource.setPosition(positionInSeconds);
}

void DJAudioPlayer::setPositionRelative(double position) {
    if (position < 0.0 || position > 1.0) {
        DBG("Position should be between 0.0 and 1.0.");
    } else {
        double positionInSeconds = transportSource.getLengthInSeconds() * position;
        setPosition(positionInSeconds);
    }
}

void DJAudioPlayer::start() {
    transportSource.start();
}

void DJAudioPlayer::stop() {
    transportSource.stop();
}

double DJAudioPlayer::getPositionRelative() {
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}