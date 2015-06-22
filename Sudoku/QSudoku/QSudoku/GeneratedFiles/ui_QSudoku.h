/********************************************************************************
** Form generated from reading UI file 'QSudoku.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSUDOKU_H
#define UI_QSUDOKU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QSudokuClass
{
public:
    QAction *aExit;
    QAction *aNewGame;
    QAction *aBigBoard;
    QAction *aSmallBoard;
    QAction *aHintOneStep;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QMenuBar *menuBar;
    QMenu *mFile;
    QMenu *mConfig;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QSudokuClass)
    {
        if (QSudokuClass->objectName().isEmpty())
            QSudokuClass->setObjectName(QStringLiteral("QSudokuClass"));
        QSudokuClass->resize(720, 773);
        aExit = new QAction(QSudokuClass);
        aExit->setObjectName(QStringLiteral("aExit"));
        aNewGame = new QAction(QSudokuClass);
        aNewGame->setObjectName(QStringLiteral("aNewGame"));
        aBigBoard = new QAction(QSudokuClass);
        aBigBoard->setObjectName(QStringLiteral("aBigBoard"));
        aBigBoard->setCheckable(true);
        aBigBoard->setChecked(true);
        aSmallBoard = new QAction(QSudokuClass);
        aSmallBoard->setObjectName(QStringLiteral("aSmallBoard"));
        aSmallBoard->setCheckable(true);
        aHintOneStep = new QAction(QSudokuClass);
        aHintOneStep->setObjectName(QStringLiteral("aHintOneStep"));
        centralWidget = new QWidget(QSudokuClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        QSudokuClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QSudokuClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 720, 21));
        mFile = new QMenu(menuBar);
        mFile->setObjectName(QStringLiteral("mFile"));
        mConfig = new QMenu(menuBar);
        mConfig->setObjectName(QStringLiteral("mConfig"));
        QSudokuClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QSudokuClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QSudokuClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QSudokuClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QSudokuClass->setStatusBar(statusBar);

        menuBar->addAction(mFile->menuAction());
        menuBar->addAction(mConfig->menuAction());
        mFile->addAction(aNewGame);
        mFile->addAction(aHintOneStep);
        mFile->addSeparator();
        mFile->addAction(aExit);
        mConfig->addAction(aBigBoard);
        mConfig->addAction(aSmallBoard);

        retranslateUi(QSudokuClass);

        QMetaObject::connectSlotsByName(QSudokuClass);
    } // setupUi

    void retranslateUi(QMainWindow *QSudokuClass)
    {
        QSudokuClass->setWindowTitle(QApplication::translate("QSudokuClass", "QSudoku", 0));
        aExit->setText(QApplication::translate("QSudokuClass", "\351\233\242\351\226\213", 0));
        aNewGame->setText(QApplication::translate("QSudokuClass", "\351\226\213\345\225\237\346\226\260\345\261\200", 0));
        aNewGame->setShortcut(QApplication::translate("QSudokuClass", "Ctrl+N", 0));
        aBigBoard->setText(QApplication::translate("QSudokuClass", "\345\244\247\346\243\213\347\233\244", 0));
        aSmallBoard->setText(QApplication::translate("QSudokuClass", "\345\260\217\346\243\213\347\233\244", 0));
        aHintOneStep->setText(QApplication::translate("QSudokuClass", "\346\217\220\347\244\272\344\270\200\346\255\245", 0));
        aHintOneStep->setShortcut(QApplication::translate("QSudokuClass", "Ctrl+H", 0));
        mFile->setTitle(QApplication::translate("QSudokuClass", "\346\252\224\346\241\210", 0));
        mConfig->setTitle(QApplication::translate("QSudokuClass", "\350\250\255\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class QSudokuClass: public Ui_QSudokuClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSUDOKU_H
