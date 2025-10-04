#include "MainComponent.h"

MainComponent::MainComponent() {
    setSize(800, 600);

    if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
        && !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio)) {
        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
            [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
    }
    else {
        setAudioChannels(2, 2);
    }

    addAndMakeVisible(deckGUIOne);
    addAndMakeVisible(deckGUITwo);

    addAndMakeVisible(playlistComponent);

    addAndMakeVisible(keyboardComponent);

    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent() {
    shutdownAudio(); // Shuts down the audio device and clears the audio source.
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {

    playerOne.prepareToPlay(samplesPerBlockExpected, sampleRate);
    playerTwo.prepareToPlay(samplesPerBlockExpected, sampleRate);
    playerThree.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    mixerSource.addInputSource(&playerOne, false);
    mixerSource.addInputSource(&playerTwo, false);
    mixerSource.addInputSource(&playerThree, false);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    playerOne.releaseResources();
    playerTwo.releaseResources();
    playerThree.releaseResources();
    mixerSource.releaseResources();

}

void MainComponent::paint(juce::Graphics& g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized() {
    int widgetHeight = getHeight() / 4;

    deckGUIOne.setBounds(0, 0, getWidth() / 2, 2 * widgetHeight);
    deckGUITwo.setBounds(getWidth() / 2, 0, getWidth() / 2, 2 * widgetHeight);

    playlistComponent.setBounds(0, getHeight() / 2, getWidth(), widgetHeight);

    keyboardComponent.setBounds(0, 3 * widgetHeight, getWidth(), widgetHeight);
}

