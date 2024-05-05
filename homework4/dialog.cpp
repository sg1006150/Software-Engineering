#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    initializeUI();
    connect(browseButton,&QPushButton::clicked,this,[=]{
        this->fileBrowser->exec();
    });
    connect(fileBrowser,&QFileDialog::urlSelected,this,[=](const QUrl S){
        outputPath=S.toString().mid(8);
        fileURL->setText(outputPath);
    });
    connect(buttonBox,&QDialogButtonBox::rejected,this,[=]
            {
        this->close();
    });
    connect(buttonBox,&QDialogButtonBox::accepted,this,[=]
            {
        QList<char>op;
        int maxnum=qmaxnumEdit->text().toInt();
        int length=qnumEdit->text().toInt();
        int quantity=quantityEdit->text().toInt();
        bool bracket=0;
        bool flo=0;
        textEdit->clear();
        if(plusCheckbox->isChecked())op.append('+');
        if(minusCheckbox->isChecked())op.append('-');
        if(subCheckbox->isChecked())op.append('/');
        if(mulCheckbox->isChecked())op.append('*');
        if(bracketCheckbox->isChecked())bracket=1;
        if(floatCheckbox->isChecked())flo=1;
        if(op.size()==0)
            {
            QMessageBox box;
            box.setText("Choose at least 1 operator");
            box.exec();
            return;
        }
        QString addr=fileURL->text();
        for(int i=0;i<quantity;i++)
        {
            genSuffixExp(op,flo,bracket,maxnum,length,addr);
        }

    });
    priority['+']=1;
    priority['-']=1;
    priority['/']=2;
    priority['*']=2;
}
void Dialog::initializeUI()
{
    formLayout=new QFormLayout;
    qnumEdit=new QLineEdit;
    qnumEdit->setClearButtonEnabled(true);
    qmaxnumEdit=new QLineEdit;
    qmaxnumEdit->setClearButtonEnabled(true);
    quantityEdit=new QLineEdit;
    quantityEdit->setClearButtonEnabled(true);
    quantityEdit->setValidator(new QIntValidator(this->quantityEdit));
    qnumEdit->setValidator(new QIntValidator(this->qnumEdit));
    qmaxnumEdit->setValidator(new QIntValidator(this->qmaxnumEdit));
    qoutputBox=new QComboBox;
    qoutputBox->addItem("File");
    qoutputBox->addItem("Printer");
    buttonBox=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
    textEdit=new QTextEdit;
    textEdit->setReadOnly(true);
    mainLayout=new QHBoxLayout;
    configureLayout=new QVBoxLayout;
    plusCheckbox=new QCheckBox(tr("+"));
    minusCheckbox=new QCheckBox(tr("-"));
    subCheckbox=new QCheckBox(tr("/"));
    mulCheckbox=new QCheckBox(tr("*"));
    bracketCheckbox=new QCheckBox(tr("()"));
    floatCheckbox=new QCheckBox(tr("Float"));
    operatorBox=new QGroupBox;
    gridLayout=new QGridLayout;
    fileURL=new QLineEdit;
    fileURL->setReadOnly(true);
    browseButton=new QPushButton(tr("Browse"));
    QFont font=textEdit->font();
    font.setPointSize(16);
    textEdit->setFont(font);
    formLayout->addRow("Length:",qnumEdit);
    formLayout->addRow("Maxnum:",qmaxnumEdit);
    formLayout->addRow("Quantity",quantityEdit);
    gridLayout->addWidget(plusCheckbox, 0, 0);
    gridLayout->addWidget(minusCheckbox, 0, 1);
    gridLayout->addWidget(subCheckbox, 0, 2);
    gridLayout->addWidget(mulCheckbox, 1, 0);
    gridLayout->addWidget(bracketCheckbox, 1, 1);
    gridLayout->addWidget(floatCheckbox, 1, 2);
    operatorBox->setLayout(gridLayout);
    formLayout->addRow("Options:",operatorBox);
    formLayout->addRow("Output:",qoutputBox);
    formLayout->addRow("Output",fileURL);
    formLayout->addRow("Address",browseButton);
    formLayout->setVerticalSpacing(20);
    formLayout->setContentsMargins(10, 70, 10, 20);
    configureLayout->addLayout(formLayout);
    configureLayout->addWidget(buttonBox);
    mainLayout->addWidget(textEdit,3);
    mainLayout->addLayout(configureLayout,2);
    fileBrowser=new QFileDialog;
    fileBrowser->setFileMode(QFileDialog::Directory);
    this->setLayout(mainLayout);
    this->setFixedWidth(600);
    this->setFixedHeight(600);
}
void Dialog::genSuffixExp(QList<char> op, bool f, bool bracket, int maxnum, int number, QString addr)
{
    QString exp="";
    int stknum=0;
    int numcount=0;
    int opcount=0;
    while(numcount<=number)
    {
        if(stknum<2)
        {
            auto randomnum=generateNumber(f,maxnum,1);
            stknum++;
            numcount++;
            exp+=QString::number(randomnum);
            exp+=' ';
        }
        else
        {
            bool isop=generateNumber(0,1,0);
            if(isop)
            {
                int randindex=generateNumber(0,op.size()-1,0);
                stknum--;
                opcount++;
                exp+=op[randindex];
                exp+=' ';
            }
            else
            {
                auto randomnum=generateNumber(f,maxnum,1);
                stknum++;
                numcount++;
                exp+=QString::number(randomnum);
                exp+=' ';
            }
        }
    }
    while(opcount<number)
    {
        int randindex=generateNumber(0,op.size()-1,0);
        exp+=op[randindex];
        exp+=' ';
        opcount++;
    }
    exp=getInfixExp(exp,bracket);
    if(qoutputBox->currentIndex()==0)handleOuput(exp,addr);
    else handlePrinter(exp);
}
QString Dialog::getInfixExp(QString exp,bool bracket)
{
    QList<QChar> ops;
    for(auto i:exp)
    {
        if(i=='/'||i=='+'||i=='-'||i=='*')ops.append(i);
    }
    int pos=0;
    QStringList tokens = exp.split(" ");
    QStack<QString> exp_stk;
    QString a,b,c;
    for(auto i:tokens)
    {
        if(!(i=='/'||i=='+'||i=='-'||i=='*'))exp_stk.push(i);
        else
        {
            b = exp_stk.top(); exp_stk.pop();
            a = exp_stk.top(); exp_stk.pop();
            pos++;
            if (pos < ops.size() &&priority[ops[pos]] > priority[i.at(0)]&&bracket)
            {
                c = "(" + a + i+ b+")";
            }
            else
            {
                c = a +i+ b;
            }
            exp_stk.push(c);
        }
    }
    exp_stk.pop();
    return exp_stk.top();
}
double Dialog::generateNumber(bool useFloat, int maxnum,int minnum)
{
    if(useFloat)
    {
        double num=QRandomGenerator::global()->generateDouble();
        return num*maxnum;
    }
    else
    {
        return QRandomGenerator::global()->bounded(minnum, maxnum + 1);
    }
}
void Dialog::handleOuput(QString exp, QString addr)
{

    this->textEdit->append(exp);
    this->textEdit->append("\n");
    QString path=addr+"/out.txt";
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            qDebug() << "Error: Cannot open file for writing:" << file.errorString();
            return;
        }
        QTextStream out(&file);
        out << exp<<'\n';
        file.close();
}
void Dialog::handlePrinter(QString exp)
{
    QPrinter printer(QPrinter::PrinterResolution);
    QPrintDialog dialog(&printer);
    if (dialog.exec() == QDialog::Accepted)
    {
        QTextDocument document;
        document.setPlainText(exp);
        document.print(&printer);
    }
}
Dialog::~Dialog()
{
    delete ui;
}

