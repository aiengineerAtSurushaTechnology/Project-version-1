#include "textedit.h"
#include "ui_textedit.h"
#include <QFileDialog>
#include<QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPrintPreviewDialog>
#include <QFontDialog>
#include <QPrintPreviewWidget>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QMessageBox>
#include <QPageSetupDialog>
#include "formula_dialog.h"
#include <QRadioButton>
#include <QDialogButtonBox>
#include <QTextDocument>
#include <QSplitter>
#include <QHBoxLayout>
#include "horizontalruler.h"
#include "verticalruler.h"
#include <QScrollBar>
#include <QResizeEvent>

TextEdit::TextEdit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEdit),
    horizontalRuler(nullptr),
    verticalRuler(nullptr)
{
    ui->setupUi(this);
    //    formulaEditor = new QTextEdit(this);
    //formulaEditor->setPlaceholderText(tr("Type your formula here"));

}



TextEdit::~TextEdit()
{
    delete ui;
}

void TextEdit::on_actionNew_triggered()
{
    // Create a new empty document
    statusBar()->showMessage("Current tool is Clear");
    ui->textEdit->clear();

    // Set the document title to "Untitled"
    setWindowTitle(tr("New Type Window/Untitled"));
}


void TextEdit::on_actionCut_triggered()
{
    statusBar()->showMessage("Current tool is Cut");
    ui->textEdit->cut();
}


void TextEdit::on_actionCopy_triggered()
{
    statusBar()->showMessage("Current tool is Copy");
    ui->textEdit->copy();
}


void TextEdit::on_actionPaste_triggered()
{
    statusBar()->showMessage("Current tool is Paste");
    ui->textEdit->paste();
}


void TextEdit::on_actionUndo_triggered()
{
    statusBar()->showMessage("Current tool is Undo");
    ui->textEdit->undo();
}


void TextEdit::on_actionRedo_triggered()
{
    statusBar()->showMessage("Current tool is Redo");
    ui->textEdit->redo();
}


void TextEdit::on_actionSave_triggered()
{
    statusBar()->showMessage("Current tool is Save");
    QTextEdit *editor = qobject_cast<QTextEdit *>(centralWidget());
    if (editor) {
        QString fileName = QFileDialog::getSaveFileName(this, "Save File", QString(), "Text Files (*.txt)");
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out << editor->toPlainText();
                file.close();
            }
        }
    }
}


void TextEdit::on_actionSave_2_triggered()
{
    statusBar()->showMessage("Current tool is Save As");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File As"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    file.close();
}


void TextEdit::on_actionPrint_triggered()
{
    statusBar()->showMessage("Current tool is Print");
    QPrinter printer;
    QPrintDialog dialog(&printer, this);

    // If the user clicked "OK" on the dialog, proceed with printing
    if (dialog.exec() == QDialog::Accepted) {
        // Create a text document from the text edit content
        QTextDocument doc;
        doc.setPlainText(ui->textEdit->toPlainText());

        // Print the document to the selected printer
        doc.print(&printer);
    }
}


void TextEdit::on_actionPrint_Preview_triggered()
{
    statusBar()->showMessage("Current tool is Print Preview");
    // Create a print preview dialog
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);

    // Connect the paintRequested signal to a slot that renders the preview
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(renderPreview(QPrinter*)));

    // Show the preview dialog
    preview.exec();
}

void TextEdit::renderPreview(QPrinter *printer)
{
    // Create a text document from the text edit content
    QTextDocument doc;
    doc.setPlainText(ui->textEdit->toPlainText());

    // Print the document to the printer
    doc.print(printer);
}

void TextEdit::on_actionClose_triggered()
{
    TextEdit::close();
}

void TextEdit::on_actionFlush_Left_triggered()
{
    statusBar()->showMessage("Current tool is Left Alignment");
    ui->textEdit->setAlignment(Qt::AlignLeft);
}

void TextEdit::on_actionCentre_triggered()
{
    statusBar()->showMessage("Current tool is Centre Alignment");
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void TextEdit::on_actionFlush_Right_triggered()
{
    statusBar()->showMessage("Current tool is Right Alignment");
    ui->textEdit->setAlignment(Qt::AlignRight);
}

void TextEdit::on_actionJustified_triggered()
{
    statusBar()->showMessage("Current tool is Justify");
    ui->textEdit->setAlignment(Qt::AlignJustify);
}

void TextEdit::on_actionAutomatic_Justified_triggered()
{
    statusBar()->showMessage("Current tool is Automatic Justify");
    QTextEdit *textEdit = new QTextEdit();
    textEdit->setAlignment(Qt::AlignJustify);
}

void TextEdit::on_actionPlain_triggered()
{
    statusBar()->showMessage("Current tool is Plain text");
    QString plainText = ui->textEdit->toPlainText();
}

void TextEdit::on_actionBold_triggered()
{
    statusBar()->showMessage("Current tool is Bold");
    QTextCharFormat format;
    format.setFontWeight(ui->textEdit->fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void TextEdit::on_actionItalic_triggered()
{
    statusBar()->showMessage("Current tool is Italic");
    bool ok;
    QFont font=QFontDialog::getFont(&ok,this);
    if(ok)
    {
        ui->textEdit->setFont(font);
    }
    else return;
}

void TextEdit::on_actionUnderline_triggered()
{

    statusBar()->showMessage("Current tool is Underline");
    /*
    QTextCursor textCursor = ui->textEdit->textCursor();
    QTextCharFormat charFormat = textCursor.charFormat();

    if (charFormat.fontUnderline()) {
        charFormat.setFontUnderline(false);
    } else {
        charFormat.setFontUnderline(true);
    }

    textCursor.setCharFormat(charFormat);
    ui->textEdit->setTextCursor(textCursor);
    */
    QTextCursor textCursor = ui->textEdit->textCursor();
    QTextCharFormat charFormat = textCursor.charFormat();
    charFormat.setFontUnderline(true);
    textCursor.setCharFormat(charFormat);
    ui->textEdit->setTextCursor(textCursor);
}

void TextEdit::on_actionFormula_triggered()
{
    formula_dialog formula;
    formula.setModal(true);
    auto ret = formula.exec();
    if (ret == QDialog::Accepted) {
        QString newFormula = formula.getFrml();
        if (!newFormula.isEmpty()) {
            QTextCursor cursor = ui->textEdit->textCursor();
            cursor.insertText(newFormula);
        }
    }
}

void TextEdit::on_actionSubscript_selected_character_triggered()
{
    statusBar()->showMessage("Current tool is Subscript");
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat charFormat = cursor.charFormat();

    if (charFormat.verticalAlignment() == QTextCharFormat::AlignSubScript) {
        charFormat.setVerticalAlignment(QTextCharFormat::AlignNormal);
    } else {
        charFormat.setVerticalAlignment(QTextCharFormat::AlignSubScript);
    }

    cursor.mergeCharFormat(charFormat);
    ui->textEdit->mergeCurrentCharFormat(charFormat);
}

void TextEdit::on_actionAdds_a_degree_sign_triggered()
{
    statusBar()->showMessage("Current tool is degree sign");
    ui->textEdit->insertPlainText(QString::fromUtf8("°C"));
}

void TextEdit::on_actionClean_triggered()
{
    statusBar()->showMessage("Current tool is Clean");
    //ui->textEdit->setText("");
    ui->textEdit->clear();
}


void TextEdit::on_actionSelect_All_triggered()
{
    statusBar()->showMessage("Current tool is Select All");
    ui->textEdit->selectAll();
}

void TextEdit::on_actionBackground_Color_triggered()
{
    statusBar()->showMessage("Current tool is Background Color");
    QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
    if (color.isValid()) {
        QPalette p = ui->textEdit->palette();
        p.setColor(QPalette::Base, color);
        ui->textEdit->setPalette(p);
    }
}

void TextEdit::on_actionText_Color_triggered()
{
    statusBar()->showMessage("Current tool is Text Color");
    QColor color = QColorDialog::getColor(Qt::white,this);
    if(color.isValid())
        ui->textEdit->setTextColor(color);
}

void TextEdit::on_actionPower_off_Selected_Text_triggered()
{
    statusBar()->showMessage("Current tool is Power of");
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat charFormat = cursor.charFormat();

    if (charFormat.verticalAlignment() == QTextCharFormat::AlignSuperScript) {
        charFormat.setVerticalAlignment(QTextCharFormat::AlignNormal);
    } else {
        charFormat.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
    }

    cursor.mergeCharFormat(charFormat);
    ui->textEdit->mergeCurrentCharFormat(charFormat);
}

void TextEdit::on_actionOpen_triggered()
{
    statusBar()->showMessage("Currenting using Open text");
    QString fileName = QFileDialog::getOpenFileName(this, "Open Text Files", "", "Text Files (*.txt)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString textfile = file.readAll();
            ui->textEdit->setPlainText(textfile);
            //ui->graphicsView->setStyleSheet(styleSheet);
            file.close();
        } else {
            QMessageBox::warning(this, "Error", QString("Failed to open file %1").arg(fileName));
        }
    }
}

void TextEdit::on_actionPage_Setup_2_triggered()
{
    // Create a dialog box to display page layout options
    QDialog dialog(this);
    dialog.setWindowTitle("Page Setup");

    // Create layout for dialog box
    QVBoxLayout layout(&dialog);

    // Add radio buttons for different page layout options
    QRadioButton *portraitButton = new QRadioButton("Portrait", &dialog);
    QRadioButton *landscapeButton = new QRadioButton("Landscape", &dialog);
    QRadioButton *customButton = new QRadioButton("Custom", &dialog);

    layout.addWidget(portraitButton);
    layout.addWidget(landscapeButton);
    layout.addWidget(customButton);

    // Add OK and Cancel buttons
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    layout.addWidget(&buttonBox);

    // Connect the OK and Cancel buttons to appropriate slots
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // Show the dialog box and wait for user input
    if (dialog.exec() == QDialog::Accepted) {
        // Determine which option the user selected and take appropriate action
        if (portraitButton->isChecked()) {
            // Set page layout to portrait
            // ...
        } else if (landscapeButton->isChecked()) {
            // Set page layout to landscape
            // ...
        } else if (customButton->isChecked()) {
            // Open a custom page setup dialog box
            // ...
        }
    }
}


void TextEdit::on_actionRuler_triggered()
{
    // Check if rulers are visible
    bool rulersVisible = horizontalRuler && verticalRuler;

    if (rulersVisible) {
        // Rulers are visible, hide them
        delete horizontalRuler;
        delete verticalRuler;
        horizontalRuler = nullptr;
        verticalRuler = nullptr;

        // Adjust the size and position of the textEdit widget to occupy the full centralwidget
        ui->textEdit->setGeometry(0, 0, ui->centralwidget->width(), ui->centralwidget->height());
    } else {
        // Rulers are hidden, show them

        // Create and show the horizontal ruler
        horizontalRuler = new HorizontalRuler(ui->centralwidget);
        horizontalRuler->setOffset(ui->textEdit->horizontalScrollBar()->value());
        connect(ui->textEdit->horizontalScrollBar(), &QScrollBar::valueChanged, horizontalRuler, &HorizontalRuler::setOffset);
        horizontalRuler->show();

        // Create and show the vertical ruler
        verticalRuler = new VerticalRuler(ui->centralwidget);
        verticalRuler->setOffset(ui->textEdit->verticalScrollBar()->value());
        connect(ui->textEdit->verticalScrollBar(), &QScrollBar::valueChanged, verticalRuler, &VerticalRuler::setOffset);
        verticalRuler->show();

        // Adjust the size and position of the rulers and textEdit widget
        adjustRulerSizes();

        // Raise the rulers above the textEdit widget
        horizontalRuler->raise();
        verticalRuler->raise();
    }
}

void TextEdit::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    adjustRulerSizes();
}

void TextEdit::adjustRulerSizes()
{
    // Check if horizontalRuler and verticalRuler are valid
    if (!horizontalRuler || !verticalRuler)
        return;

    // Calculate the available space for the rulers and textEdit widget
    int spacing = 10;
    int verticalRulerWidth = verticalRuler->width();
    int horizontalRulerHeight = horizontalRuler->height();
    int availableWidth = ui->centralwidget->width() - verticalRulerWidth - spacing;
    int availableHeight = ui->centralwidget->height() - horizontalRulerHeight - spacing;

    // Set the geometry of the rulers
    horizontalRuler->setGeometry(verticalRulerWidth, 0, availableWidth, horizontalRulerHeight);
    verticalRuler->setGeometry(0, horizontalRulerHeight, verticalRulerWidth, availableHeight);

    // Calculate the adjusted size for the textEdit widget
    int textEditWidth = availableWidth - spacing;  // Subtract spacing to make the textEdit closer to the ruler
    int textEditHeight = availableHeight;

    // Check if the adjusted width exceeds the maximum width
    int maxTextEditWidth = ui->centralwidget->width() - verticalRulerWidth - spacing;
    if (textEditWidth > maxTextEditWidth)
        textEditWidth = maxTextEditWidth;

    // Check if the adjusted height exceeds the maximum height
    int maxTextEditHeight = ui->centralwidget->height() - horizontalRulerHeight - spacing;
    if (textEditHeight > maxTextEditHeight)
        textEditHeight = maxTextEditHeight;

    // Set the geometry of the textEdit widget to align with the rulers
    ui->textEdit->setGeometry(verticalRulerWidth + spacing, horizontalRulerHeight, textEditWidth, textEditHeight);
}

void TextEdit::on_actionToolbar_triggered()
{
    ui->toolBar->setHidden(!ui->toolBar->isHidden());
}

