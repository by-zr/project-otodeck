#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include <vector>
#include <string>

class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener,
                           public juce::FileDragAndDropTarget {
public:
    PlaylistComponent(DJAudioPlayer* player,
                      juce::AudioFormatManager& formatManagerToUse,
                      juce::AudioThumbnailCache& cacheToUse);
    ~PlaylistComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;

    void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;

    void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected,
                                       Component* existingComponentToUpdate) override;

    void buttonClicked(juce::Button* button) override;

    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

private:
    juce::TableListBox tableComponent;
    std::vector<std::string> trackTitle;

    DJAudioPlayer* player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
