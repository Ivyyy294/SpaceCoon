#ifndef MENUE_H
#define MENUE_H
#include "LarasEngine.h"
#include "ui_Menue.h"

using namespace LarasEngine;

class Menue : public QDialog
{
	Q_OBJECT

public:
	Menue(QWidget *parent = 0);
	~Menue() {};

	inline GameStatus GetExitCode() const { return exitCode; };
private:
	Ui::Dialog ui;
	GameStatus exitCode;

public slots:
	void on_pushButtonExit_pressed();
	void on_pushButtonSinglePlayer_pressed();
	void on_pushButtonTwoPlayers_pressed();
	void on_pushButtonScore_pressed ();
};

#endif // MENUE_H
