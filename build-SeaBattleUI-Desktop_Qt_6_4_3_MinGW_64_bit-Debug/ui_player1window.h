/********************************************************************************
** Form generated from reading UI file 'player1window.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYER1WINDOW_H
#define UI_PLAYER1WINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Player1Window
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_3;
    QVBoxLayout *column5Me;
    QVBoxLayout *column3Me;
    QVBoxLayout *column9Me;
    QVBoxLayout *column7Me;
    QVBoxLayout *column4Me;
    QVBoxLayout *column1Me;
    QVBoxLayout *column8Me;
    QVBoxLayout *column2Me;
    QVBoxLayout *column6Me;
    QVBoxLayout *column_10Me;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_11;
    QPushButton *pushButton_10;
    QLabel *label_2;
    QLabel *label_5;
    QGridLayout *gridLayout_2;
    QVBoxLayout *column5Enemy;
    QVBoxLayout *column7Enemy;
    QVBoxLayout *column4Enemy;
    QVBoxLayout *column3Enemy;
    QVBoxLayout *column1Enemy;
    QVBoxLayout *column8Enemy;
    QVBoxLayout *column2Enemy;
    QVBoxLayout *column_10Enemy;
    QVBoxLayout *column9Enemy;
    QVBoxLayout *column6Enemy;

    void setupUi(QDialog *Player1Window)
    {
        if (Player1Window->objectName().isEmpty())
            Player1Window->setObjectName("Player1Window");
        Player1Window->resize(989, 522);
        Player1Window->setMaximumSize(QSize(1312435, 5125327));
        gridLayout = new QGridLayout(Player1Window);
        gridLayout->setObjectName("gridLayout");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setHorizontalSpacing(2);
        gridLayout_3->setVerticalSpacing(7);
        column5Me = new QVBoxLayout();
        column5Me->setSpacing(2);
        column5Me->setObjectName("column5Me");

        gridLayout_3->addLayout(column5Me, 1, 4, 1, 1);

        column3Me = new QVBoxLayout();
        column3Me->setSpacing(2);
        column3Me->setObjectName("column3Me");

        gridLayout_3->addLayout(column3Me, 1, 2, 1, 1);

        column9Me = new QVBoxLayout();
        column9Me->setSpacing(2);
        column9Me->setObjectName("column9Me");

        gridLayout_3->addLayout(column9Me, 1, 8, 1, 1);

        column7Me = new QVBoxLayout();
        column7Me->setSpacing(2);
        column7Me->setObjectName("column7Me");

        gridLayout_3->addLayout(column7Me, 1, 6, 1, 1);

        column4Me = new QVBoxLayout();
        column4Me->setSpacing(2);
        column4Me->setObjectName("column4Me");

        gridLayout_3->addLayout(column4Me, 1, 3, 1, 1);

        column1Me = new QVBoxLayout();
        column1Me->setSpacing(2);
        column1Me->setObjectName("column1Me");

        gridLayout_3->addLayout(column1Me, 1, 0, 1, 1);

        column8Me = new QVBoxLayout();
        column8Me->setSpacing(2);
        column8Me->setObjectName("column8Me");

        gridLayout_3->addLayout(column8Me, 1, 7, 1, 1);

        column2Me = new QVBoxLayout();
        column2Me->setSpacing(2);
        column2Me->setObjectName("column2Me");

        gridLayout_3->addLayout(column2Me, 1, 1, 1, 1);

        column6Me = new QVBoxLayout();
        column6Me->setSpacing(2);
        column6Me->setObjectName("column6Me");

        gridLayout_3->addLayout(column6Me, 1, 5, 1, 1);

        column_10Me = new QVBoxLayout();
        column_10Me->setSpacing(2);
        column_10Me->setObjectName("column_10Me");

        gridLayout_3->addLayout(column_10Me, 1, 9, 1, 1);


        gridLayout->addLayout(gridLayout_3, 3, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(Player1Window);
        label->setObjectName("label");
        QFont font;
        font.setFamilies({QString::fromUtf8("Terminal")});
        font.setPointSize(7);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        label_3 = new QLabel(Player1Window);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        horizontalLayout->addWidget(label_3);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalSpacer = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_11 = new QPushButton(Player1Window);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_11->sizePolicy().hasHeightForWidth());
        pushButton_11->setSizePolicy(sizePolicy);
        pushButton_11->setFont(font);
        pushButton_11->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_11->setLocale(QLocale(QLocale::Ukrainian, QLocale::Ukraine));
        pushButton_11->setCheckable(false);

        horizontalLayout_2->addWidget(pushButton_11);


        gridLayout->addLayout(horizontalLayout_2, 4, 0, 1, 2);

        pushButton_10 = new QPushButton(Player1Window);
        pushButton_10->setObjectName("pushButton_10");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Terminal")});
        pushButton_10->setFont(font1);
        pushButton_10->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(pushButton_10, 5, 0, 1, 2);

        label_2 = new QLabel(Player1Window);
        label_2->setObjectName("label_2");
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_5 = new QLabel(Player1Window);
        label_5->setObjectName("label_5");
        label_5->setFont(font1);
        label_5->setTextFormat(Qt::AutoText);

        gridLayout->addWidget(label_5, 0, 1, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        column5Enemy = new QVBoxLayout();
        column5Enemy->setObjectName("column5Enemy");

        gridLayout_2->addLayout(column5Enemy, 0, 4, 1, 1);

        column7Enemy = new QVBoxLayout();
        column7Enemy->setObjectName("column7Enemy");

        gridLayout_2->addLayout(column7Enemy, 0, 6, 1, 1);

        column4Enemy = new QVBoxLayout();
        column4Enemy->setObjectName("column4Enemy");

        gridLayout_2->addLayout(column4Enemy, 0, 3, 1, 1);

        column3Enemy = new QVBoxLayout();
        column3Enemy->setObjectName("column3Enemy");

        gridLayout_2->addLayout(column3Enemy, 0, 2, 1, 1);

        column1Enemy = new QVBoxLayout();
        column1Enemy->setObjectName("column1Enemy");

        gridLayout_2->addLayout(column1Enemy, 0, 0, 1, 1);

        column8Enemy = new QVBoxLayout();
        column8Enemy->setObjectName("column8Enemy");

        gridLayout_2->addLayout(column8Enemy, 0, 7, 1, 1);

        column2Enemy = new QVBoxLayout();
        column2Enemy->setObjectName("column2Enemy");

        gridLayout_2->addLayout(column2Enemy, 0, 1, 1, 1);

        column_10Enemy = new QVBoxLayout();
        column_10Enemy->setObjectName("column_10Enemy");

        gridLayout_2->addLayout(column_10Enemy, 0, 9, 1, 1);

        column9Enemy = new QVBoxLayout();
        column9Enemy->setObjectName("column9Enemy");

        gridLayout_2->addLayout(column9Enemy, 0, 8, 1, 1);

        column6Enemy = new QVBoxLayout();
        column6Enemy->setObjectName("column6Enemy");

        gridLayout_2->addLayout(column6Enemy, 0, 5, 1, 1);


        gridLayout->addLayout(gridLayout_2, 3, 1, 1, 1);


        retranslateUi(Player1Window);

        QMetaObject::connectSlotsByName(Player1Window);
    } // setupUi

    void retranslateUi(QDialog *Player1Window)
    {
        Player1Window->setWindowTitle(QCoreApplication::translate("Player1Window", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Player1Window", "Number of unplaced ship cells left:", nullptr));
        label_3->setText(QCoreApplication::translate("Player1Window", "5", nullptr));
        pushButton_11->setText(QCoreApplication::translate("Player1Window", "Place ship", nullptr));
        pushButton_10->setText(QCoreApplication::translate("Player1Window", "Shoot", nullptr));
        label_2->setText(QCoreApplication::translate("Player1Window", "Your board", nullptr));
        label_5->setText(QCoreApplication::translate("Player1Window", "Enemy's board", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Player1Window: public Ui_Player1Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYER1WINDOW_H
