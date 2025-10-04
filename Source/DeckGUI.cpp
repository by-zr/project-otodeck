// SOONG ZI RUI

#include <JuceHeader.h>
#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer* _player, 
                 juce::AudioFormatManager& formatManagerToUse,
                 juce::AudioThumbnailCache& cacheToUse) : player(_player), 
                                                          waveformDisplay(formatManagerToUse, cacheToUse) {
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);

    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(positionSlider);

    addAndMakeVisible(waveformDisplay);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    volumeSlider.addListener(this);
    volumeSlider.setRange(0.0, 1.0);
    speedSlider.addListener(this);
    speedSlider.setRange(1.0, 10.0);
    positionSlider.addListener(this);
    positionSlider.setRange(0.0, 1.0);

    startTimer(60.0);
}

DeckGUI::~DeckGUI() {
    stopTimer();
}

void DeckGUI::paint(juce::Graphics& g) {
    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    getLookAndFeel().setColour(juce::TextButton::buttonColourId, juce::Colours::powderblue);
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    g.drawText("DeckGUI", getLocalBounds(), juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized() {
    double widgetHeight = getHeight() / 8;

    playButton.setBounds(0, 0, getWidth(), widgetHeight);
    stopButton.setBounds(0, widgetHeight, getWidth(), widgetHeight);
    volumeSlider.setBounds(0, 2 * widgetHeight, getWidth(), widgetHeight);
    speedSlider.setBounds(0, 3 * widgetHeight, getWidth(), widgetHeight);
    positionSlider.setBounds(0, 4 * widgetHeight, getWidth(), widgetHeight);
    waveformDisplay.setBounds(0, 5 * widgetHeight, getWidth(), 2 * widgetHeight);
    loadButton.setBounds(0, 7 * widgetHeight, getWidth(), widgetHeight);
}

void DeckGUI::buttonClicked(juce::Button* button) {
    if (button == &playButton) {
        DBG("Play button was clicked!");
        player->start();
    }
    if (button == &stopButton) {
        DBG("Stop button was clicked!");

        player->stop();
    }
    if (button == &loadButton) {
        juce::FileChooser chooser{ "Select an audio file." };
        if (chooser.browseForFileToOpen()) {
            player->loadURL(juce::URL{ chooser.getResult() });
            waveformDisplay.loadURL(juce::URL{ chooser.getResult() });
        }
    }
}

void DeckGUI::sliderValueChanged(juce::Slider* slider) {
    if (slider == &volumeSlider) {
        double volumeChanged = slider->getValue();
        DBG("Volume adjusted to " << volumeChanged << ".");
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider) {
        double speedChanged = slider->getValue();
        DBG("Speed adjusted to " << speedChanged << ".");
        player->setSpeed(slider->getValue());
    }

    if (slider == &positionSlider) {
        double positionChanged = slider->getValue();
        DBG("position adjusted to " << positionChanged << ".");
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files) {
    return true;
}

void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y) {
    if (files.size() == 1) {
        player->loadURL(juce::URL{ juce::File{files[0]} });
    }
}

void DeckGUI::timerCallback() {
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}