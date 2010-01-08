/********************************************************************
* Copyright (C) PanteR
*-------------------------------------------------------------------
*
* QDBFRedactor is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* QDBFRedactor is distributed in the hope that it will be
* useful, but WITHOUT ANY WARRANTY; without even the implied
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Panther Commander; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor,
* Boston, MA 02110-1301 USA
*-------------------------------------------------------------------
* Project:		QDBFRedactor
* Author:		PanteR
* Contact:		panter.dsd@gmail.com
*******************************************************************/

#include <QtCore/QBitArray>

#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QComboBox>
#include <QtGui/QToolButton>
#include <QtGui/QGridLayout>
#include <QtGui/QColorDialog>
#include <QtGui/QFontDialog>
#include <QtGui/QtEvents>

#include "displaypreferences.h"

DisplayPreferences::DisplayPreferences(QWidget *parent)
	:AbstractPreferencesPage(parent)
{
	delegatePreferencesGroup = new QGroupBox(this);

	cellType = new QLabel(this);
	cellType->setAlignment(Qt::AlignHCenter);
	cellAlignment = new QLabel(this);
	cellAlignment->setAlignment(Qt::AlignHCenter);
	cellColor = new QLabel(this);
	cellColor->setAlignment(Qt::AlignHCenter);
	cellFont = new QLabel(this);
	cellFont->setAlignment(Qt::AlignHCenter);

	stringColorLabel = new QLabel(this);

	stringAligmentEdit = new QComboBox(this);
	connect(stringAligmentEdit, SIGNAL(currentIndexChanged(int)), this, SIGNAL(modified()));
	stringAligmentEdit->insertItem(0, "", Qt::AlignLeft);
	stringAligmentEdit->insertItem(1, "", Qt::AlignHCenter);
	stringAligmentEdit->insertItem(2, "", Qt::AlignRight);
	stringAligmentEdit->insertItem(3, "", Qt::AlignJustify);

	stringColorButton = new QToolButton(this);
	stringColorButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	stringColorButton->setAutoRaise(true);
	connect(stringColorButton, SIGNAL(clicked()), this, SLOT(setButtonColor()));

	stringFontButton = new QToolButton(this);
	stringFontButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	stringFontButton->setAutoRaise(true);
	connect(stringFontButton, SIGNAL(clicked()), this, SLOT(setButtonFont()));

	numericColorLabel = new QLabel(this);

	numericAligmentEdit = new QComboBox(this);
	connect(numericAligmentEdit, SIGNAL(currentIndexChanged(int)), this, SIGNAL(modified()));
	numericAligmentEdit->insertItem(0, "", Qt::AlignLeft);
	numericAligmentEdit->insertItem(1, "", Qt::AlignHCenter);
	numericAligmentEdit->insertItem(2, "", Qt::AlignRight);
	numericAligmentEdit->insertItem(3, "", Qt::AlignJustify);

	numericColorButton = new QToolButton(this);
	numericColorButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	numericColorButton->setAutoRaise(true);
	connect(numericColorButton, SIGNAL(clicked()), this, SLOT(setButtonColor()));

	numericFontButton = new QToolButton(this);
	numericFontButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	numericFontButton->setAutoRaise(true);
	connect(numericFontButton, SIGNAL(clicked()), this, SLOT(setButtonFont()));

	memoColorLabel = new QLabel(this);

	memoAligmentEdit = new QComboBox(this);
	connect(memoAligmentEdit, SIGNAL(currentIndexChanged(int)), this, SIGNAL(modified()));
	memoAligmentEdit->insertItem(0, "", Qt::AlignLeft);
	memoAligmentEdit->insertItem(1, "", Qt::AlignHCenter);
	memoAligmentEdit->insertItem(2, "", Qt::AlignRight);
	memoAligmentEdit->insertItem(3, "", Qt::AlignJustify);

	memoColorButton = new QToolButton(this);
	memoColorButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	memoColorButton->setAutoRaise(true);
	connect(memoColorButton, SIGNAL(clicked()), this, SLOT(setButtonColor()));

	memoFontButton = new QToolButton(this);
	memoFontButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	memoFontButton->setAutoRaise(true);
	connect(memoFontButton, SIGNAL(clicked()), this, SLOT(setButtonFont()));

	dateColorLabel = new QLabel(this);

	dateAligmentEdit = new QComboBox(this);
	connect(dateAligmentEdit, SIGNAL(currentIndexChanged(int)), this, SIGNAL(modified()));
	dateAligmentEdit->insertItem(0, "", Qt::AlignLeft);
	dateAligmentEdit->insertItem(1, "", Qt::AlignHCenter);
	dateAligmentEdit->insertItem(2, "", Qt::AlignRight);
	dateAligmentEdit->insertItem(3, "", Qt::AlignJustify);

	dateColorButton = new QToolButton(this);
	dateColorButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	dateColorButton->setAutoRaise(true);
	connect(dateColorButton, SIGNAL(clicked()), this, SLOT(setButtonColor()));

	dateFontButton = new QToolButton(this);
	dateFontButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	dateFontButton->setAutoRaise(true);
	connect(dateFontButton, SIGNAL(clicked()), this, SLOT(setButtonFont()));

	floatColorLabel = new QLabel(this);

	floatAligmentEdit = new QComboBox(this);
	connect(floatAligmentEdit, SIGNAL(currentIndexChanged(int)), this, SIGNAL(modified()));
	floatAligmentEdit->insertItem(0, "", Qt::AlignLeft);
	floatAligmentEdit->insertItem(1, "", Qt::AlignHCenter);
	floatAligmentEdit->insertItem(2, "", Qt::AlignRight);
	floatAligmentEdit->insertItem(3, "", Qt::AlignJustify);

	floatColorButton = new QToolButton(this);
	floatColorButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	floatColorButton->setAutoRaise(true);
	connect(floatColorButton, SIGNAL(clicked()), this, SLOT(setButtonColor()));

	floatFontButton = new QToolButton(this);
	floatFontButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	floatFontButton->setAutoRaise(true);
	connect(floatFontButton, SIGNAL(clicked()), this, SLOT(setButtonFont()));

	QGridLayout *colorLayout = new QGridLayout();
	colorLayout->addWidget(cellType, 0, 0);
	colorLayout->addWidget(cellAlignment, 0, 1);
	colorLayout->addWidget(cellColor, 0, 2);
	colorLayout->addWidget(cellFont, 0, 3);
	colorLayout->addWidget(stringColorLabel, 1, 0);
	colorLayout->addWidget(stringAligmentEdit, 1, 1);
	colorLayout->addWidget(stringColorButton, 1, 2, Qt::AlignHCenter);
	colorLayout->addWidget(stringFontButton, 1, 3, Qt::AlignHCenter);
	colorLayout->addWidget(numericColorLabel, 2, 0);
	colorLayout->addWidget(numericAligmentEdit, 2, 1);
	colorLayout->addWidget(numericColorButton, 2, 2, Qt::AlignHCenter);
	colorLayout->addWidget(numericFontButton, 2, 3, Qt::AlignHCenter);
	colorLayout->addWidget(memoColorLabel, 3, 0);
	colorLayout->addWidget(memoAligmentEdit, 3, 1);
	colorLayout->addWidget(memoColorButton, 3, 2, Qt::AlignHCenter);
	colorLayout->addWidget(memoFontButton, 3, 3, Qt::AlignHCenter);
	colorLayout->addWidget(dateColorLabel, 4, 0);
	colorLayout->addWidget(dateAligmentEdit, 4, 1);
	colorLayout->addWidget(dateColorButton, 4, 2, Qt::AlignHCenter);
	colorLayout->addWidget(dateFontButton, 4, 3, Qt::AlignHCenter);
	colorLayout->addWidget(floatColorLabel, 5, 0);
	colorLayout->addWidget(floatAligmentEdit, 5, 1);
	colorLayout->addWidget(floatColorButton, 5, 2, Qt::AlignHCenter);
	colorLayout->addWidget(floatFontButton, 5, 3, Qt::AlignHCenter);

	delegatePreferencesGroup->setLayout(colorLayout);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(delegatePreferencesGroup);
	mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::Expanding));
	setLayout(mainLayout);

	retranslateStrings();
	loadSettings();
}

void DisplayPreferences::retranslateStrings()
{
	delegatePreferencesGroup->setTitle(tr("Cells view preference"));

	cellType->setText(tr("Cell type"));
	cellAlignment->setText(tr("Alignment"));
	cellColor->setText(tr("Text color"));
	cellFont->setText(tr("Text font"));

	stringColorLabel->setText(tr("String"));
	stringColorButton->setText(tr("Color"));
	stringFontButton->setText(tr("Font"));

	numericColorLabel->setText(tr("Numeric"));
	numericColorButton->setText(tr("Color"));
	numericFontButton->setText(tr("Font"));

	memoColorLabel->setText(tr("Memo"));
	memoColorButton->setText(tr("Color"));
	memoFontButton->setText(tr("Font"));

	dateColorLabel->setText(tr("Date"));
	dateColorButton->setText(tr("Color"));
	dateFontButton->setText(tr("Font"));

	floatColorLabel->setText(tr("Float"));
	floatColorButton->setText(tr("Color"));
	floatFontButton->setText(tr("Font"));

	foreach(QComboBox *comboBox, delegatePreferencesGroup->findChildren<QComboBox*> ()) {
		comboBox->setItemText(0, tr("Align left"));
		comboBox->setItemText(1, tr("Align center"));
		comboBox->setItemText(2, tr("Align right"));
		comboBox->setItemText(3, tr("Align justify"));
	}
}

bool DisplayPreferences::event(QEvent *ev)
{
	if (ev->type() == QEvent::LanguageChange) {
		retranslateStrings();
	}

	return QWidget::event(ev);
}

void DisplayPreferences::saveSettings()
{
	QSettings settings;

	settings.beginGroup("Display");
	settings.setValue("String_Alignment", stringAligmentEdit->itemData(stringAligmentEdit->currentIndex()));
	settings.setValue("Numeric_Alignment", numericAligmentEdit->itemData(numericAligmentEdit->currentIndex()));
	settings.setValue("Memo_Alignment", memoAligmentEdit->itemData(memoAligmentEdit->currentIndex()));
	settings.setValue("Date_Alignment", dateAligmentEdit->itemData(dateAligmentEdit->currentIndex()));
	settings.setValue("Float_Alignment", floatAligmentEdit->itemData(floatAligmentEdit->currentIndex()));

	settings.setValue("String_Color", stringColorButton->palette().color(QPalette::ButtonText));
	settings.setValue("Numeric_Color", numericColorButton->palette().color(QPalette::ButtonText));
	settings.setValue("Memo_Color", memoColorButton->palette().color(QPalette::ButtonText));
	settings.setValue("Date_Color", dateColorButton->palette().color(QPalette::ButtonText));
	settings.setValue("Float_Color", floatColorButton->palette().color(QPalette::ButtonText));

	settings.setValue("String_Font", stringFontButton->font());
	settings.setValue("Numeric_Font", numericFontButton->font());
	settings.setValue("Memo_Font", memoFontButton->font());
	settings.setValue("Date_Font", dateFontButton->font());
	settings.setValue("Float_Font", floatFontButton->font());

	settings.endGroup();
}

void DisplayPreferences::loadSettings()
{
	QSettings settings;

	settings.beginGroup("Display");
	stringAligmentEdit->setCurrentIndex(stringAligmentEdit->findData(settings.value("String_Alignment", Qt::AlignLeft).toInt()));
	numericAligmentEdit->setCurrentIndex(numericAligmentEdit->findData(settings.value("Numeric_Alignment", Qt::AlignLeft).toInt()));
	memoAligmentEdit->setCurrentIndex(memoAligmentEdit->findData(settings.value("Memo_Alignment", Qt::AlignLeft).toInt()));
	dateAligmentEdit->setCurrentIndex(dateAligmentEdit->findData(settings.value("Date_Alignment", Qt::AlignLeft).toInt()));
	floatAligmentEdit->setCurrentIndex(floatAligmentEdit->findData(settings.value("Float_Alignment", Qt::AlignLeft).toInt()));

	QPalette m_palette;

	m_palette = palette();
	m_palette.setColor(QPalette::ButtonText, settings.value("String_Color", m_palette.color(QPalette::ButtonText)).value<QColor>());
	stringColorButton->setPalette(m_palette);

	m_palette = palette();
	m_palette.setColor(QPalette::ButtonText, settings.value("Numeric_Color", m_palette.color(QPalette::ButtonText)).value<QColor>());
	numericColorButton->setPalette(m_palette);

	m_palette = palette();
	m_palette.setColor(QPalette::ButtonText, settings.value("Memo_Color", m_palette.color(QPalette::ButtonText)).value<QColor>());
	memoColorButton->setPalette(m_palette);

	m_palette = palette();
	m_palette.setColor(QPalette::ButtonText, settings.value("Date_Color", m_palette.color(QPalette::ButtonText)).value<QColor>());
	dateColorButton->setPalette(m_palette);

	m_palette = palette();
	m_palette.setColor(QPalette::ButtonText, settings.value("Float_Color", m_palette.color(QPalette::ButtonText)).value<QColor>());
	floatColorButton->setPalette(m_palette);

	stringFontButton->setFont(settings.value("String_Font", font()).value<QFont>());
	numericFontButton->setFont(settings.value("Numeric_Font", font()).value<QFont>());
	memoFontButton->setFont(settings.value("Memo_Font", font()).value<QFont>());
	dateFontButton->setFont(settings.value("Date_Font", font()).value<QFont>());
	floatFontButton->setFont(settings.value("Float_Font", font()).value<QFont>());

	settings.endGroup();
}

void DisplayPreferences::setDefaults()
{

}

void DisplayPreferences::setButtonColor()
{
	QToolButton *button = qobject_cast<QToolButton*> (sender());
	if (!button)
		return;

	QPalette palette = button->palette();

	QColor color = QColorDialog::getColor(palette.color(QPalette::ButtonText), this);

	if (color.isValid())
		palette.setColor(QPalette::ButtonText, color);

	if (palette != button->palette()) {
		button->setPalette(palette);
		emit modified();
	}
}

void DisplayPreferences::setButtonFont()
{
	QToolButton *button = qobject_cast<QToolButton*> (sender());
	if (!button)
		return;

	bool ok = false;
	QFont font = QFontDialog::getFont(&ok, button->font(), this);

	if (ok && font != button->font()) {
		button->setFont(font);
		emit modified();
	}


}