/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ModulatedDelayAudioProcessorEditor::ModulatedDelayAudioProcessorEditor (ModulatedDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (600, 400);

    // Chorus Rate Knob
    chorusRateSlider.setBounds(100, 200, 100, 100);
    chorusRateSlider.setRange(0.1f,10.f);
    chorusRateSlider.setSkewFactorFromMidPoint(5.f);
    chorusRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    chorusRateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(chorusRateSlider);
    chorusRateSlider.addListener(this);
    
    // Chorus Depth Knob
    chorusDepthSlider.setBounds(400, 200, 100, 100);
    chorusDepthSlider.setRange(1.f,10.f);
    chorusDepthSlider.setSkewFactorFromMidPoint(5.f);
    chorusDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    chorusDepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(chorusDepthSlider);
    chorusDepthSlider.addListener(this);
    
    // Chorus Delay Knob
    chorusDelaySlider.setBounds(250, 275, 100, 100);
    chorusDelaySlider.setRange(10.f,50.f);
    chorusDelaySlider.setSkewFactorFromMidPoint(25.f);
    chorusDelaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    chorusDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(chorusDelaySlider);
    chorusDelaySlider.addListener(this);
    
    // Chorus Wet Knob
    chorusWetSlider.setBounds(490, 30, 80, 80);
    chorusWetSlider.setRange(0.f,100.f);
    chorusWetSlider.setSkewFactorFromMidPoint(50.f);
    chorusWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    chorusWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(chorusWetSlider);
    chorusWetSlider.addListener(this);
    
    // Flanger Rate Knob
    flangerRateSlider.setBounds(100, 200, 100, 100);
    flangerRateSlider.setRange(0.1f,10.f);
    flangerRateSlider.setSkewFactorFromMidPoint(5.f);
    flangerRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    flangerRateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(flangerRateSlider);
    flangerRateSlider.addListener(this);
    
    // Flanger Depth Knob
    flangerDepthSlider.setBounds(400, 200, 100, 100);
    flangerDepthSlider.setRange(1.f,10.f);
    flangerDepthSlider.setSkewFactorFromMidPoint(5.f);
    flangerDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    flangerDepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(flangerDepthSlider);
    flangerDepthSlider.addListener(this);
    
    // Flanger Delay Knob
    flangerDelaySlider.setBounds(250, 275, 100, 100);
    flangerDelaySlider.setRange(10.f,50.f);
    flangerDelaySlider.setSkewFactorFromMidPoint(25.f);
    flangerDelaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    flangerDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(flangerDelaySlider);
    flangerDelaySlider.addListener(this);
    
    // Flanger Wet Knob
    flangerWetSlider.setBounds(490, 30, 80, 80);
    flangerWetSlider.setRange(0.f,100.f);
    flangerWetSlider.setSkewFactorFromMidPoint(50.f);
    flangerWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    flangerWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(flangerWetSlider);
    flangerWetSlider.addListener(this);
    
    // ComboBox Selection
    selector.addListener(this);
    selector.setBounds(230, 100, 140, 40);
    selector.addItem("Chorus",1);
    selector.addItem("Flanger",2);
//    selector.addItem("Phaser",3);
//    selector.setText("Select Type...");
    addAndMakeVisible(selector);
    
    // Toggle Button
    bypassButton.setBounds(30, 20, 100, 50);
    bypassButton.setButtonText("Bypass");
    bypassButton.setToggleState(false, juce::dontSendNotification);
    addAndMakeVisible(bypassButton);
    bypassButton.addListener(this);
}

ModulatedDelayAudioProcessorEditor::~ModulatedDelayAudioProcessorEditor()
{
}

//==============================================================================
void ModulatedDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (25.0f);
    g.drawFittedText ("My Modulated Delay Plugin!", getLocalBounds(), juce::Justification::centredTop, 1);
    
    g.setFont(20.0f);
    g.drawText ("Rate", 100, 170, 100, 40, juce::Justification::centred, false);
    g.drawText ("Depth", 400, 170, 100, 40, juce::Justification::centred, false);
    g.drawText ("Delay", 250, 245, 100, 40, juce::Justification::centred, false);
    g.drawText ("Wet", 515, 0, 100, 40, juce::Justification::left, false);
}

void ModulatedDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

// derived class implementation for changing each slider value
void ModulatedDelayAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    if(slider == &chorusRateSlider) {
        audioProcessor.effectRate = chorusRateSlider.getValue();
    }
    
    if(slider == &chorusDepthSlider) {
        audioProcessor.effectDepth = chorusDepthSlider.getValue();
    }
    
    if(slider == &chorusDelaySlider) {
        audioProcessor.effectDelay = chorusDelaySlider.getValue();
    }
    
    if(slider == &chorusWetSlider) {
        audioProcessor.effectWet = chorusWetSlider.getValue();
    }
    
}

// derived class implementation for changing the drop-down menu selection
void ModulatedDelayAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBox) {
    if(comboBox == &selector) {
        audioProcessor.setEffect(selector.getSelectedId());
    }
}

// derived class implementation for engaging the bypass toggle button
void ModulatedDelayAudioProcessorEditor::buttonClicked(juce::Button* button) {
    if(button == &bypassButton) {
        audioProcessor.bypass = bypassButton.getToggleState();
    }
}
