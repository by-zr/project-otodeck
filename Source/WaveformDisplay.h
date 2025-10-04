#pragma once

#include <JuceHeader.h>

class WaveformDisplay  : public juce::Component,
                         public juce::ChangeListener {
public:
    WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
                    juce::AudioThumbnailCache& cacheToUse);
    
    ~WaveformDisplay() override;

    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void loadURL(juce::URL audioURL);

    void setPositionRelative(double position); // To set the relative position of playhead

private:
    juce::AudioThumbnail audioThumb;
    bool fileLoaded;
    double localPosition;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
