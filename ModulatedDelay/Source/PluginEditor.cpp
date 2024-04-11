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
    chorusDelaySlider.setRange(1.f,50.f);
    chorusDelaySlider.setSkewFactorFromMidPoint(25.f);
    chorusDelaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    chorusDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(chorusDelaySlider);
    chorusDelaySlider.addListener(this);
    
    // Chorus Wet Knob
//    chorusWetSlider.setBounds(490, 30, 80, 80);
    chorusWetSlider.setBounds(260, 150, 80, 80);
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
    flangerDelaySlider.setRange(1.f,50.f);
    flangerDelaySlider.setSkewFactorFromMidPoint(25.f);
    flangerDelaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    flangerDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(flangerDelaySlider);
    flangerDelaySlider.addListener(this);
    
    // Flanger Wet Knob
    flangerWetSlider.setBounds(260, 150, 80, 80);
    flangerWetSlider.setRange(0.f,100.f);
    flangerWetSlider.setSkewFactorFromMidPoint(50.f);
    flangerWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    flangerWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(flangerWetSlider);
    flangerWetSlider.addListener(this);
    
    // Phaser Rate Knob
    phaserRateSlider.setBounds(100, 200, 100, 100);
    phaserRateSlider.setRange(0.1f,10.f);
    phaserRateSlider.setSkewFactorFromMidPoint(5.f);
    phaserRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaserRateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(phaserRateSlider);
    phaserRateSlider.addListener(this);
    
    // Phaser Depth Knob
    phaserDepthSlider.setBounds(400, 200, 100, 100);
    phaserDepthSlider.setRange(500.f,1500.f);
    phaserDepthSlider.setSkewFactorFromMidPoint(1000.f);
    phaserDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaserDepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(phaserDepthSlider);
    phaserDepthSlider.addListener(this);
    
    // Phaser Center Frequency Knob
    phaserCenterFreqSlider.setBounds(250, 275, 100, 100);
    phaserCenterFreqSlider.setRange(250.f,12000.f);
    phaserCenterFreqSlider.setSkewFactorFromMidPoint(6000.f);
    phaserCenterFreqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaserCenterFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(phaserCenterFreqSlider);
    phaserCenterFreqSlider.addListener(this);
    
    // Phaser Wet Knob
    phaserWetSlider.setBounds(260, 150, 80, 80);
    phaserWetSlider.setRange(0.f,100.f);
    phaserWetSlider.setSkewFactorFromMidPoint(50.f);
    phaserWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaserWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(phaserWetSlider);
    phaserWetSlider.addListener(this);
    
    // ComboBox Selection
    selector.addListener(this);
    selector.setBounds(230, 70, 140, 40);
    selector.addItem("Chorus",1);
    selector.addItem("Flanger",2);
    selector.addItem("Phaser",3);
    addAndMakeVisible(selector);
    
    // Toggle Button
    bypassButton.setBounds(20, 10, 100, 50);
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
    auto baseColour = juce::Colours::salmon;
    auto colour = baseColour.brighter();
    g.fillAll (colour);
    
    g.setColour (juce::Colours::white);
    g.setFont (40.0f);
    g.drawFittedText ("3-in-1 Mod-Delay", getLocalBounds(), juce::Justification::centredTop, false);
    
    // I'm not sure how to change which text appears for which effect, e.g. "Center Freq" in lieu of "Delay" for Phaser
    g.setFont(20.0f);
    g.drawText ("Rate", 100, 170, 100, 40, juce::Justification::centred, false);
    g.drawText ("Depth", 400, 170, 100, 40, juce::Justification::centred, false);
    g.drawText ("Delay", 250, 245, 100, 40, juce::Justification::centred, false);
    g.drawText ("Wet", 249, 120, 100, 40, juce::Justification::centred, false);
    
    // Eventually, I want to include a randomization button (die image) in the upper right corner to randomly assign reasonable values for the effect that is selected in the comboBox. That's the last remaining UI feature to code
}

void ModulatedDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

// derived class implementation for changing each slider value
void ModulatedDelayAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    if(slider == &chorusRateSlider) {
        audioProcessor.chorusEffectRate = chorusRateSlider.getValue();
    }
    
    if(slider == &chorusDepthSlider) {
        audioProcessor.chorusEffectDepth = chorusDepthSlider.getValue();
    }
    
    if(slider == &chorusDelaySlider) {
        audioProcessor.chorusEffectDelay = chorusDelaySlider.getValue();
    }
    
    if(slider == &chorusWetSlider) {
        audioProcessor.chorusEffectWet = chorusWetSlider.getValue();
    }
    
    if(slider == &flangerRateSlider) {
        audioProcessor.flangerEffectRate = flangerRateSlider.getValue();
    }
    
    if(slider == &flangerDepthSlider) {
        audioProcessor.flangerEffectDepth = flangerDepthSlider.getValue();
    }
    
    if(slider == &flangerDelaySlider) {
        audioProcessor.flangerEffectDelay = flangerDelaySlider.getValue();
    }
    
    if(slider == &flangerWetSlider) {
        audioProcessor.flangerEffectWet = flangerWetSlider.getValue();
    }
    
    if(slider == &phaserRateSlider) {
        audioProcessor.phaserEffectRate = phaserRateSlider.getValue();
    }
    
    if(slider == &phaserDepthSlider) {
        audioProcessor.phaserEffectDepth = phaserDepthSlider.getValue();
    }
    
    if(slider == &phaserCenterFreqSlider) {
        audioProcessor.phaserEffectCenterFreq = phaserCenterFreqSlider.getValue();
    }
    
    if(slider == &phaserWetSlider) {
        audioProcessor.phaserEffectWet = phaserWetSlider.getValue();
    }
}

// derived class implementation for changing the drop-down menu selection
void ModulatedDelayAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBox) {
    if(comboBox == &selector) {
        if(selector.getSelectedId() == 1) {
            audioProcessor.setEffect(selector.getSelectedId());
            chorusRateSlider.setVisible(true);
            chorusDepthSlider.setVisible(true);
            chorusDelaySlider.setVisible(true);
            chorusWetSlider.setVisible(true);
            flangerRateSlider.setVisible(false);
            flangerDepthSlider.setVisible(false);
            flangerDelaySlider.setVisible(false);
            flangerWetSlider.setVisible(false);
            phaserRateSlider.setVisible(false);
            phaserDepthSlider.setVisible(false);
            phaserCenterFreqSlider.setVisible(false);
            phaserWetSlider.setVisible(false);
        }
        
        if(selector.getSelectedId() == 2) {
            audioProcessor.setEffect(selector.getSelectedId());
            chorusRateSlider.setVisible(false);
            chorusDepthSlider.setVisible(false);
            chorusDelaySlider.setVisible(false);
            chorusWetSlider.setVisible(false);
            flangerRateSlider.setVisible(true);
            flangerDepthSlider.setVisible(true);
            flangerDelaySlider.setVisible(true);
            flangerWetSlider.setVisible(true);
            phaserRateSlider.setVisible(false);
            phaserDepthSlider.setVisible(false);
            phaserCenterFreqSlider.setVisible(false);
            phaserWetSlider.setVisible(false);
        }
        
        if(selector.getSelectedId() == 3) {
            audioProcessor.setEffect(selector.getSelectedId());
            chorusRateSlider.setVisible(false);
            chorusDepthSlider.setVisible(false);
            chorusDelaySlider.setVisible(false);
            chorusWetSlider.setVisible(false);
            flangerRateSlider.setVisible(false);
            flangerDepthSlider.setVisible(false);
            flangerDelaySlider.setVisible(false);
            flangerWetSlider.setVisible(false);
            phaserRateSlider.setVisible(true);
            phaserDepthSlider.setVisible(true);
            phaserCenterFreqSlider.setVisible(true);
            phaserWetSlider.setVisible(true);
        }
    }
}

// derived class implementation for engaging the bypass toggle button
void ModulatedDelayAudioProcessorEditor::buttonClicked(juce::Button* button) {
    if(button == &bypassButton) {
        audioProcessor.bypass = bypassButton.getToggleState();
    }
}
