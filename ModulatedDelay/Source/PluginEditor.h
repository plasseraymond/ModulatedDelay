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
class ModulatedDelayAudioProcessorEditor  : public juce::AudioProcessorEditor ,
                                            public juce::ComboBox::Listener ,
                                            public juce::Slider::Listener ,
                                            public juce::Button::Listener
{
public:
    ModulatedDelayAudioProcessorEditor (ModulatedDelayAudioProcessor&);
    ~ModulatedDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(juce::Slider* slider) override;
    void comboBoxChanged(juce::ComboBox* comboBox) override;
    void buttonClicked(juce::Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ModulatedDelayAudioProcessor& audioProcessor;
        
    juce::Slider rateSlider;
    juce::Slider depthSlider;
    juce::Slider delaySlider;
    juce::Slider wetSlider;
    
    juce::ComboBox selector;
    
    juce::ToggleButton bypassButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulatedDelayAudioProcessorEditor)
};
