//#ifndef ICONTEXTBUTTON_H
//#define ICONTEXTBUTTON_H


//class IconTextButton
//{
//public:
//    IconTextButton();
//};

//#endif // ICONTEXTBUTTON_H



#ifndef ICONTEXTBUTTON_H
#define ICONTEXTBUTTON_H

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
class IconTextButton : public QPushButton
{
public:
    IconTextButton(const QString& iconPath, const QString& text, QWidget* parent = nullptr);
};

#endif // ICONTEXTBUTTON_H
