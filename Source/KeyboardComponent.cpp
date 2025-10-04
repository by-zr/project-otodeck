// SOONG ZI RUI

#include <JuceHeader.h>
#include "KeyboardComponent.h"

// I learnt how to built a keyboard synthesizer from https ://docs.juce.com/master/tutorial_synth_using_midi_input.html

KeyboardComponent::KeyboardComponent() :
keyboardComponent(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard) {
    addAndMakeVisible(keyboardComponent);

    setSize(600, 160);
}

KeyboardComponent::~KeyboardComponent() {
}

void KeyboardComponent::paint (juce::Graphics& g) {
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawText ("KeyboardComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void KeyboardComponent::resized() {
    keyboardComponent.setBounds(10, 10, getWidth() - 20, getHeight() - 20);
}
