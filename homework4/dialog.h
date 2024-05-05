#ifndef DIALOG_H
#define DIALOG_H
#include<QGroupBox>
#include <QDialog>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QCheckBox>
#include<QComboBox>
#include<QPushButton>
#include<QFormLayout>
#include<QLineEdit>
#include<QDialogButtonBox>
#include<QTextEdit>
#include<QFont>
#include<QFileDialog>
#include<QList>
#include<QMessageBox>
#include<QRandomGenerator>
#include<QStack>
#include<QMap>
#include<QChar>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    void initializeUI();
    void genSuffixExp(QList<char> op,bool f,bool bracket,int maxnum,int number,QString addr);
    QString getInfixExp(QString exp,bool bracket);
    void handleOuput(QString exp,QString addr);
    double generateNumber(bool useFloat,int maxnum,int minnum);
    void handlePrinter(QString exp);
    QMap<QChar,int>priority;

    QFormLayout* formLayout;
    QLineEdit* qnumEdit;
    QLineEdit* qmaxnumEdit;
    QLineEdit* quantityEdit;
    QComboBox* qoutputBox;
    QDialogButtonBox* buttonBox;
    QTextEdit* textEdit;
    QVBoxLayout* configureLayout;
    QHBoxLayout* mainLayout;
    QCheckBox *plusCheckbox;
    QCheckBox *minusCheckbox;
    QCheckBox *subCheckbox;
    QCheckBox *mulCheckbox;
    QCheckBox *bracketCheckbox;
    QCheckBox *floatCheckbox;
    QGroupBox *operatorBox;
    QGridLayout *gridLayout;
    QLineEdit *fileURL;
    QPushButton* browseButton;
    QFileDialog* fileBrowser;
    QString outputPath;

};
#endif // DIALOG_H
