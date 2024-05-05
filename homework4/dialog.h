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
    //初始化gui
    void initializeUI();
    //生成合法的后缀表达式
    void genSuffixExp(QList<char> op,bool f,bool bracket,int maxnum,int number,QString addr);
    //由后缀表达式转换为中缀表达式，并添加括号
    QString getInfixExp(QString exp,bool bracket);
    //输出到文件
    void handleOuput(QString exp,QString addr);
    //生成随机数
    double generateNumber(bool useFloat,int maxnum,int minnum);
    //在打印机输出
    void handlePrinter(QString exp);
    QMap<QChar,int>priority;
    //gui的实现
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
