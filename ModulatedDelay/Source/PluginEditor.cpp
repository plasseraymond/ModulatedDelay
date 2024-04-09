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
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);

    // Rate Knob
    rateSlider.setBounds(100, 200, 100, 100);
    rateSlider.setRange(0.1f,10.f);
    rateSlider.setSkewFactorFromMidPoint(5.f);
    rateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(rateSlider);
    rateSlider.addListener(this);
    
    // Depth Knob
    depthSlider.setBounds(400, 200, 100, 100);
    depthSlider.setRange(1.f,10.f);
    depthSlider.setSkewFactorFromMidPoint(5.f);
    depthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(depthSlider);
    depthSlider.addListener(this);
    
    // Delay Knob
    delaySlider.setBounds(250, 275, 100, 100);
    delaySlider.setRange(10.f,50.f);
    delaySlider.setSkewFactorFromMidPoint(25.f);
    delaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(delaySlider);
    delaySlider.addListener(this);
    
    // Wet Knob
    wetSlider.setBounds(490, 30, 80, 80);
    wetSlider.setRange(0.f,100.f);
    wetSlider.setSkewFactorFromMidPoint(50.f);
    wetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    wetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(wetSlider);
    wetSlider.addListener(this);
    
    // ComboBox Selection
    selector.addListener(this);
    selector.setBounds(230, 100, 140, 40);
    selector.addItem("Chorus",1);
    selector.addItem("Flanger",2);
    selector.addItem("Phaser",3);
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
    // (Our component is opaque, so we must completely fill the background with a solid colour)
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

void ModulatedDelayAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    if(slider == &rateSlider) {
        audioProcessor.effectRate = rateSlider.getValue();
    }
    
    if(slider == &depthSlider) {
        audioProcessor.effectDepth = depthSlider.getValue();
    }
    
    if(slider == &delaySlider) {
        audioProcessor.effectDelay = delaySlider.getValue();
    }
    
    if(slider == &wetSlider) {
        audioProcessor.effectWet = wetSlider.getValue();
    }
    
}

void ModulatedDelayAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBox) {
    if(comboBox == &selector) {
        audioProcessor.setEffect(selector.getSelectedId());
    }
}

void ModulatedDelayAudioProcessorEditor::buttonClicked(juce::Button* button) {
    if(button == &bypassButton) {
        audioProcessor.bypass = bypassButton.getToggleState();
    }
}
