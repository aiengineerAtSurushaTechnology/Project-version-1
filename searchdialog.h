#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QWebEngineView>

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    SearchDialog(QWidget *parent = nullptr);

private slots:
    void search();

private:
    QLineEdit *searchInput;
    QWebView *webView;
};

#endif // SEARCHDIALOG_H
