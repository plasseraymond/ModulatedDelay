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
    chorusRateSlider.setNumDecimalPlacesToDisplay(1);
    chorusRateSlider.setTextValueSuffix(" hz");
    chorusRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    chorusRateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    chorusRateSlider.onValueChange = [this]() {
        audioProcessor.chorusRateSliderChanged(chorusRateSlider.getValue());
    };
    addAndMakeVisible(chorusRateSlider);
    
    // Chorus Depth Knob
    chorusDepthSlider.setBounds(390, 200, 120, 120);
    chorusDepthSlider.setNumDecimalPlacesToDisplay(1);
    chorusDepthSlider.setTextValueSuffix(" ms");
    chorusDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    chorusDepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    chorusDepthSlider.onValueChange = [this]() {
        audioProcessor.chorusDepthSliderChanged(chorusDepthSlider.getValue());
    };
    addAndMakeVisible(chorusDepthSlider);
    
    // Chorus Delay Knob
    chorusDelaySlider.setBounds(240, 275, 120, 120);
    chorusDelaySlider.setNumDecimalPlacesToDisplay(1);
    chorusDelaySlider.setTextValueSuffix(" ms");
    chorusDelaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    chorusDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    chorusDelaySlider.onValueChange = [this]() {
        audioProcessor.chorusDelaySliderChanged(chorusDelaySlider.getValue());
    };
    addAndMakeVisible(chorusDelaySlider);
    
    // Chorus Wet Knob
    chorusWetSlider.setBounds(260, 150, 80, 80);
    chorusWetSlider.setNumDecimalPlacesToDisplay(0);
    chorusWetSlider.setTextValueSuffix(" %");
    chorusWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    chorusWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    chorusWetSlider.onValueChange = [this]() {
        audioProcessor.chorusWetSliderChanged(chorusWetSlider.getValue());
    };
    addAndMakeVisible(chorusWetSlider);
    
    // Flanger Rate Knob
    flangerRateSlider.setBounds(90, 200, 120, 120);
    flangerRateSlider.setNumDecimalPlacesToDisplay(1);
    flangerRateSlider.setTextValueSuffix(" hz");
    flangerRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    flangerRateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    flangerRateSlider.onValueChange = [this]() {
        audioProcessor.flangerRateSliderChanged(flangerRateSlider.getValue());
    };
    
    // Flanger Depth Knob
    flangerDepthSlider.setBounds(390, 200, 120, 120);
    flangerDepthSlider.setNumDecimalPlacesToDisplay(1);
    flangerDepthSlider.setTextValueSuffix(" samples");
    flangerDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    flangerDepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    flangerDepthSlider.onValueChange = [this]() {
        audioProcessor.flangerDepthSliderChanged(flangerDepthSlider.getValue());
    };
    
    // Flanger Delay Knob
    flangerDelaySlider.setBounds(240, 275, 120, 120);
    flangerDelaySlider.setNumDecimalPlacesToDisplay(1);
    flangerDelaySlider.setTextValueSuffix(" samples");
    flangerDelaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    flangerDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    flangerDelaySlider.onValueChange = [this]() {
        audioProcessor.flangerDelaySliderChanged(flangerDelaySlider.getValue());
    };
    
    // Flanger Wet Knob
    flangerWetSlider.setBounds(260, 150, 80, 80);
    flangerWetSlider.setNumDecimalPlacesToDisplay(0);
    flangerWetSlider.setTextValueSuffix(" %");
    flangerWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    flangerWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    flangerWetSlider.onValueChange = [this]() {
        audioProcessor.flangerWetSliderChanged(flangerWetSlider.getValue());
    };
    
    // Phaser Rate Knob
    phaserRateSlider.setBounds(90, 200, 120, 120);
    phaserRateSlider.setNumDecimalPlacesToDisplay(1);
    phaserRateSlider.setTextValueSuffix(" hz");
    phaserRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaserRateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    phaserRateSlider.onValueChange = [this]() {
        audioProcessor.phaserRateSliderChanged(phaserRateSlider.getValue());
    };
    
    // Phaser Depth Knob
    phaserDepthSlider.setBounds(390, 200, 120, 120);
    phaserDepthSlider.setNumDecimalPlacesToDisplay(1);
    phaserDepthSlider.setTextValueSuffix(" hz");
    phaserDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaserDepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    phaserDepthSlider.onValueChange = [this]() {
        audioProcessor.phaserDepthSliderChanged(phaserDepthSlider.getValue());
    };
    
    // Phaser Center Frequency Knob
    phaserCenterFreqSlider.setBounds(240, 275, 120, 120);
    phaserCenterFreqSlider.setNumDecimalPlacesToDisplay(1);
    phaserCenterFreqSlider.setTextValueSuffix(" hz");
    phaserCenterFreqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaserCenterFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    phaserCenterFreqSlider.onValueChange = [this]() {
        audioProcessor.phaserCenterFreqSliderChanged(phaserCenterFreqSlider.getValue());
    };
    
    // Phaser Wet Knob
    phaserWetSlider.setBounds(260, 150, 80, 80);
    phaserWetSlider.setNumDecimalPlacesToDisplay(0);
    phaserWetSlider.setTextValueSuffix(" %");
    phaserWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaserWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    phaserWetSlider.onValueChange = [this]() {
        audioProcessor.phaserWetSliderChanged(phaserWetSlider.getValue());
    };
    
    // ComboBox Selection
    selector.setBounds(230, 70, 140, 40);
    selector.addItem("chorus",1);
    selector.addItem("flanger",2);
    selector.addItem("phaser",3);
    selector.onChange = [this]() {
        audioProcessor.comboBoxChanged(selector.getSelectedId());
        if(selector.getSelectedId() == 1) {
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
    };
    addAndMakeVisible(selector);
    
    // Text Button
    bypassButton.setClickingTogglesState(true);
    bypassButton.setBounds(25, 25, 60, 40);
    bypassButton.onClick = [this]() {
        audioProcessor.buttonClicked(bypassButton.getToggleState());
    };
    addAndMakeVisible(bypassButton);
    
    
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,ModulatedDelayAudioProcessor::CHORUSKNOB1,chorusRateSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,ModulatedDelayAudioProcessor::CHORUSKNOB2,chorusDepthSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,ModulatedDelayAudioProcessor::CHORUSKNOB3,chorusDelaySlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,ModulatedDelayAudioProcessor::CHORUSKNOB4,chorusWetSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,ModulatedDelayAudioProcessor::FLANGERKNOB1,flangerRateSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,ModulatedDelayAudioProcessor::FLANGERKNOB2,flangerDepthSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,ModulatedDelayAudioProcessor::FLANGERKNOB3,flangerDelaySlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,ModulatedDelayAudioProcessor::FLANGERKNOB4,flangerWetSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,ModulatedDelayAudioProcessor::PHASERKNOB1,phaserRateSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,ModulatedDelayAudioProcessor::PHASERKNOB2,phaserDepthSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,ModulatedDelayAudioProcessor::PHASERKNOB3,phaserCenterFreqSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,ModulatedDelayAudioProcessor::PHASERKNOB4,phaserWetSlider));
    
    buttonAttachments.emplace_back(new ButtonAttachment(audioProcessor.apvts,ModulatedDelayAudioProcessor::BYPASSBUTTON,bypassButton));
        
    comboBoxAttachments.emplace_back(new ComboBoxAttachment(audioProcessor.apvts,ModulatedDelayAudioProcessor::COMBOBOX,selector));
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
