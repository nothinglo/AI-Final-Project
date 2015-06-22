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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QNewGameDialog
{
public:
    QVBoxLayout *verticalLayout;
    QRadioButton *rAuto;
    QGroupBox *gAuto;
    QGridLayout *gridLayout;
    QComboBox *cDifficulty;
    QLabel *lDifficulty;
    QRadioButton *rManual;
    QSpacerItem *verticalSpacer;
    QPushButton *bGenerate;

    void setupUi(QWidget *QNewGameDialog)
    {
        if (QNewGameDialog->objectName().isEmpty())
            QNewGameDialog->setObjectName(QStringLiteral("QNewGameDialog"));
        QNewGameDialog->resize(353, 268);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font.setPointSize(12);
        QNewGameDialog->setFont(font);
        verticalLayout = new QVBoxLayout(QNewGameDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        rAuto = new QRadioButton(QNewGameDialog);
        rAuto->setObjectName(QStringLiteral("rAuto"));
        rAuto->setChecked(true);

        verticalLayout->addWidget(rAuto);

        gAuto = new QGroupBox(QNewGameDialog);
        gAuto->setObjectName(QStringLiteral("gAuto"));
        gAuto->setMinimumSize(QSize(0, 150));
        gridLayout = new QGridLayout(gAuto);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        cDifficulty = new QComboBox(gAuto);
        cDifficulty->setObjectName(QStringLiteral("cDifficulty"));

        gridLayout->addWidget(cDifficulty, 0, 1, 1, 1);

        lDifficulty = new QLabel(gAuto);
        lDifficulty->setObjectName(QStringLiteral("lDifficulty"));
        lDifficulty->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lDifficulty, 0, 0, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 2);

        verticalLayout->addWidget(gAuto);

        rManual = new QRadioButton(QNewGameDialog);
        rManual->setObjectName(QStringLiteral("rManual"));

        verticalLayout->addWidget(rManual);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        bGenerate = new QPushButton(QNewGameDialog);
        bGenerate->setObjectName(QStringLiteral("bGenerate"));
        bGenerate->setFont(font);

        verticalLayout->addWidget(bGenerate);


        retranslateUi(QNewGameDialog);

        QMetaObject::connectSlotsByName(QNewGameDialog);
    } // setupUi

    void retranslateUi(QWidget *QNewGameDialog)
    {
        QNewGameDialog->setWindowTitle(QApplication::translate("QNewGameDialog", "QNewGameDialog", 0));
        rAuto->setText(QApplication::translate("QNewGameDialog", "\350\207\252\345\213\225\345\207\272\351\241\214", 0));
        gAuto->setTitle(QString());
        cDifficulty->clear();
        cDifficulty->insertItems(0, QStringList()
         << QApplication::translate("QNewGameDialog", "\345\210\235\347\264\232", 0)
         << QApplication::translate("QNewGameDialog", "\344\270\255\347\264\232", 0)
         << QApplication::translate("QNewGameDialog", "\351\253\230\347\264\232", 0)
         << QApplication::translate("QNewGameDialog", "\351\255\224\347\216\213\347\264\232", 0)
        );
        lDifficulty->setText(QApplication::translate("QNewGameDialog", "\351\233\243\345\272\246", 0));
        rManual->setText(QApplication::translate("QNewGameDialog", "\346\211\213\345\213\225\345\207\272\351\241\214", 0));
        bGenerate->setText(QApplication::translate("QNewGameDialog", "Generate", 0));
    } // retranslateUi

};

namespace Ui {
    class QNewGameDialog: public Ui_QNewGameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QNEWGAMEDIALOG_H
