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
    
    // override corresponding juce graphics methods for GUI components
    void sliderValueChanged(juce::Slider* slider) override;
    void comboBoxChanged(juce::ComboBox* comboBox) override;
    void buttonClicked(juce::Button* button) override;

private:

    ModulatedDelayAudioProcessor& audioProcessor;
    
    // declare ChorusEffect GUI sliders
    juce::Slider chorusRateSlider;
    juce::Slider chorusDepthSlider;
    juce::Slider chorusDelaySlider;
    juce::Slider chorusWetSlider;
    
    // declare FlangerEffect GUI sliders
    juce::Slider flangerRateSlider;
    juce::Slider flangerDepthSlider;
    juce::Slider flangerDelaySlider;
    juce::Slider flangerWetSlider;
    
    // declare PhaserEffect GUI sliders
    juce::Slider phaserRateSlider;
    juce::Slider phaserDepthSlider;
    juce::Slider phaserCenterFreqSlider;
    juce::Slider phaserWetSlider;
    
    // declare GUI drop-down menu
    juce::ComboBox selector;
    
    // declare GUI bypass checkbox
    juce::TextButton bypassButton { "bypass" };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulatedDelayAudioProcessorEditor)
};
