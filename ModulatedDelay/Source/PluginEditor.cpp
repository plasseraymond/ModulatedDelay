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
    
    auto baseColor = juce::Colour(242,137,92);
    
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::azure);
    getLookAndFeel().setColour(juce::Slider::rotarySliderOutlineColourId, baseColor.brighter(0.6f));
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, baseColor.darker(0.6f));
    getLookAndFeel().setColour(juce::Slider::textBoxOutlineColourId, baseColor);
    getLookAndFeel().setColour(juce::ComboBox::backgroundColourId, baseColor.darker(0.6f));
    getLookAndFeel().setColour(juce::TextButton::buttonColourId, baseColor.brighter(0.6f));
    getLookAndFeel().setColour(juce::TextButton::buttonOnColourId, baseColor.darker(0.6f));
    getLookAndFeel().setDefaultSansSerifTypefaceName("Avenir");

    // Chorus Rate Knob
    chorusRateSlider.setBounds(90, 200, 120, 120);
    chorusRateSlider.setRange(0.1f,10.f);
    chorusRateSlider.setSkewFactorFromMidPoint(5.f);
    chorusRateSlider.setNumDecimalPlacesToDisplay(1);
    chorusRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    chorusRateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    chorusRateSlider.setTextValueSuffix(" hz");
    addAndMakeVisible(chorusRateSlider);
    chorusRateSlider.addListener(this);
    
    // Chorus Depth Knob
    chorusDepthSlider.setBounds(390, 200, 120, 120);
    chorusDepthSlider.setRange(1.f,10.f);
    chorusDepthSlider.setSkewFactorFromMidPoint(5.f);
    chorusDepthSlider.setNumDecimalPlacesToDisplay(1);
    chorusDepthSlider.setTextValueSuffix(" ms");
    chorusDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    chorusDepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(chorusDepthSlider);
    chorusDepthSlider.addListener(this);
    
    // Chorus Delay Knob
    chorusDelaySlider.setBounds(240, 275, 120, 120);
    chorusDelaySlider.setRange(10.f,50.f);
    chorusDelaySlider.setSkewFactorFromMidPoint(30.f);
    chorusDelaySlider.setNumDecimalPlacesToDisplay(1);
    chorusDelaySlider.setTextValueSuffix(" ms");
    chorusDelaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    chorusDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(chorusDelaySlider);
    chorusDelaySlider.addListener(this);
    
    // Chorus Wet Knob
    chorusWetSlider.setBounds(260, 150, 80, 80);
    chorusWetSlider.setRange(0.f,100.f);
    chorusWetSlider.setSkewFactorFromMidPoint(50.f);
    chorusWetSlider.setNumDecimalPlacesToDisplay(0);
    chorusWetSlider.setTextValueSuffix(" %");
    chorusWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    chorusWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(chorusWetSlider);
    chorusWetSlider.addListener(this);
    
    // Flanger Rate Knob
    flangerRateSlider.setBounds(90, 200, 120, 120);
    flangerRateSlider.setRange(0.1f,10.f);
    flangerRateSlider.setSkewFactorFromMidPoint(5.f);
    flangerRateSlider.setNumDecimalPlacesToDisplay(1);
    flangerRateSlider.setTextValueSuffix(" hz");
    flangerRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    flangerRateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    flangerRateSlider.addListener(this);
    
    // Flanger Depth Knob
    flangerDepthSlider.setBounds(390, 200, 120, 120);
    flangerDepthSlider.setRange(1.f,10.f);
    flangerDepthSlider.setSkewFactorFromMidPoint(5.f);
    flangerDepthSlider.setNumDecimalPlacesToDisplay(1);
    flangerDepthSlider.setTextValueSuffix(" samples");
    flangerDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    flangerDepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    flangerDepthSlider.addListener(this);
    
    // Flanger Delay Knob
    flangerDelaySlider.setBounds(240, 275, 120, 120);
    flangerDelaySlider.setRange(1.f,50.f);
    flangerDelaySlider.setSkewFactorFromMidPoint(25.f);
    flangerDelaySlider.setNumDecimalPlacesToDisplay(1);
    flangerDelaySlider.setTextValueSuffix(" samples");
    flangerDelaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    flangerDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    flangerDelaySlider.addListener(this);
    
    // Flanger Wet Knob
    flangerWetSlider.setBounds(260, 150, 80, 80);
    flangerWetSlider.setRange(0.f,100.f);
    flangerWetSlider.setSkewFactorFromMidPoint(50.f);
    flangerWetSlider.setNumDecimalPlacesToDisplay(0);
    flangerWetSlider.setTextValueSuffix(" %");
    flangerWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    flangerWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    flangerWetSlider.addListener(this);
    
    // Phaser Rate Knob
    phaserRateSlider.setBounds(90, 200, 120, 120);
    phaserRateSlider.setRange(0.1f,10.f);
    phaserRateSlider.setSkewFactorFromMidPoint(5.f);
    phaserRateSlider.setNumDecimalPlacesToDisplay(1);
    phaserRateSlider.setTextValueSuffix(" hz");
    phaserRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaserRateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    phaserRateSlider.addListener(this);
    
    // Phaser Depth Knob
    phaserDepthSlider.setBounds(390, 200, 120, 120);
    phaserDepthSlider.setRange(500.f,1500.f);
    phaserDepthSlider.setSkewFactorFromMidPoint(1000.f);
    phaserDepthSlider.setNumDecimalPlacesToDisplay(1);
    phaserDepthSlider.setTextValueSuffix(" hz");
    phaserDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaserDepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    phaserDepthSlider.addListener(this);
    
    // Phaser Center Frequency Knob
    phaserCenterFreqSlider.setBounds(240, 275, 120, 120);
    phaserCenterFreqSlider.setRange(200.f,12000.f);
    phaserCenterFreqSlider.setSkewFactorFromMidPoint(6100.f);
    phaserCenterFreqSlider.setNumDecimalPlacesToDisplay(1);
    phaserCenterFreqSlider.setTextValueSuffix(" hz");
    phaserCenterFreqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaserCenterFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    phaserCenterFreqSlider.addListener(this);
    
    // Phaser Wet Knob
    phaserWetSlider.setBounds(260, 150, 80, 80);
    phaserWetSlider.setRange(0.f,100.f);
    phaserWetSlider.setSkewFactorFromMidPoint(50.f);
    phaserWetSlider.setNumDecimalPlacesToDisplay(0);
    phaserWetSlider.setTextValueSuffix(" %");
    phaserWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaserWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    phaserWetSlider.addListener(this);
    
    // ComboBox Selection
    selector.addListener(this);
    selector.setBounds(230, 70, 140, 40);
    selector.addItem("chorus",1);
    selector.addItem("flanger",2);
    selector.addItem("phaser",3);
    addAndMakeVisible(selector);
    
    // Toggle Button
//    bypassButton.setBounds(20, 20, 100, 100);
//    bypassButton.setButtonText("bypass");
//    bypassButton.setToggleState(false, juce::dontSendNotification);
    bypassButton.setClickingTogglesState(true);
    bypassButton.setBounds(25, 25, 60, 40);
    addAndMakeVisible(bypassButton);
    bypassButton.addListener(this);
}

ModulatedDelayAudioProcessorEditor::~ModulatedDelayAudioProcessorEditor()
{
}

//==============================================================================
void ModulatedDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour(242,137,92));
    
    g.setColour(juce::Colours::azure);
    g.setFont(55.f);
    g.drawText("Trifecta", 100, 4, 400, 60, juce::Justification::centred, false);
    
    g.setFont(30.f);
    g.drawText("rate", 100, 170, 100, 40, juce::Justification::centred, false);
    g.drawText("depth", 400, 170, 100, 40, juce::Justification::centred, false);
    g.drawText("mix", 250, 120, 100, 40, juce::Justification::centred, false);
    g.drawText("delay", 250, 245, 100, 40, juce::Justification::centred, false);

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
            addAndMakeVisible(chorusRateSlider);
            addAndMakeVisible(chorusDepthSlider);
            addAndMakeVisible(chorusDelaySlider);
            addAndMakeVisible(chorusWetSlider);
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
            addAndMakeVisible(flangerRateSlider);
            addAndMakeVisible(flangerDepthSlider);
            addAndMakeVisible(flangerDelaySlider);
            addAndMakeVisible(flangerWetSlider);
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
            addAndMakeVisible(phaserRateSlider);
            addAndMakeVisible(phaserDepthSlider);
            addAndMakeVisible(phaserCenterFreqSlider);
            addAndMakeVisible(phaserWetSlider);
        }
    }
}

// derived class implementation for engaging the bypass toggle button
void ModulatedDelayAudioProcessorEditor::buttonClicked(juce::Button* button) {
    if(button == &bypassButton) {
        audioProcessor.bypass = bypassButton.getToggleState();
    }
}
