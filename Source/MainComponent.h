// SOONG ZI RUI

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"
#include "KeyboardComponent.h"

class MainComponent : public juce::AudioAppComponent {
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::AudioFormatManager formatManager;
    juce::AudioThumbnailCache thumbCache{ 100 };

    DJAudioPlayer playerOne{ formatManager };
    DJAudioPlayer playerTwo{ formatManager };
    DJAudioPlayer playerThree{ formatManager }; 

    DeckGUI deckGUIOne{ &playerOne, formatManager, thumbCache };
    DeckGUI deckGUITwo{ &playerTwo, formatManager, thumbCache };

    juce::MixerAudioSource mixerSource;

    PlaylistComponent playlistComponent{ &playerThree, formatManager, thumbCache };

    KeyboardComponent keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
