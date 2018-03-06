/********************************************************************************
** Form generated from reading UI file 'planefight.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLANEFIGHT_H
#define UI_PLANEFIGHT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_planeFightClass
{
public:

    void setupUi(QWidget *planeFightClass)
    {
        if (planeFightClass->objectName().isEmpty())
            planeFightClass->setObjectName(QStringLiteral("planeFightClass"));
        planeFightClass->resize(600, 400);

        retranslateUi(planeFightClass);

        QMetaObject::connectSlotsByName(planeFightClass);
    } // setupUi

    void retranslateUi(QWidget *planeFightClass)
    {
        planeFightClass->setWindowTitle(QApplication::translate("planeFightClass", "planeFight", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class planeFightClass: public Ui_planeFightClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLANEFIGHT_H
