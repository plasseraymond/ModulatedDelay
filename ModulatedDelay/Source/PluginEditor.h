/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
// inherit the necessary GUI graphics classes to add listeners
class ModulatedDelayAudioProcessorEditor  : public juce::AudioProcessorEditor ,
                                            public juce::ComboBox::Listener
//                                            public juce::Slider::Listener ,
//                                            public juce::Button::Listener
{
public:
    ModulatedDelayAudioProcessorEditor (ModulatedDelayAudioProcessor&);
    ~ModulatedDelayAudioProcessorEditor() override;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    // override corresponding juce graphics methods for GUI components
    void comboBoxChanged(juce::ComboBox* comboBox) override;

private:

    ModulatedDelayAudioProcessor& audioProcessor;

    // ChorusEffect UI sliders
    juce::Slider chorusRateSlider;
    juce::Slider chorusDepthSlider;
    juce::Slider chorusDelaySlider;
    juce::Slider chorusWetSlider;
    
    // FlangerEffect UI sliders
    juce::Slider flangerRateSlider;
    juce::Slider flangerDepthSlider;
    juce::Slider flangerDelaySlider;
    juce::Slider flangerWetSlider;
    
    // PhaserEffect UI sliders
    juce::Slider phaserRateSlider;
    juce::Slider phaserDepthSlider;
    juce::Slider phaserCenterFreqSlider;
    juce::Slider phaserWetSlider;
    
    // UI drop-down menu
    juce::ComboBox selector;
    
    // UI bypass text button
    juce::TextButton bypassButton { "bypass" };
    
    // APVTS attachments
    std::vector<std::unique_ptr<SliderAttachment>> sliderAttachments;
    std::vector<std::unique_ptr<ButtonAttachment>> buttonAttachments;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulatedDelayAudioProcessorEditor)
};
