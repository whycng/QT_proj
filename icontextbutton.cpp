#include "icontextbutton.h"

//IconTextButton::IconTextButton()
//{

//}

IconTextButton::IconTextButton(const QString& iconPath, const QString& text, QWidget* parent)
    : QPushButton(parent)
{
    QHBoxLayout* layout = new QHBoxLayout();
    setLayout(layout);

    // 创建图标
    QLabel* iconLabel = new QLabel(this);
    iconLabel->setPixmap(QPixmap(iconPath));
    layout->addWidget(iconLabel);

    // 创建文字
    QLabel* textLabel = new QLabel(text, this);
    layout->addWidget(textLabel);

    // 设置布局
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(6);  // 调整图标和文字之间的间距

    // 移除按钮的默认的边框和背景
    setFlat(true);
    setStyleSheet("QPushButton { border: none; background: transparent; }");
}
