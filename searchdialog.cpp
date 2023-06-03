#include "searchdialog.h"
#include <QVBoxLayout>

SearchDialog::SearchDialog(QWidget *parent)
    : QDialog(parent)
{
    // Create the input field and search button
    searchInput = new QLineEdit(this);
    QPushButton *searchButton = new QPushButton("Search", this);

    // Create the canvas to display search results
    webView = new QWebView(this);

    // Connect the search button click event to the search slot
    connect(searchButton, &QPushButton::clicked, this, &SearchDialog::search);

    // Create the layout and add the widgets
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(searchInput);
    layout->addWidget(searchButton);
    layout->addWidget(webView);
    setLayout(layout);
}

void SearchDialog::search()
{
    // Get the search query from the input field
    QString searchQuery = searchInput->text();

    // Perform the search and load the results in the canvas
    webView->load("https://www.google.com/search?q=" + searchQuery);
}
