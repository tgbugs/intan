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

#ifndef TRIGGERRECORDDIALOG_H
#define TRIGGERRECORDDIALOG_H

#include <QDialog>
#include "qtincludes.h"

class QDialogButtonBox;
class QComboBox;
class QSpinBox;

class TriggerRecordDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TriggerRecordDialog(int initialTriggerChannel, int initialTriggerPolarity,
                                 int initialTriggerBuffer, QWidget *parent);

    QDialogButtonBox *buttonBox;
    int digitalInput;
    int triggerPolarity;
    int recordBuffer;

signals:

public slots:

private slots:
    void setDigitalInput(int index);
    void setTriggerPolarity(int index);
    void recordBufferSeconds(int value);

private:
    QComboBox *digitalInputComboBox;
    QComboBox *triggerPolarityComboBox;

    QSpinBox *recordBufferSpinBox;

};

#endif // TRIGGERRECORDDIALOG_H
