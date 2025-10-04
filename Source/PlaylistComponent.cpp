#include <JuceHeader.h>
#include "PlaylistComponent.h"

PlaylistComponent::PlaylistComponent(DJAudioPlayer* _player,
                                     juce::AudioFormatManager& formatManagerToUse,
                                     juce::AudioThumbnailCache& cacheToUse) : player(_player) {
    trackTitle.push_back("Track 1");
    trackTitle.push_back("Track 2");
    trackTitle.push_back("Track 3");
    trackTitle.push_back("Track 4");
    trackTitle.push_back("Track 5");

    tableComponent.getHeader().addColumn("Track Title", 1, 400/3);
    tableComponent.getHeader().addColumn("Artist Name", 2, 400/3);
    tableComponent.getHeader().addColumn("Track Duration", 3, 400/3);
    tableComponent.getHeader().addColumn("", 4, 80);
    tableComponent.getHeader().addColumn("", 5, 80);
    tableComponent.getHeader().addColumn("", 6, 80);
    tableComponent.getHeader().addColumn("", 7, 80);
    tableComponent.getHeader().addColumn("", 8, 80);

    tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);
}

PlaylistComponent::~PlaylistComponent() {
}

void PlaylistComponent::paint (juce::Graphics& g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
    g.setColour (juce::Colours::lavender);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::antiquewhite);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(), juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized() {
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

int PlaylistComponent::getNumRows() {
    return trackTitle.size();
}

void PlaylistComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) {  
    if (rowIsSelected) {
        g.fillAll(juce::Colours::floralwhite);
    }
    else {
        g.fillAll(juce::Colours::lavenderblush);
    }
}

void PlaylistComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) {
    g.drawText(trackTitle[rowNumber], 5, 0, width - 4, height, juce::Justification::centredLeft, true);
}

juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) {
    if (columnId == 4) {
        if (existingComponentToUpdate == nullptr) {
            juce::TextButton* playlistButton = new juce::TextButton { "PLAY" };
            juce::String id{ std::to_string(columnId) + std::to_string(rowNumber) };
            playlistButton->setComponentID(id);
            playlistButton->addListener(this);
            existingComponentToUpdate = playlistButton;
        }
    }

    if (columnId == 5) {
        if (existingComponentToUpdate == nullptr) {
            juce::TextButton* playlistButton = new juce::TextButton{ "LOAD" };
            juce::String id{ std::to_string(columnId) + std::to_string(rowNumber) };
            playlistButton->setComponentID(id);
            playlistButton->addListener(this);
            existingComponentToUpdate = playlistButton;
        }
    }

    if (columnId == 6) {
        if (existingComponentToUpdate == nullptr) {
            juce::TextButton* playlistButton = new juce::TextButton{ "STOP" };
            juce::String id{ std::to_string(columnId) + std::to_string(rowNumber) };
            playlistButton->setComponentID(id);
            playlistButton->addListener(this);
            existingComponentToUpdate = playlistButton;
        }
    }

    if (columnId == 7) {
        if (existingComponentToUpdate == nullptr) {
            juce::TextButton* playlistButton = new juce::TextButton{ "DECK 1" };
            juce::String id{ std::to_string(columnId) + std::to_string(rowNumber) };
            playlistButton->setComponentID(id);
            playlistButton->addListener(this);
            existingComponentToUpdate = playlistButton;
        }
    }

    if (columnId == 8) {
        if (existingComponentToUpdate == nullptr) {
            juce::TextButton* playlistButton = new juce::TextButton{ "DECK 2" };
            juce::String id{ std::to_string(columnId) + std::to_string(rowNumber) };
            playlistButton->setComponentID(id);
            playlistButton->addListener(this);
            existingComponentToUpdate = playlistButton;
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(juce::Button* button) {   
    int id = std::stoi(button->getComponentID().toStdString());

    if ((id / 10) == 4) {
        player->start();
    }

    if ((id / 10) == 5) {
        juce::FileChooser chooser{ "Select an audio file." };
        if (chooser.browseForFileToOpen()) {
            player->loadURL(juce::URL{ chooser.getResult() });
        }
    }

    if ((id / 10) == 6) {
        player->stop();
    }


    if ((id / 10) == 6) {
    }

    if ((id / 10) == 7) {
    }
}

bool PlaylistComponent::isInterestedInFileDrag(const juce::StringArray& files) {
    return true;
}

void PlaylistComponent::filesDropped(const juce::StringArray& files, int x, int y) {
    if (files.size() == 1) {
        player->loadURL(juce::URL{ juce::File{files[0]} });
    }
}