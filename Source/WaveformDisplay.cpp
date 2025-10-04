
#include <JuceHeader.h>
#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
                                 juce::AudioThumbnailCache& cacheToUse) : audioThumb(1000, formatManagerToUse, cacheToUse), 
                                                                          fileLoaded(false), localPosition(0) {
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay() {
}

void WaveformDisplay::paint (juce::Graphics& g) {
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.setColour (juce::Colours::lavenderblush);

    if (fileLoaded == true) {
        audioThumb.drawChannel(g, getLocalBounds(), 0.0, audioThumb.getTotalLength(), 0.0, 1.0f);
        g.setColour(juce::Colours::lavender);
        g.drawRect(localPosition * getWidth(), 0, getWidth() / 20, getHeight());
    } else {
        g.setColour(juce::Colours::white);
        g.setFont(20.0f);
        g.drawText("File not loaded.", getLocalBounds(), juce::Justification::centred, true);   // draw some placeholder text
    }
}

void WaveformDisplay::resized() {
}

void WaveformDisplay::loadURL(juce::URL audioURL) {
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));

    if (fileLoaded == true) {
        DBG("The track " << audioURL.getFileName() << " is loaded.");
    } else {
        DBG("Audio file is not loaded.");
    }
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster *source) {
    repaint();
}

void WaveformDisplay::setPositionRelative(double position) {
    if (position != localPosition) {
        localPosition = position;
        repaint();
    }
}
