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
class ModulatedDelayAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ModulatedDelayAudioProcessorEditor (ModulatedDelayAudioProcessor&);
    ~ModulatedDelayAudioProcessorEditor() override;
    
    // saves me some extra steps not having to type this every time
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

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
    
    // UI die image button
    juce::ImageButton dieButton;
    
    // UI randomization method connected to die image button trigger click
    void randomizeParams(int selection);
        
    // APVTS attachments
    std::vector<std::unique_ptr<SliderAttachment>> sliderAttachments;
    std::vector<std::unique_ptr<ButtonAttachment>> buttonAttachments;
    std::vector<std::unique_ptr<ComboBoxAttachment>> comboBoxAttachments;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulatedDelayAudioProcessorEditor)
};
