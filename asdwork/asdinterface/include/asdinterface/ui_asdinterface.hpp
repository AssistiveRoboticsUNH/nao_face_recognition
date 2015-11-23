#ifndef UI_ASDINTERFACE_H
#define UI_ASDINTERFACE_H

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QLCDNumber>
#include <QPushButton>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_ASDInterface {

	public:

        /***************************************/

        // Initialize buttons and clock
        QPushButton *WhoAmI;
		QPushButton *LearnName;
		QPushButton *LearnFace;
		QPushButton *Start;
		QPushButton *ShutDown;
		QLCDNumber *MyClock;
	
        /***************************************/

        void setupUi(QWidget *ASDInterface) {
		
            /***************************************/

            // Create and size window    
            
            if(ASDInterface->objectName().isEmpty()) {
				ASDInterface->setObjectName(QString("ASDInterface"));
            }

			ASDInterface->resize(800, 400);

            /***************************************/

            // Create and position who am i button

			WhoAmI = new QPushButton(ASDInterface);
			WhoAmI->setObjectName(QString("WhoAmI"));
			WhoAmI->setGeometry(QRect(550, 50, 200, 80)); 
	
            /***************************************/

            // Create and position clock

            MyClock = new QLCDNumber(ASDInterface);
			MyClock->setObjectName(QString("MyClock"));
			MyClock->setGeometry(QRect(570, 145, 160, 105));
		
            /***************************************/

            // Create and position learn name button

            LearnName = new QPushButton(ASDInterface);
			LearnName->setObjectName(QString("LearnName"));
			LearnName->setGeometry(QRect(550, 265, 200, 40));
	
            /***************************************/

            // Create and position learn face button

            LearnFace = new QPushButton(ASDInterface);
			LearnFace->setObjectName(QString("LearnFace"));
			LearnFace->setGeometry(QRect(550, 310, 200, 40));
	
            /***************************************/

            // Create and position start button

            Start = new QPushButton(ASDInterface);
			Start->setObjectName(QString("Start"));
			Start->setGeometry(QRect(50, 30, 425, 40));
	
            /***************************************/

            // Create and position shutdown button

            ShutDown = new QPushButton(ASDInterface);
			ShutDown->setObjectName(QString("ShutDown"));
			ShutDown->setGeometry(QRect(50, 330, 425, 40));
	
            /***************************************/

            // Polish it all off
			retranslateUi(ASDInterface);
			QMetaObject::connectSlotsByName(ASDInterface);
	
            /***************************************/

        }

        /***************************************/

        // Name window and buttons    
		void retranslateUi(QWidget *ASDInterface){
			ASDInterface->setWindowTitle(QApplication::translate("ASDInterface", "ASDInterface", 0));
			WhoAmI->setText(QApplication::translate("ASDInterface", "Who Am I?", 0));
			LearnName->setText(QApplication::translate("ASDInterface", "Learn Name", 0));
			LearnFace->setText(QApplication::translate("ASDInterface", "Learn Face", 0));
			Start->setText(QApplication::translate("ASDInterface", "Start", 0));
			ShutDown->setText(QApplication::translate("ASDInterface", "Shut Down", 0));
		}

        /***************************************/

};

namespace Ui{
	class ASDInterface: public Ui_ASDInterface {};
}

QT_END_NAMESPACE

#endif
