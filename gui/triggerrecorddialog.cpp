//  ------------------------------------------------------------------------
//
//  This file is part of the Intan Technologies RHD2000 Interface
//  Version 1.3
//  Copyright (C) 2013 Intan Technologies
//
//  ------------------------------------------------------------------------
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <QtGui>

#include "qtincludes.h"
#include "triggerrecorddialog.h"

// Triggered recording dialog.
// Allows users to select a digital input channel for a triggered
// recording session.

TriggerRecordDialog::TriggerRecordDialog(int initialTriggerChannel, int initialTriggerPolarity,
                                         int initialTriggerBuffer, int initialTriggerRepeat, //FIXME the order of this is out of order with the way I have listed them elsewhere
					                     int initialTriggerSamples, int initialTriggerPerFile,
                                         double triggerAnalogThreshold, bool recordOnConst, QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Triggered Recording Control"));
    setFixedWidth(340);

    QLabel *label1 = new QLabel(tr("Digital or analog inputs lines may be used to trigger "
                                   "recording.  If an analog input line is selected, you may "
                                   "set the threshold between logic high and logic low."));
    label1->setWordWrap(true);

    digitalInputComboBox = new QComboBox();
    digitalInputComboBox->addItem(tr("Digital Input 0"));
    digitalInputComboBox->addItem(tr("Digital Input 1"));
    digitalInputComboBox->addItem(tr("Digital Input 2"));
    digitalInputComboBox->addItem(tr("Digital Input 3"));
    digitalInputComboBox->addItem(tr("Digital Input 4"));
    digitalInputComboBox->addItem(tr("Digital Input 5"));
    digitalInputComboBox->addItem(tr("Digital Input 6"));
    digitalInputComboBox->addItem(tr("Digital Input 7"));
    digitalInputComboBox->addItem(tr("Digital Input 8"));
    digitalInputComboBox->addItem(tr("Digital Input 9"));
    digitalInputComboBox->addItem(tr("Digital Input 10"));
    digitalInputComboBox->addItem(tr("Digital Input 11"));
    digitalInputComboBox->addItem(tr("Digital Input 12"));
    digitalInputComboBox->addItem(tr("Digital Input 13"));
    digitalInputComboBox->addItem(tr("Digital Input 14"));
    digitalInputComboBox->addItem(tr("Digital Input 15"));
    digitalInputComboBox->addItem(tr("Analog Input 1"));
    digitalInputComboBox->addItem(tr("Analog Input 2"));
    digitalInputComboBox->addItem(tr("Analog Input 3"));
    digitalInputComboBox->addItem(tr("Analog Input 4"));
    digitalInputComboBox->addItem(tr("Analog Input 5"));
    digitalInputComboBox->addItem(tr("Analog Input 6"));
    digitalInputComboBox->addItem(tr("Analog Input 7"));
    digitalInputComboBox->addItem(tr("Analog Input 8"));
    digitalInputComboBox->setCurrentIndex(initialTriggerChannel);

    connect(digitalInputComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setDigitalInput(int)));

    triggerPolarityComboBox = new QComboBox();
    triggerPolarityComboBox->addItem(tr("Trigger on Logic High"));
    triggerPolarityComboBox->addItem(tr("Trigger on Logic Low"));
    triggerPolarityComboBox->setCurrentIndex(initialTriggerPolarity);

    connect(triggerPolarityComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setTriggerPolarity(int)));

    QVBoxLayout *triggerControls = new QVBoxLayout; //FIXME change trigger controls to be a QHBoxLayout so we can have the check box on the right
    triggerControls->addWidget(digitalInputComboBox);
    triggerControls->addWidget(triggerPolarityComboBox);

    // analog controls
    triggerAnalogSpinBox = new QDoubleSpinBox;
    triggerAnalogSpinBox->setRange(0,3.3); // FIXME aren't there some inputs that go [-3.3,3.3] ?
    triggerAnalogSpinBox->setDecimals(2);
    triggerAnalogSpinBox->setSingleStep(.1);
    triggerAnalogSpinBox->setValue(triggerAnalogThreshold);

    QVBoxLayout *triggerAnalog = new QVBoxLayout;
    triggerAnalog->addWidget(new QLabel(tr("Analog threshold (V)")));
    triggerAnalog->addWidget(triggerAnalogSpinBox);

    QHBoxLayout *triggerSettings = new QHBoxLayout;
    triggerSettings->addLayout(triggerControls);
    triggerSettings->addLayout(triggerAnalog);

    //Trigger repeate code
    //set number of repeats before end TODO if this is set then samples per trigger MUST be set
    triggerRepsSpinBox = new QSpinBox();
    triggerRepsSpinBox->setRange(0,999);
    triggerRepsSpinBox->setValue(initialTriggerRepeat);
    triggerRepsSpinBox->setMinimumHeight(18);

    //set number of samples per trigger
    triggerSamplesSpinBox = new QSpinBox();
    triggerSamplesSpinBox->setRange(1,99999999); //FIXME this really aught to be in seconds...
    triggerSamplesSpinBox->setValue(initialTriggerSamples);
    triggerSamplesSpinBox->setMinimumHeight(18);

    //set number of triggers per file
    triggerPerFileSpinBox = new QSpinBox();
    triggerPerFileSpinBox->setRange(1,999); //FIXME this really aught to be in seconds...
    triggerPerFileSpinBox->setValue(initialTriggerPerFile);
    triggerPerFileSpinBox->setMinimumHeight(18);
  
    QVBoxLayout *triggerRepsLayout = new QVBoxLayout;
    triggerRepsLayout->addWidget(new QLabel(tr("Number of times to trigger")));
    triggerRepsLayout->addWidget(triggerRepsSpinBox);
    triggerRepsLayout->addWidget(new QLabel(tr("Samples per trigger")));
    triggerRepsLayout->addWidget(triggerSamplesSpinBox);
    triggerRepsLayout->addWidget(new QLabel(tr("Triggers per file")));
    triggerRepsLayout->addWidget(triggerPerFileSpinBox);

    
    //recordOnConst checkbox space
    recordOnConstCheckBox = new QCheckBox("Record continually");
    recordOnConstCheckBox->setChecked(recordOnConst);

    //if we are initing with roc this will disable the repeat boxes
    triggerRepeatEnable();

    connect(recordOnConstCheckBox, SIGNAL(clicked(bool)),
            this, SLOT(triggerRepeatEnable(void)));

    QHBoxLayout *recordOnConstLayout = new QHBoxLayout;
    recordOnConstLayout->addWidget(recordOnConstCheckBox);

    QGroupBox *recordGroupBox = new QGroupBox("Record on High/Low logic");
    recordGroupBox->setLayout(recordOnConstLayout);

    QGroupBox *triggerRepsBox = new QGroupBox(tr("Trigger Repeats"));
    triggerRepsBox->setLayout(triggerRepsLayout);

    QHBoxLayout *triggerRepsHLayout = new QHBoxLayout;
    triggerRepsHLayout->addWidget(triggerRepsBox);
    triggerRepsHLayout->addWidget(recordGroupBox);
    triggerRepsHLayout->addStretch(1);

    //end additions

    QHBoxLayout *triggerHBox = new QHBoxLayout;
    triggerHBox->addLayout(triggerSettings);
    triggerHBox->addStretch(1);

    QVBoxLayout *triggerLayout = new QVBoxLayout;
    triggerLayout->addWidget(label1);
    triggerLayout->addLayout(triggerHBox);

    QGroupBox *triggerGroupBox = new QGroupBox(tr("Trigger Source"));
    triggerGroupBox->setLayout(triggerLayout);

    QHBoxLayout *triggerHLayout = new QHBoxLayout;
    triggerHLayout->addWidget(triggerGroupBox);


    recordBufferSpinBox = new QSpinBox();
    recordBufferSpinBox->setRange(1, 30);
    recordBufferSpinBox->setValue(initialTriggerBuffer);

    connect(recordBufferSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(recordBufferSeconds(int)));

    QHBoxLayout *bufferSpinBoxLayout = new QHBoxLayout;
    bufferSpinBoxLayout->addWidget(recordBufferSpinBox);
    bufferSpinBoxLayout->addWidget(new QLabel(tr("seconds")));
    bufferSpinBoxLayout->addStretch(1);

    QLabel *label2 = new QLabel(tr("If a pretrigger buffer size of N seconds is selected, "
                                   "slightly more than N seconds of pretrigger data will be "
                                   "saved to disk when a trigger is detected, assuming that "
                                   "data acquisition has been running for at least N seconds."));
    label2->setWordWrap(true);

    QVBoxLayout *bufferSelectLayout = new QVBoxLayout;
    bufferSelectLayout->addWidget(new QLabel(tr("Pretrigger data saved (range: 1-30 seconds):")));
    bufferSelectLayout->addLayout(bufferSpinBoxLayout);
    bufferSelectLayout->addWidget(label2);

    QGroupBox *bufferGroupBox = new QGroupBox(tr("Pretrigger Buffer"));
    bufferGroupBox->setLayout(bufferSelectLayout);

    QHBoxLayout *bufferHLayout = new QHBoxLayout;
    bufferHLayout->addWidget(bufferGroupBox);
//    bufferHLayout->addStretch(1);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QLabel *label3 = new QLabel(tr("Press OK to start triggered recording with selected settings.  "
                                   "Waveforms will be displayed in real time, but recording will "
                                   "not start until the trigger is detected.  A tone will indicate "
                                   "when the trigger has been detected.  Press the Stop button to "
                                   "cancel triggered recording."));
    label3->setWordWrap(true);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(triggerHLayout);
    mainLayout->addLayout(triggerRepsHLayout);
    mainLayout->addLayout(bufferHLayout);
    mainLayout->addWidget(label3);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    setDigitalInput(digitalInputComboBox->currentIndex());
    setTriggerPolarity(triggerPolarityComboBox->currentIndex());
    recordBufferSeconds(recordBufferSpinBox->value());

}

void TriggerRecordDialog::setDigitalInput(int index)
{
    digitalInput = index;
}

void TriggerRecordDialog::setTriggerPolarity(int index)
{
    triggerPolarity = index;
}

void TriggerRecordDialog::triggerRepeatEnable(void)
{
    triggerRepsSpinBox->setEnabled(!(recordOnConstCheckBox->isChecked()));
    triggerSamplesSpinBox->setEnabled(!(recordOnConstCheckBox->isChecked()));
}

void TriggerRecordDialog::recordBufferSeconds(int value)
{
    recordBuffer = value;
    buttonBox->setFocus();
}
