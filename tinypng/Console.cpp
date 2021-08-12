﻿#include "Console.h"
#include <QScrollBar>
#include <qDebug>
#include <QDesktopServices>

Console::Console(QWidget* parent)
	: QTextBrowser(parent)
{
	setMinimumHeight(100);
	setTextBackgroundColor(QColor(0, 0, 0, 0));
	setStyleSheet("QTextBrowser { \
		background-color: #000000; \
color:#FFFFFF; \
	font-size:15px;\
	font-family:\"verdana,Arial,Helvetica,sans-serif\", \
}");
	append("The image compression software is available for png/jpg/jpeg that is developed based on the apis offering by tinypng.png.");
	append("Usage:");
	append("  To compress your images, Click the button to choose or drag directly the object — some files or a folder — into the area of table widget.");
	append("Developer: yongplus@foxmail.com ");
	this->setOpenLinks(false);
	this->atBottom = true;
	connect(this, SIGNAL(textChanged()), this, SLOT(textChangedSlot()));
	connect(this, SIGNAL(infoSignal(QString)), this, SLOT(info(QString)));
	connect(this, SIGNAL(tipSignal(QString)), this, SLOT(tip(QString)));
	connect(this, SIGNAL(errorSignal(QString)), this, SLOT(error(QString)));
	connect(this, SIGNAL(anchorClicked(QUrl)), this, SLOT(clickLink(QUrl)));


}
void Console::textChangedSlot() {
	if (atBottom) {
		verticalScrollBar()->setValue(verticalScrollBar()->maximum());
	}

}
void Console::append(const QString& text) {
	//setTextColor(color);
	atBottom = false;
	if (verticalScrollBar()->maximum() - verticalScrollBar()->value() < 30) {
		atBottom = true;
	}
	//qDebug() << verticalScrollBar()->maximum() << verticalScrollBar()->value() + verticalScrollBar()->pageStep();

	QTextBrowser::append(text);


}
void Console::info(const QString& text) {

	append(QString("<span style=\"color:#17a81a\">%1</a>").arg(text));
}

void Console::tip(const QString& text) {
	append(QString("<span style=\"color:#ffffff\">%1</a>").arg(text));
}

void Console::error(QString text) {
	append(QString("<span style=\"color:#ff0000\">%1</a>").arg(text));
}

void Console::clickLink(const QUrl& link) {
	qDebug() << "点击链接" << link.toString();
	QDesktopServices::openUrl(link);
}
Console::~Console()
{
}
