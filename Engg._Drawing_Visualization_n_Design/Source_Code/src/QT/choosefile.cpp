#include "include/QT/choosefile.h"
#include "ui_choosefile.h"
#include "include/QT/inputmode.h"

#include "include/3D/threeDObject.h"
#include "include/3D/threeDInput.h"
#include "include/2D/twoDProjection.h"
#include "include/2D/twoDInput.h"

#include <QFileDialog>
#include <QMessageBox>

ChooseFile::ChooseFile(int mode, QWidget *parent) : QWidget(parent),
                                                    ui(new Ui::ChooseFile)
{
    ui->setupUi(this);

    setWindowTitle(tr("Open File"));

    switch (mode)
    {
    case 1:
        type = "2D Projection (*.cop2DProj)";
        break;
    case 2:
        type = "2D Orthographic Views (*.cop2D)";
        break;
    default:
        type = "3D File (*.cop3D)";
    }

    ui->label->setText("Please choose an \"" + type + "\" file:");

    this->mode = mode;
}

ChooseFile::~ChooseFile()
{
    delete ui;
}

void ChooseFile::on_select_File_clicked()
{
    // Open a Select File Menu
    QString filename = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        ".",
        type);

    if (filename == "")
    {
        QMessageBox::information(this, tr("Warning"), "Please Choose a File");
    }
    else
    {
        // QMessageBox::information(this, tr("File Name"), "You have chosen: " + filename);
        if (QMessageBox::Yes == QMessageBox::question(this, "File Name", "You have chosen: " + filename + "\nContinue?", QMessageBox::Yes | QMessageBox::No))
        {
            // Approved File Opening, Go Ahead
            threeDInput input3d;
            twoDInput input2d;

            switch (mode)
            {
            case 3:
                input3d.inputData(qPrintable(filename));
                chosenObject(input3d.get3DObject());
                break;
            default:
                chosenProjection(input2d.getProjectionDrawing(qPrintable(filename)));
            }

            // Destroy itself
            this->~ChooseFile();
        }
    }
}

void ChooseFile::chosenObject(threeDObject *object)
{
    // Chosen Object
}

void ChooseFile::chosenProjection(twoDProjectionView *projection)
{
    // Chosen Projection
}

void ChooseFile::on_Cancel_clicked()
{
    // The User does not want to open File, go back
    InputMode *input_mode = new InputMode(mode);
    input_mode->show();

    this->~ChooseFile();
}
