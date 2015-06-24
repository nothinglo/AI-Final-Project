/********************************************************************************
** Form generated from reading UI file 'QNewGameDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QNEWGAMEDIALOG_H
#define UI_QNEWGAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QNewGameDialog
{
public:
    QGridLayout *gridLayout_2;
    QRadioButton *rAuto;
    QRadioButton *rManual;
    QPushButton *bGenerate;
    QComboBox *cDifficulty;
    QSpacerItem *verticalSpacer;
    QRadioButton *rClues;
    QSpinBox *cClueCount;

    void setupUi(QWidget *QNewGameDialog)
    {
        if (QNewGameDialog->objectName().isEmpty())
            QNewGameDialog->setObjectName(QStringLiteral("QNewGameDialog"));
        QNewGameDialog->resize(353, 146);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font.setPointSize(12);
        QNewGameDialog->setFont(font);
        gridLayout_2 = new QGridLayout(QNewGameDialog);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        rAuto = new QRadioButton(QNewGameDialog);
        rAuto->setObjectName(QStringLiteral("rAuto"));
        rAuto->setChecked(true);

        gridLayout_2->addWidget(rAuto, 0, 0, 1, 1);

        rManual = new QRadioButton(QNewGameDialog);
        rManual->setObjectName(QStringLiteral("rManual"));

        gridLayout_2->addWidget(rManual, 2, 0, 1, 2);

        bGenerate = new QPushButton(QNewGameDialog);
        bGenerate->setObjectName(QStringLiteral("bGenerate"));
        bGenerate->setFont(font);

        gridLayout_2->addWidget(bGenerate, 6, 0, 1, 2);

        cDifficulty = new QComboBox(QNewGameDialog);
        cDifficulty->setObjectName(QStringLiteral("cDifficulty"));

        gridLayout_2->addWidget(cDifficulty, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 5, 0, 1, 2);

        rClues = new QRadioButton(QNewGameDialog);
        rClues->setObjectName(QStringLiteral("rClues"));

        gridLayout_2->addWidget(rClues, 1, 0, 1, 1);

        cClueCount = new QSpinBox(QNewGameDialog);
        cClueCount->setObjectName(QStringLiteral("cClueCount"));
        cClueCount->setMinimum(19);
        cClueCount->setMaximum(80);

        gridLayout_2->addWidget(cClueCount, 1, 1, 1, 1);


        retranslateUi(QNewGameDialog);

        QMetaObject::connectSlotsByName(QNewGameDialog);
    } // setupUi

    void retranslateUi(QWidget *QNewGameDialog)
    {
        QNewGameDialog->setWindowTitle(QApplication::translate("QNewGameDialog", "QNewGameDialog", 0));
        rAuto->setText(QApplication::translate("QNewGameDialog", "\350\207\252\345\213\225\345\207\272\351\241\214", 0));
        rManual->setText(QApplication::translate("QNewGameDialog", "\346\211\213\345\213\225\345\207\272\351\241\214", 0));
        bGenerate->setText(QApplication::translate("QNewGameDialog", "Generate", 0));
        cDifficulty->clear();
        cDifficulty->insertItems(0, QStringList()
         << QApplication::translate("QNewGameDialog", "\345\210\235\347\264\232", 0)
         << QApplication::translate("QNewGameDialog", "\344\270\255\347\264\232", 0)
         << QApplication::translate("QNewGameDialog", "\351\253\230\347\264\232", 0)
         << QApplication::translate("QNewGameDialog", "\351\255\224\347\216\213\347\264\232", 0)
        );
        rClues->setText(QApplication::translate("QNewGameDialog", "\350\207\252\350\250\202\346\240\274\345\255\220\346\225\270", 0));
    } // retranslateUi

};

namespace Ui {
    class QNewGameDialog: public Ui_QNewGameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QNEWGAMEDIALOG_H
