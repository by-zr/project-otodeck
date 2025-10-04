#pragma once

#include <JuceHeader.h>

// I learnt how to built a keyboard synthesizer from https ://docs.juce.com/master/tutorial_synth_using_midi_input.html

class KeyboardComponent  : public juce::Component {
public:
    KeyboardComponent();
    ~KeyboardComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardComponent)
};
